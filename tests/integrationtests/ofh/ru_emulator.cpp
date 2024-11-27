/*
 *
 * Copyright 2021-2024 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include "helpers.h"
#include "ru_emulator_appconfig.h"
#include "ru_emulator_cli11_schema.h"
#include "ru_emulator_rx_window_checker.h"
#include "ru_emulator_timing_notifier.h"
#include "ru_emulator_transceiver.h"
#include "srsran/adt/circular_map.h"
#include "srsran/adt/expected.h"
#include "srsran/ofh/compression/compression_params.h"
#include "srsran/ofh/ecpri/ecpri_constants.h"
#include "srsran/ofh/ecpri/ecpri_packet_properties.h"
#include "srsran/ofh/ofh_constants.h"
#include "srsran/ofh/serdes/ofh_message_properties.h"
#include "srsran/ran/resource_block.h"
#include "srsran/ran/slot_point.h"
#include "srsran/srslog/logger.h"
#include "srsran/support/config_parsers.h"
#include "srsran/support/executors/task_execution_manager.h"
#include "srsran/support/executors/task_executor.h"
#include "srsran/support/format_utils.h"
#include "srsran/support/signal_handling.h"
#include "fmt/chrono.h"
#include <arpa/inet.h>
#include <random>
#include <srsran/adt/to_array.h>
#include <srsran/ran/cyclic_prefix.h>
#ifdef DPDK_FOUND
#include "srsran/hal/dpdk/dpdk_eal_factory.h"
#endif

using namespace srsran;
using namespace ofh;
using namespace ether;

/// Ethernet packet size.
static constexpr unsigned ETHERNET_FRAME_SIZE = 9000;

/// Maximum number of symbols in a slot, considering normal cyclic prefix.
static constexpr size_t MAX_NOF_SYMBOLS = get_nsymb_per_slot(cyclic_prefix::NORMAL);

/// Depending on configured compression parameters one UL U-Plane message may occupy up to 2 Ethernet packets.
static constexpr size_t MAX_NOF_PACKETS_PER_UPLANE_MESSAGE = 2;

/// Supported values of udCmpHdr field used for UL U-Plane.
static constexpr auto SUPPORTED_UL_CMPR_HDR = to_array<uint8_t>({0x00, 0x91});

namespace {

/// Structure storing the reception window timing parameters expressed in a number of symbols.
struct ru_em_rx_window_timing_parameters {
  /// Offset from the current OTA symbol to the start of DL Control-Plane reception window. Must be calculated based on
  /// \c T2a_max_cp_dl parameter.
  unsigned sym_cp_dl_start;
  /// Offset from the current OTA symbol to end of DL Control-Plane message reception window. Must be calculated based
  /// on \c T2a_min_cp_dl parameter.
  unsigned sym_cp_dl_end;
  /// Offset from the current OTA symbol to the start of UL Control-Plane reception window. Must be calculated based on
  /// \c T2a_max_cp_ul parameter.
  unsigned sym_cp_ul_start;
  /// Offset from the current OTA symbol to the end of UL Control-Plane reception window. Must be calculated based on \c
  /// T2a_min_cp_ul parameter.
  unsigned sym_cp_ul_end;
  /// Offset from the current OTA symbol to the start of DL User-Plane reception window. Must be calculated based on \c
  /// T2a_max_up parameter.
  unsigned sym_up_dl_start;
  /// Offset from the current OTA symbol to the start of DL User-Plane reception window. Must be calculated based on \c
  /// T2a_min_up parameter.
  unsigned sym_up_dl_end;
};

/// RU emulator configuration structure.
struct ru_emulator_config {
  /// Static compression parameters.
  ru_compression_params compr_params;
  /// Cell bandwidth in number of PRBs.
  unsigned nof_prb;
  /// RU emulator Ethernet MAC address.
  mac_address ru_mac;
  /// DU Ethernet MAC address.
  mac_address du_mac;
  /// VLAN tag.
  unsigned vlan_tag;
  /// Timing parameters.
  ru_em_rx_window_timing_parameters timing_params;
};

/// Helper structure used to group OFH header parameters.
struct header_parameters {
  uint8_t  port;
  unsigned payload_size;
  unsigned start_prb;
  unsigned nof_prbs;
};

/// Aggregates information received in a message from DU.
struct rx_message_info {
  unsigned          eaxc;
  data_direction    direction;
  message_type      type;
  slot_symbol_point symbol_point{{}, 0, MAX_NOF_SYMBOLS};
  unsigned          nof_symbols;
};

/// \brief OFH packet decoding failure codes.
/// drop    - packet must be dropped (it is not an eCPRI OFH packet).
/// corrupt - packet contains OFH message with valid seqID, but contains either an undefined in the ORAN specification
///           value, unsupported value (e.g. compression parameters) or unconfigured value (e.g. eAxC value).
enum class decoder_error_codes { drop, corrupt };

/// One symbol may require up to two byte buffers depending on configured compression parameters.
using symbol_buffer = static_vector<std::vector<uint8_t>, MAX_NOF_PACKETS_PER_UPLANE_MESSAGE>;

/// Array of symbol buffers, representing symbols of one eAxC.
using eaxc_buffers = static_vector<symbol_buffer, MAX_NOF_SYMBOLS>;

} // namespace

/// Fills the given array with random bytes.
static void fill_random_data(span<uint8_t> frame, unsigned seed)
{
  std::mt19937                           rgen(seed);
  std::uniform_int_distribution<uint8_t> dist{0, 255};
  std::generate(frame.begin(), frame.end(), [&]() { return dist(rgen); });
}

/// Fills static OFH header parameters given the static RU config.
static void set_static_header_params(span<uint8_t> frame, header_parameters params, const ru_emulator_config& cfg)
{
  static const uint8_t hdr_template[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x81, 0x00, 0x00, 0x02, 0xae, 0xfe, 0x10, 0x00, 0x1d, 0xea, 0x00, 0x00,
                                         0x00, 0x80, 0x10, 0xee, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0x00};

  // Copy default header.
  std::memcpy(frame.data(), hdr_template, sizeof(hdr_template));

  // Set MAC addresses.
  std::memcpy(&frame[0], cfg.du_mac.data(), ETH_ADDR_LEN);
  std::memcpy(&frame[ETH_ADDR_LEN], cfg.ru_mac.data(), ETH_ADDR_LEN);

  // Set VLAN tag.
  uint16_t net_bytes = htons(uint16_t(cfg.vlan_tag));
  std::memcpy(&frame[14], &net_bytes, sizeof(net_bytes));

  // Set correct payload size.
  uint16_t payload_size = ::htons(params.payload_size);
  std::memcpy(&frame[20], &payload_size, sizeof(uint16_t));

  // Set port ID.
  frame[23] = params.port;

  // Set start PRB and number of PRBs.
  frame[31] = uint8_t(params.start_prb >> 8u) & 0x3;
  frame[32] = uint8_t(params.start_prb);
  frame[33] = uint8_t((params.nof_prbs == cfg.nof_prb) ? 0 : params.nof_prbs);

  // Set compression header.
  uint8_t octet = 0U;
  octet |= uint8_t(cfg.compr_params.data_width) << 4U;
  octet |= uint8_t(to_value(cfg.compr_params.type));
  frame[34] = octet;
}

/// Returns pre-generated test data for each symbol for each configured eAxC.
static std::vector<eaxc_buffers> generate_test_data(const ru_emulator_config& cfg, span<const unsigned> ul_eaxc)
{
  // Vector of bytes for each frame (up to 2) of each OFDM symbol of each eAxC.
  std::vector<eaxc_buffers> test_data;

  const units::bytes ecpri_iq_data_header_size(8);
  const units::bytes ofh_header_size(10);
  const units::bytes ether_header_size(18);

  unsigned headers_size = (ether_header_size + ecpri_iq_data_header_size + ofh_header_size).value();
  // Size in bytes of one PRB using the given static compression parameters.
  units::bytes prb_size = units::bits(cfg.compr_params.data_width * NOF_SUBCARRIERS_PER_RB * 2 +
                                      (cfg.compr_params.type == compression_type::BFP ? 8 : 0))
                              .round_up_to_bytes();
  unsigned iq_data_size = cfg.nof_prb * prb_size.value();

  // It is assumed that maximum 2 packets required to send symbol data for antenna.
  unsigned nof_frames = ((headers_size + iq_data_size) > ETHERNET_FRAME_SIZE) ? 2u : 1u;
  // Save number of PRBs to be sent in each allocated frame.
  std::vector<unsigned> nof_frame_prbs;
  if (nof_frames == 1) {
    nof_frame_prbs.push_back(cfg.nof_prb);
  } else {
    unsigned nof_prbs_first  = (ETHERNET_FRAME_SIZE - headers_size) / prb_size.value();
    unsigned nof_prbs_second = cfg.nof_prb - nof_prbs_first;
    nof_frame_prbs.push_back(nof_prbs_first);
    nof_frame_prbs.push_back(nof_prbs_second);
  }

  // Initializes IQ data and Ethernet packet headers for all configured eAxCs (timestamp and sequence index
  // will be updated on every transmission).
  for (unsigned port = 0, last = ul_eaxc.size(); port != last; ++port) {
    test_data.emplace_back();
    auto& eaxc_frames = test_data.back();

    for (unsigned symbol = 0, end = MAX_NOF_SYMBOLS; symbol != end; ++symbol) {
      eaxc_frames.emplace_back();
      auto& symbol_frames = eaxc_frames.back();

      unsigned start_prb = 0;
      for (unsigned j = 0; j != nof_frames; ++j) {
        unsigned data_size = nof_frame_prbs[j] * prb_size.value();

        symbol_frames.emplace_back();
        std::vector<uint8_t>& frame = symbol_frames.back();
        frame.resize(headers_size + data_size);

        // Prepare header.
        span<uint8_t>     frame_header(frame.data(), headers_size);
        header_parameters params;
        params.port         = port;
        params.payload_size = data_size + ofh_header_size.value() + ecpri::ECPRI_COMMON_HEADER_SIZE.value();
        params.start_prb    = start_prb;
        params.nof_prbs     = nof_frame_prbs[j];

        set_static_header_params(frame_header, params, cfg);

        // Prepare IQ data.
        fill_random_data(span<uint8_t>(frame).last(data_size), ul_eaxc[port] + symbol);

        start_prb += nof_frame_prbs[j];
      }
    }
  }
  return test_data;
}

static ru_em_rx_window_timing_parameters rx_timing_window_params_us_to_symbols(std::chrono::microseconds T2a_max_cp_dl,
                                                                               std::chrono::microseconds T2a_min_cp_dl,
                                                                               std::chrono::microseconds T2a_max_cp_ul,
                                                                               std::chrono::microseconds T2a_min_cp_ul,
                                                                               std::chrono::microseconds T2a_max_up,
                                                                               std::chrono::microseconds T2a_min_up)
{
  std::chrono::duration<double, std::nano> symbol_duration(
      (1e6 / (MAX_NOF_SYMBOLS * get_nof_slots_per_subframe(subcarrier_spacing::kHz30))));

  ru_em_rx_window_timing_parameters rx_window_timing_params;
  rx_window_timing_params.sym_cp_dl_start = std::floor(T2a_max_cp_dl / symbol_duration);
  rx_window_timing_params.sym_cp_dl_end   = std::ceil(T2a_min_cp_dl / symbol_duration);
  rx_window_timing_params.sym_cp_ul_start = std::floor(T2a_max_cp_ul / symbol_duration);
  rx_window_timing_params.sym_cp_ul_end   = std::ceil(T2a_min_cp_ul / symbol_duration);
  rx_window_timing_params.sym_up_dl_start = std::floor(T2a_max_up / symbol_duration);
  rx_window_timing_params.sym_up_dl_end   = std::ceil(T2a_min_up / symbol_duration);

  return rx_window_timing_params;
}

/// Analyzes content of received OFH packets.
/// Returns decoded message parameters on success, otherwise an error code (see \c decoder_error_codes).
static expected<rx_message_info, decoder_error_codes>
decode_rx_message(span<const uint8_t> packet, span<const unsigned> ul_eaxc, srslog::basic_logger& logger)
{
  rx_message_info message_info;

  // Drop non OFH packet.
  if (packet.size() < 26) {
    logger.debug("Dropping packet of size smaller than 26 bytes");
    return make_unexpected(decoder_error_codes::drop);
  }

  // Verify the Ethernet type is eCPRI.
  uint16_t eth_type = (uint16_t(packet[12]) << 8u) | packet[13];
  if (eth_type != ECPRI_ETH_TYPE) {
    logger.debug("Dropping packet as it is not of eCPRI type");
    return make_unexpected(decoder_error_codes::drop);
  }

  // Check the filter index in the byte 26, bits 0-3.
  auto filter_index = static_cast<filter_index_type>(packet[22] & 0x0f);
  if (filter_index != filter_index_type::standard_channel_filter) {
    logger.warning("Packet is corrupt: non-standard filter index = {} decoded", filter_index);
    return make_unexpected(decoder_error_codes::corrupt);
  }

  uint8_t type = packet[15];
  if (type != uint8_t(ecpri::message_type::rt_control_data) && type != uint8_t(ecpri::message_type::iq_data)) {
    logger.warning("Packet is corrupt: unknown eCPRI message type = {} decoded", type);
    return make_unexpected(decoder_error_codes::corrupt);
  }
  message_info.type = static_cast<ecpri::message_type>(type) == ecpri::message_type::rt_control_data
                          ? message_type::control_plane
                          : message_type::user_plane;

  // Check direction, which is codified in the byte 26, bit 7.
  message_info.direction = static_cast<data_direction>((packet[22] & 0x80) >> 7u);
  logger.debug("Packet direction is {}", message_info.direction == data_direction::uplink ? "uplink" : "downlink");

  // Peek the timestamp.
  unsigned slot_id           = 0;
  unsigned symbol_id         = 0;
  uint8_t  frame             = packet[23];
  uint8_t  subframe_and_slot = packet[24];
  uint8_t  slot_and_symbol   = packet[25];
  uint8_t  subframe          = subframe_and_slot >> 4;

  slot_id |= (subframe_and_slot & 0x0f) << 2;
  slot_id |= slot_and_symbol >> 6;
  symbol_id = slot_and_symbol & 0x3f;

  auto slot                 = slot_point(to_numerology_value(subcarrier_spacing::kHz30), frame, subframe, slot_id);
  message_info.symbol_point = {slot, symbol_id, MAX_NOF_SYMBOLS};

  if (!message_info.symbol_point.get_slot().valid() || !message_info.symbol_point.is_valid()) {
    logger.warning("Packet is corrupt: incorrect timestamp = {}:{}",
                   message_info.symbol_point.get_slot(),
                   message_info.symbol_point.get_symbol_index());
    return make_unexpected(decoder_error_codes::corrupt);
  }

  // Following parameters are only checked for UL C-Plane messages.
  if (message_info.direction == data_direction::uplink && message_info.type == message_type::control_plane) {
    // Peek the eAxC.
    message_info.eaxc = packet[19];

    if (std::find(ul_eaxc.begin(), ul_eaxc.end(), message_info.eaxc) == ul_eaxc.end()) {
      logger.warning("Packet is corrupt: received eAxC = '{}' is not configured in the RU emulator", message_info.eaxc);
      return make_unexpected(decoder_error_codes::corrupt);
    }

    // Peek number of symbols.
    message_info.nof_symbols = (packet[35] & 0xf);
    if (message_info.nof_symbols > MAX_NOF_SYMBOLS) {
      logger.warning("Packet is corrupt: incorrect number of symbols = {}", message_info.nof_symbols);
      return make_unexpected(decoder_error_codes::corrupt);
    }

    // For UL C-Plane message check also compression parameters.
    uint8_t compr_header = packet[28];
    if (std::find(SUPPORTED_UL_CMPR_HDR.begin(), SUPPORTED_UL_CMPR_HDR.end(), compr_header) ==
        SUPPORTED_UL_CMPR_HDR.end()) {
      logger.warning("Packet is corrupt: unsupported UL compression parameters = {}", compr_header);
      return make_unexpected(decoder_error_codes::corrupt);
    }
  }

  return message_info;
}

namespace {

/// RU emulator receives OFH traffic and replies with UL packets to a DU.
class ru_emulator : public frame_notifier
{
  /// Helper class that represents a KPI counter.
  class kpi_counter
  {
    std::atomic<uint64_t> counter{0};
    uint64_t              last_value_printed = 0U;

  public:
    uint64_t get_value()
    {
      uint64_t current_value = counter.load(std::memory_order_relaxed);
      uint64_t total         = current_value - last_value_printed;
      last_value_printed     = current_value;
      return total;
    }

    void increment(unsigned n = 1) { counter.fetch_add(n, std::memory_order_relaxed); }
  };

  srslog::basic_logger&    logger;
  task_executor&           executor;
  ru_emulator_transceiver& transceiver;

  // Timing window checkers, store statistics of early/late/on-time packets.
  ru_emulator_rx_window_checker dl_cp_window_checker;
  ru_emulator_rx_window_checker dl_up_window_checker;
  ru_emulator_rx_window_checker ul_cp_window_checker;

  // RU emulator configuration.
  const ru_emulator_config cfg;
  // Pre-generated test data for each symbol for each configured eAxC.
  std::vector<eaxc_buffers> test_data;
  // Keeps track of last used seq_id for each eAxC.
  circular_map<unsigned, uint8_t, MAX_SUPPORTED_EAXC_ID_VALUE> seq_counters;
  // Stores the list of configured eAxC.
  static_vector<unsigned, MAX_NOF_SUPPORTED_EAXC> ul_eaxc;

  // Other KPI counters.
  kpi_counter rx_total_counter;
  kpi_counter tx_total_counter;
  kpi_counter corrupt_counter;
  kpi_counter dropped_counter;

public:
  ru_emulator(srslog::basic_logger&    logger_,
              task_executor&           executor_,
              ru_emulator_transceiver& transceiver_,
              ru_emulator_config       cfg_,
              std::vector<unsigned>    ul_eaxc_) :
    logger(logger_),
    executor(executor_),
    transceiver(transceiver_),
    dl_cp_window_checker({cfg_.timing_params.sym_cp_dl_end, cfg_.timing_params.sym_cp_dl_start}),
    dl_up_window_checker({cfg_.timing_params.sym_up_dl_end, cfg_.timing_params.sym_up_dl_start}),
    ul_cp_window_checker({cfg_.timing_params.sym_cp_ul_end, cfg_.timing_params.sym_cp_ul_start}),
    cfg(cfg_)
  {
    ul_eaxc.assign(ul_eaxc_.begin(), ul_eaxc_.end());
    for (auto eaxc : ul_eaxc) {
      srsran_assert(eaxc <= MAX_SUPPORTED_EAXC_ID_VALUE, "Unsupported eAxC value requested");
      seq_counters.insert(eaxc, 0);
    }

    test_data = generate_test_data(cfg, ul_eaxc);
  }

  // See interface for documentation.
  void on_new_frame(unique_rx_buffer buffer) override
  {
    if (!executor.execute([this, b = std::move(buffer)]() mutable { process_new_frame(std::move(b)); })) {
      logger.warning("Failed to dispatch receiver task");
    }
  }

  void start() { transceiver.start(*this); }

  void print_statistics(unsigned emu_id)
  {
    fmt::memory_buffer buffer;

    auto    now          = std::chrono::system_clock::now();
    std::tm current_time = fmt::gmtime(std::chrono::system_clock::to_time_t(now));

    // Fetch KPIs from window checkers.
    auto dl_up_kpi = dl_up_window_checker.get_statistics();
    auto dl_cp_kpi = dl_cp_window_checker.get_statistics();
    auto ul_cp_kpi = ul_cp_window_checker.get_statistics();

    uint64_t rx_total  = rx_total_counter.get_value();
    uint64_t tx_total  = tx_total_counter.get_value();
    uint64_t malformed = corrupt_counter.get_value();
    uint64_t dropped   = dropped_counter.get_value();

    fmt::format_to(buffer,
                   "| {:%H:%M:%S} | {:^3} | {:^11} | {:^11} | {:^11} | {:^11} | {:^13} | {:^13} | {:^13} | {:^14} | "
                   "{:^14} | {:^14} | {:^11} | {:^11} | {:^11} |\n",
                   current_time,
                   emu_id,
                   rx_total,
                   dl_up_kpi.rx_on_time,
                   dl_up_kpi.rx_early,
                   dl_up_kpi.rx_late,
                   dl_cp_kpi.rx_on_time,
                   dl_cp_kpi.rx_early,
                   dl_cp_kpi.rx_late,
                   ul_cp_kpi.rx_on_time,
                   ul_cp_kpi.rx_early,
                   ul_cp_kpi.rx_late,
                   malformed,
                   dropped,
                   tx_total);

    fmt::print(to_c_str(buffer));
  }

  std::vector<ofh::ota_symbol_boundary_notifier*> get_ota_notifiers()
  {
    std::vector<ofh::ota_symbol_boundary_notifier*> notifiers;
    notifiers.push_back(&dl_up_window_checker);
    notifiers.push_back(&dl_cp_window_checker);
    notifiers.push_back(&ul_cp_window_checker);

    return notifiers;
  }

private:
  /// Returns window checker for OFH messages of corresponding type given by \c message_info parameter.
  ru_emulator_rx_window_checker& get_window_checker(rx_message_info& message_info)
  {
    return (message_info.direction == data_direction::uplink)   ? ul_cp_window_checker
           : (message_info.type == message_type::control_plane) ? dl_cp_window_checker
                                                                : dl_up_window_checker;
  }

  /// Decodes and processes received OFH message.
  void process_new_frame(unique_rx_buffer buffer)
  {
    span<const uint8_t> payload = buffer.data();

    auto decoded_message_info = decode_rx_message(payload, ul_eaxc, logger);

    if (!decoded_message_info.has_value()) {
      switch (decoded_message_info.error()) {
        case decoder_error_codes::corrupt:
          corrupt_counter.increment();
          break;
        case decoder_error_codes::drop:
          dropped_counter.increment();
          break;
      }
      return;
    }
    rx_total_counter.increment();

    auto message_info = decoded_message_info.value();
    get_window_checker(message_info).update_rx_window_statistics(message_info.symbol_point);

    if (message_info.direction == data_direction::uplink) {
      generate_ul_uplane_messages(message_info);
    }
  }

  /// Generates UL U-Plane messages with correct headers based on received C-Plane message.
  void generate_ul_uplane_messages(rx_message_info& message_info)
  {
    static_vector<span<const uint8_t>, MAX_BURST_SIZE> frame_burst;

    auto& eaxc_frames = test_data[message_info.eaxc];

    // Set correct header parameters and send UL U-Plane packets for each symbol.
    for (unsigned symbol = message_info.symbol_point.get_symbol_index(), end = message_info.nof_symbols; symbol != end;
         ++symbol) {
      auto& symbol_frames = eaxc_frames[symbol];
      // Set runtime header parameters.
      for (auto& frame : symbol_frames) {
        set_runtime_header_params(frame, message_info.symbol_point.get_slot(), symbol, message_info.eaxc);
        frame_burst.emplace_back(frame.data(), frame.size());
      }
    }
    // Send symbols.
    transceiver.send(frame_burst);

    // Increment TX_TOTAL counter.
    tx_total_counter.increment(frame_burst.size());
  }

  void set_runtime_header_params(span<uint8_t> frame, slot_point slot, unsigned symbol, unsigned eaxc)
  {
    // Set timestamp.
    uint8_t octet = 0;
    frame[27]     = uint8_t(slot.sfn());
    // Subframe index; offset: 4, 4 bits long.
    octet |= uint8_t(slot.subframe_index()) << 4u;
    // Four MSBs of the slot index within 1ms subframe; offset: 4, 6 bits long.
    octet |= uint8_t(slot.subframe_slot_index() >> 2u);
    frame[28] = octet;

    octet = 0;
    octet |= uint8_t(slot.subframe_slot_index() & 0x3) << 6u;
    octet |= uint8_t(symbol);
    frame[29] = octet;

    // Set sequence index.
    uint8_t& seq_id = seq_counters[eaxc];
    frame[24]       = seq_id++;
  }
};

/// Manages the workers of the RU emulators.
struct worker_manager {
  static constexpr uint32_t task_worker_queue_size = 1024;

  worker_manager(unsigned nof_emulators) { create_executors(nof_emulators); }

  void create_executors(unsigned nof_emulators)
  {
    using namespace execution_config_helper;

    for (unsigned i = 0; i != nof_emulators; ++i) {
      // Executors for Open Fronthaul messages reception.
      {
        const std::string name      = "ru_rx_#" + std::to_string(i);
        const std::string exec_name = "ru_rx_exec_#" + std::to_string(i);

        const single_worker ru_worker{name,
                                      {concurrent_queue_policy::lockfree_spsc, 2},
                                      {{exec_name}},
                                      std::chrono::microseconds{1},
                                      os_thread_realtime_priority::max() - 1};
        if (!exec_mng.add_execution_context(create_execution_context(ru_worker))) {
          report_fatal_error("Failed to instantiate {} execution context", ru_worker.name);
        }
        ru_rx_exec.push_back(exec_mng.executors().at(exec_name));
      }

      // Executors for the RU emulators.
      {
        const std::string   name      = "ru_emu_#" + std::to_string(i);
        const std::string   exec_name = "ru_emu_exec_#" + std::to_string(i);
        const single_worker ru_worker{name,
                                      {concurrent_queue_policy::lockfree_spsc, task_worker_queue_size},
                                      {{exec_name}},
                                      std::chrono::microseconds{1},
                                      os_thread_realtime_priority::max() - 1};
        if (!exec_mng.add_execution_context(create_execution_context(ru_worker))) {
          report_fatal_error("Failed to instantiate {} execution context", ru_worker.name);
        }
        ru_emulators_exec.push_back(exec_mng.executors().at(exec_name));
      }
    }

    // Timing executor.
    {
      const std::string name      = "ru_timing";
      const std::string exec_name = "ru_timing_exec";

      const single_worker ru_worker{name,
                                    {concurrent_queue_policy::lockfree_spsc, 4},
                                    {{exec_name}},
                                    std::chrono::microseconds{0},
                                    os_thread_realtime_priority::max() - 0};
      if (!exec_mng.add_execution_context(create_execution_context(ru_worker))) {
        report_fatal_error("Failed to instantiate {} execution context", ru_worker.name);
      }
      ru_timing_exec = exec_mng.executors().at(exec_name);
    }
  }

  void stop() { exec_mng.stop(); }

  task_execution_manager exec_mng;
  task_executor*         ru_timing_exec = nullptr;

  std::vector<task_executor*> ru_rx_exec;
  std::vector<task_executor*> ru_emulators_exec;
};

} // namespace

static std::string config_file;

/// Flag that indicates if the application is running or being shutdown.
static std::atomic<bool> is_app_running = {true};
/// Maximum number of configuration files allowed to be concatenated in the command line.
static constexpr unsigned MAX_CONFIG_FILES = 6;

/// Function to call when the application is interrupted.
static void interrupt_signal_handler()
{
  is_app_running = false;
}

/// Function to call when the application is going to be forcefully shutdown.
static void cleanup_signal_handler()
{
  srslog::flush();
}

int main(int argc, char** argv)
{
  // Set interrupt and cleanup signal handlers.
  register_interrupt_signal_handler(interrupt_signal_handler);
  register_cleanup_signal_handler(cleanup_signal_handler);

  // Setup and configure config parsing.
  CLI::App app("RU emulator application");
  app.config_formatter(create_yaml_config_parser());
  app.allow_config_extras(CLI::config_extras_mode::error);
  app.set_config("-c,", config_file, "Read config from file", false)->expected(1, MAX_CONFIG_FILES);

  ru_emulator_appconfig ru_emulator_parsed_cfg;
  // Configure CLI11 with the RU emulator application configuration schema.
  configure_cli11_with_ru_emulator_appconfig_schema(app, ru_emulator_parsed_cfg);

  // Parse arguments.
  CLI11_PARSE(app, argc, argv);

  if (ru_emulator_parsed_cfg.ru_cfg.empty()) {
    report_error("Invalid configuration detected, at least one RU configuration must be provided\n");
  }

  // Set up logging.
  srslog::sink* log_sink = (ru_emulator_parsed_cfg.log_cfg.filename == "stdout")
                               ? srslog::create_stdout_sink()
                               : srslog::create_file_sink(ru_emulator_parsed_cfg.log_cfg.filename);
  if (log_sink == nullptr) {
    report_error("Could not create application main log sink.\n");
  }
  srslog::set_default_sink(*log_sink);
  srslog::init();

  srslog::basic_logger& logger = srslog::fetch_basic_logger("RU_EMU", false);
  logger.set_level(ru_emulator_parsed_cfg.log_cfg.level);

#ifdef DPDK_FOUND
  bool uses_dpdk = ru_emulator_parsed_cfg.dpdk_config.has_value();

  // Initialize DPDK EAL.
  std::unique_ptr<dpdk::dpdk_eal> eal;
  if (uses_dpdk) {
    // Prepend the application name in argv[0] as it is expected by EAL.
    eal = dpdk::create_dpdk_eal(std::string(argv[0]) + " " + ru_emulator_parsed_cfg.dpdk_config->eal_args,
                                srslog::fetch_basic_logger("EAL", false));
    if (!eal) {
      report_error("Failed to initialize DPDK EAL\n");
    }
  }
#endif
  // Create workers and executors.
  worker_manager workers(ru_emulator_parsed_cfg.ru_cfg.size());

  // Set up DPDK transceivers and create RU emulators.
  std::vector<std::unique_ptr<ru_emulator_transceiver>> transceivers;
  std::vector<std::unique_ptr<ru_emulator>>             ru_emulators;

  for (unsigned i = 0, e = ru_emulator_parsed_cfg.ru_cfg.size(); i != e; ++i) {
    ru_emulator_ofh_appconfig ru_cfg = ru_emulator_parsed_cfg.ru_cfg[i];
#ifdef DPDK_FOUND
    if (uses_dpdk) {
      dpdk_port_config port_cfg;
      port_cfg.pcie_id                     = ru_cfg.network_interface;
      port_cfg.mtu_size                    = units::bytes{ETHERNET_FRAME_SIZE};
      port_cfg.is_promiscuous_mode_enabled = ru_cfg.enable_promiscuous;
      auto ctx                             = dpdk_port_context::create(port_cfg);
      transceivers.push_back(std::make_unique<dpdk_transceiver>(logger, *workers.ru_rx_exec[i], ctx));
    } else
#endif
    {
      gw_config cfg;
      cfg.interface                   = ru_cfg.network_interface;
      cfg.mtu_size                    = units::bytes{ETHERNET_FRAME_SIZE};
      cfg.is_promiscuous_mode_enabled = ru_cfg.enable_promiscuous;
      if (!parse_mac_address(ru_cfg.du_mac_address, cfg.mac_dst_address)) {
        report_error("Invalid MAC address provided: '{}'", ru_cfg.du_mac_address);
      }
      transceivers.push_back(std::make_unique<socket_transceiver>(logger, *workers.ru_rx_exec[i], cfg));
    }

    ru_emulator_config emu_cfg;
    emu_cfg.nof_prb =
        get_max_Nprb(bs_channel_bandwidth_to_MHz(ru_cfg.bandwidth), subcarrier_spacing::kHz30, frequency_range::FR1);
    emu_cfg.compr_params = {to_compression_type(ru_cfg.ul_compr_method), ru_cfg.ul_compr_bitwidth};
    emu_cfg.vlan_tag     = ru_cfg.vlan_tag;
    if (!parse_mac_address(ru_cfg.ru_mac_address, emu_cfg.ru_mac)) {
      report_error("Invalid MAC address provided: '{}'", ru_cfg.ru_mac_address);
    }
    if (!parse_mac_address(ru_cfg.du_mac_address, emu_cfg.du_mac)) {
      report_error("Invalid MAC address provided: '{}'", ru_cfg.du_mac_address);
    }
    emu_cfg.timing_params = rx_timing_window_params_us_to_symbols(ru_cfg.T2a_max_cp_dl,
                                                                  ru_cfg.T2a_min_cp_dl,
                                                                  ru_cfg.T2a_max_cp_ul,
                                                                  ru_cfg.T2a_min_cp_ul,
                                                                  ru_cfg.T2a_max_up,
                                                                  ru_cfg.T2a_min_up);

    ru_emulators.push_back(std::make_unique<ru_emulator>(
        logger, *workers.ru_emulators_exec[i], *transceivers[i], emu_cfg, ru_cfg.ru_ul_port_id));
  }

  // Create timing worker.
  ru_emulator_timing_notifier timing_notifier(logger, *workers.ru_timing_exec);

  // Subscribe RU emulator window checkers to the 'OTA symbol start' notifications.
  std::vector<ofh::ota_symbol_boundary_notifier*> ota_symbol_notifiers;
  for (auto& ru : ru_emulators) {
    auto ru_em_ota_notifiers = ru->get_ota_notifiers();
    ota_symbol_notifiers.insert(ota_symbol_notifiers.end(), ru_em_ota_notifiers.begin(), ru_em_ota_notifiers.end());
  }
  timing_notifier.subscribe(ota_symbol_notifiers);

  // Start RU emulators.
  timing_notifier.start();
  for (auto& ru : ru_emulators) {
    ru->start();
  }
  fmt::print("Running. Waiting for incoming packets...\n");

  fmt::print("| {:^8} | {:^3} | {:^11} | {:^11} | {:^11} | {:^11} | {:^13} | {:^13} | {:^13} | {:^14} | {:^14} | "
             "{:^14} | {:^11} | {:^11} | {:^11} |\n",
             "TIME",
             "ID",
             "RX_TOTAL",
             "RX_ON_TIME",
             "RX_EARLY",
             "RX_LATE",
             "RX_ON_TIME_C",
             "RX_EARLY_C",
             "RX_LATE_C",
             "RX_ON_TIME_C_U",
             "RX_EARLY_C_U",
             "RX_LATE_C_U",
             "RX_CORRUPT",
             "RX_ERR_DROP",
             "TX_TOTAL");

  while (is_app_running) {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    for (unsigned i = 0, e = ru_emulators.size(); i != e; ++i) {
      ru_emulators[i]->print_statistics(i);
    }
  }

  timing_notifier.stop();
  for (auto& txrx : transceivers) {
    txrx->stop();
  }
  workers.stop();
  srslog::flush();

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  fmt::print("\nRU emulator app stopped\n");

  return 0;
}
