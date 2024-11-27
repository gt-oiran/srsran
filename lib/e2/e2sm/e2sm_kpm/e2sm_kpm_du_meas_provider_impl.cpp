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

#include "e2sm_kpm_du_meas_provider_impl.h"

using namespace asn1::e2ap;
using namespace asn1::e2sm;
using namespace srsran;

e2sm_kpm_du_meas_provider_impl::e2sm_kpm_du_meas_provider_impl(srs_du::f1ap_ue_id_translator& f1ap_ue_id_translator_) :
  logger(srslog::fetch_basic_logger("E2SM-KPM")), f1ap_ue_id_provider(f1ap_ue_id_translator_)
{
  // Array of supported metrics.
  supported_metrics.emplace(
      "CQI", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, false, &e2sm_kpm_du_meas_provider_impl::get_cqi});
  supported_metrics.emplace(
      "RSRP", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, false, &e2sm_kpm_du_meas_provider_impl::get_rsrp});
  supported_metrics.emplace(
      "RSRQ", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, false, &e2sm_kpm_du_meas_provider_impl::get_rsrq});
  supported_metrics.emplace(
      "SNR", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_pusch_snr});
  supported_metrics.emplace(
      "PCI", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_pci});
  supported_metrics.emplace(
      "RNTI", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_rnti});
  supported_metrics.emplace(
      "BrateDl", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_brate_dl});
  supported_metrics.emplace(
      "BrateUl", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_brate_ul});
  supported_metrics.emplace(
      "McsDl", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_mcs_dl});
  supported_metrics.emplace(
      "McsUl", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_mcs_ul});
  supported_metrics.emplace(
      "NofOKDl", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_nof_ok_dl});
  supported_metrics.emplace(
      "NofOKUl", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_nof_ok_ul});
  supported_metrics.emplace(
      "NofNOKDl", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_nof_nok_dl});
  supported_metrics.emplace(
      "NofNOKUl", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_nof_nok_ul});
  supported_metrics.emplace(
      "BSR", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_bsr});
  supported_metrics.emplace(
      "BSDl", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_dl_bs});
  supported_metrics.emplace(
      "TA", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_ta});
  supported_metrics.emplace(
      "PHR", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_phr});
  supported_metrics.emplace(
      "RI", e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_ri});


  supported_metrics.emplace(
      "RRU.PrbAvailDl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, E2_NODE_LEVEL | UE_LEVEL, true, &e2sm_kpm_du_meas_provider_impl::get_prb_avail_dl});

  supported_metrics.emplace(
      "RRU.PrbAvailUl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, E2_NODE_LEVEL | UE_LEVEL, true, &e2sm_kpm_du_meas_provider_impl::get_prb_avail_ul});

  supported_metrics.emplace(
      "RRU.PrbUsedDl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, E2_NODE_LEVEL | UE_LEVEL, true, &e2sm_kpm_du_meas_provider_impl::get_prb_used_dl});

  supported_metrics.emplace(
      "RRU.PrbUsedUl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, E2_NODE_LEVEL | UE_LEVEL, true, &e2sm_kpm_du_meas_provider_impl::get_prb_used_ul});

  supported_metrics.emplace(
      "RRU.PrbTotDl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, E2_NODE_LEVEL | UE_LEVEL, true, &e2sm_kpm_du_meas_provider_impl::get_prb_use_perc_dl});

  supported_metrics.emplace(
      "RRU.PrbTotUl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, E2_NODE_LEVEL | UE_LEVEL, true, &e2sm_kpm_du_meas_provider_impl::get_prb_use_perc_ul});

  supported_metrics.emplace(
      "DRB.RlcSduDelayDl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_drb_dl_rlc_sdu_latency});

  supported_metrics.emplace(
      "DRB.PacketSuccessRateUlgNBUu",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, E2_NODE_LEVEL | UE_LEVEL, true, &e2sm_kpm_du_meas_provider_impl::get_drb_ul_success_rate});
  supported_metrics.emplace(
      "DRB.UEThpDl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, E2_NODE_LEVEL | UE_LEVEL, true, &e2sm_kpm_du_meas_provider_impl::get_drb_dl_mean_throughput});
  supported_metrics.emplace(
      "DRB.UEThpUl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, E2_NODE_LEVEL | UE_LEVEL, true, &e2sm_kpm_du_meas_provider_impl::get_drb_ul_mean_throughput});
  supported_metrics.emplace(
      "DRB.RlcPacketDropRateDl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_drb_rlc_packet_drop_rate_dl});
  supported_metrics.emplace(
      "DRB.RlcSduTransmittedVolumeDL",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_drb_rlc_sdu_transmitted_volume_dl});
  supported_metrics.emplace(
      "DRB.RlcSduTransmittedVolumeUL",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_drb_rlc_sdu_transmitted_volume_ul});

  supported_metrics.emplace(
      "DRB.AirIfDelayUl",
      e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_delay_ul});

  supported_metrics.emplace(
      "DRB.RlcDelayUl",
      e2sm_kpm_supported_metric_t{
          NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_drb_ul_rlc_sdu_latency});

  supported_metrics.emplace(
      "RACH.PreambleDedCell",
      e2sm_kpm_supported_metric_t{NO_LABEL, ALL_LEVELS, true, &e2sm_kpm_du_meas_provider_impl::get_prach_cell_count});

  // Check if the supported metrics are matching e2sm_kpm metrics definitions.
  check_e2sm_kpm_metrics_definitions(get_e2sm_kpm_28_552_metrics());
  check_e2sm_kpm_metrics_definitions(get_e2sm_kpm_oran_metrics());
}

e2sm_kpm_du_meas_provider_impl::e2sm_kpm_du_meas_provider_impl(srs_du::f1ap_ue_id_translator& f1ap_ue_id_translator_,
                                                               int                            max_rlc_metrics_) :
  e2sm_kpm_du_meas_provider_impl(f1ap_ue_id_translator_)
{
  max_rlc_metrics = max_rlc_metrics_;
}

bool e2sm_kpm_du_meas_provider_impl::check_e2sm_kpm_metrics_definitions(span<const e2sm_kpm_metric_t> metric_defs)
{
  std::string metric_name;
  auto        name_matches = [&metric_name](const e2sm_kpm_metric_t& x) {
    return (x.name == metric_name.c_str() or x.name == metric_name);
  };

  for (auto& supported_metric : supported_metrics) {
    metric_name = supported_metric.first;
    auto it     = std::find_if(metric_defs.begin(), metric_defs.end(), name_matches);
    if (it == metric_defs.end()) {
      continue;
    }

    if (supported_metric.second.supported_labels & ~(it->optional_labels | e2sm_kpm_label_enum::NO_LABEL)) {
      logger.debug("Wrong definition of the supported metric: \"{}\", labels cannot be supported.", metric_name);
    }

    if (supported_metric.second.supported_levels & ~it->optional_levels) {
      logger.debug("Wrong definition of the supported metric: \"{}\", level cannot be supported.", metric_name);
    }

    if (is_cell_id_required(*it) and not supported_metric.second.cell_scope_supported) {
      logger.debug("Wrong definition of the supported metric: \"{}\", cell scope has to be supported.",
                   metric_name.c_str());
    }
  }
  return true;
}

void e2sm_kpm_du_meas_provider_impl::report_metrics(const scheduler_cell_metrics& cell_metrics)
{
  last_ue_metrics.clear();
  nof_cell_prbs          = cell_metrics.nof_prbs;
  nof_dl_slots           = cell_metrics.nof_dl_slots;
  nof_ul_slots           = cell_metrics.nof_ul_slots;
  nof_ded_cell_preambles = cell_metrics.nof_prach_preambles;
  for (auto& ue_metric : cell_metrics.ue_metrics) {
    last_ue_metrics.push_back(ue_metric);
  }
}

void e2sm_kpm_du_meas_provider_impl::report_metrics(const rlc_metrics& metrics)
{
  logger.debug("Received RLC metrics: ue={} {}.", metrics.ue_index, metrics.rb_id.get_drb_id());
  ue_aggr_rlc_metrics[metrics.ue_index].push_back(metrics);
  if (ue_aggr_rlc_metrics[metrics.ue_index].size() > max_rlc_metrics) {
    ue_aggr_rlc_metrics[metrics.ue_index].pop_front();
  }
}

std::vector<std::string> e2sm_kpm_du_meas_provider_impl::get_supported_metric_names(e2sm_kpm_metric_level_enum level)
{
  std::vector<std::string> metrics;
  for (auto& m : supported_metrics) {
    if ((level & E2_NODE_LEVEL) and (m.second.supported_levels & E2_NODE_LEVEL)) {
      metrics.push_back(m.first);
    } else if ((level & UE_LEVEL) and (m.second.supported_levels & UE_LEVEL)) {
      metrics.push_back(m.first);
    }
  }
  return metrics;
}

bool e2sm_kpm_du_meas_provider_impl::is_cell_supported(const asn1::e2sm::cgi_c& cell_global_id)
{
  // TODO: check if CELL is supported
  return true;
}

bool e2sm_kpm_du_meas_provider_impl::is_ue_supported(const asn1::e2sm::ue_id_c& ueid)
{
  // TODO: check if UE is supported
  return true;
}

bool e2sm_kpm_du_meas_provider_impl::is_test_cond_supported(const asn1::e2sm::test_cond_type_c& test_cond_type)
{
  // TODO: check if test condition is supported
  return true;
}

bool e2sm_kpm_du_meas_provider_impl::is_metric_supported(const asn1::e2sm::meas_type_c&   meas_type,
                                                         const asn1::e2sm::meas_label_s&  label,
                                                         const e2sm_kpm_metric_level_enum level,
                                                         const bool&                      cell_scope)
{
  if (!label.no_label_present) {
    logger.debug("Currently only NO_LABEL metric supported.");
    return false;
  }

  for (auto& metric : supported_metrics) {
    if (strcmp(meas_type.meas_name().to_string().c_str(), metric.first.c_str()) == 0) {
      return true;
    }
  }

  // TODO: check if metric supported with required label, level and cell_scope
  return false;
}

bool e2sm_kpm_du_meas_provider_impl::get_ues_matching_test_conditions(
    const asn1::e2sm::matching_cond_list_l& matching_cond_list,
    std::vector<asn1::e2sm::ue_id_c>&       ues)
{
  // TODO: add test condition checking, now return all UEs
  for (const auto& ue : ue_aggr_rlc_metrics) {
    du_ue_index_t       ue_index          = to_du_ue_index(ue.first);
    gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = f1ap_ue_id_provider.get_gnb_cu_ue_f1ap_id(ue_index);
    if (gnb_cu_ue_f1ap_id == gnb_cu_ue_f1ap_id_t::invalid) {
      continue;
    }
    ue_id_c        ueid;
    ue_id_gnb_du_s ueid_gnb_du{};
    ueid_gnb_du.gnb_cu_ue_f1ap_id = gnb_cu_ue_f1ap_id_to_uint(gnb_cu_ue_f1ap_id);
    ueid_gnb_du.ran_ue_id_present = false;
    ueid.set_gnb_du_ue_id()       = ueid_gnb_du;
    ues.push_back(ueid);
  }

  return true;
}

bool e2sm_kpm_du_meas_provider_impl::get_ues_matching_test_conditions(
    const asn1::e2sm::matching_ue_cond_per_sub_list_l& matching_ue_cond_list,
    std::vector<asn1::e2sm::ue_id_c>&                  ues)
{
  // TODO: add test condition checking, now return all UEs
  for (const auto& ue : ue_aggr_rlc_metrics) {
    du_ue_index_t       ue_index          = to_du_ue_index(ue.first);
    gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = f1ap_ue_id_provider.get_gnb_cu_ue_f1ap_id(ue_index);
    if (gnb_cu_ue_f1ap_id == gnb_cu_ue_f1ap_id_t::invalid) {
      continue;
    }
    ue_id_c        ueid;
    ue_id_gnb_du_s ueid_gnb_du{};
    ueid_gnb_du.gnb_cu_ue_f1ap_id = gnb_cu_ue_f1ap_id_to_uint(gnb_cu_ue_f1ap_id);
    ueid_gnb_du.ran_ue_id_present = false;
    ueid.set_gnb_du_ue_id()       = ueid_gnb_du;
    ues.push_back(ueid);
  }

  return true;
}

bool e2sm_kpm_du_meas_provider_impl::get_meas_data(const asn1::e2sm::meas_type_c&               meas_type,
                                                   const asn1::e2sm::label_info_list_l          label_info_list,
                                                   const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                                   const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                                   std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  metric_meas_getter_func_ptr metric_meas_getter_func;
  auto                        it = supported_metrics.find(meas_type.meas_name().to_string().c_str());
  if (it == supported_metrics.end()) {
    logger.debug("Metric {} not supported.", meas_type.meas_name().to_string());
    return false;
  }
  metric_meas_getter_func = it->second.func;
  srsran_assert(metric_meas_getter_func != nullptr, "Metric getter function cannot be empty.");
  return (this->*metric_meas_getter_func)(label_info_list, ues, cell_global_id, items);
}

bool e2sm_kpm_du_meas_provider_impl::handle_no_meas_data_available(
    const std::vector<asn1::e2sm::ue_id_c>&        ues,
    std::vector<asn1::e2sm::meas_record_item_c>&   items,
    asn1::e2sm::meas_record_item_c::types::options value_type)
{
  if (ues.empty()) {
    // Fill with zero if E2 Node Measurement (Report Style 1)
    meas_record_item_c meas_record_item;
    if (value_type == asn1::e2sm::meas_record_item_c::types::options::integer) {
      meas_record_item.set_integer() = 0;
    } else if (value_type == asn1::e2sm::meas_record_item_c::types::options::real) {
      meas_record_item.set_real();
      meas_record_item.real().value = 0;
    } else if (value_type == asn1::e2sm::meas_record_item_c::types::options::not_satisfied) {
      meas_record_item.set_not_satisfied();
    } else {
      meas_record_item.set_no_value();
    }
    items.push_back(meas_record_item);
    return true;
  }
  return false;
}

bool e2sm_kpm_du_meas_provider_impl::get_cqi(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = ue_metrics.cqi_stats.get_nof_observations() > 0
                                       ? static_cast<uint64_t>(std::roundf(ue_metrics.cqi_stats.get_mean()))
                                       : 0;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_rsrp(const asn1::e2sm::label_info_list_l          label_info_list,
                                              const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                              const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                              std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = (int)ue_metrics.pusch_snr_db;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_rsrq(const asn1::e2sm::label_info_list_l          label_info_list,
                                              const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                              const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                              std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = (int)ue_metrics.pusch_snr_db;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_prb_avail_dl(const asn1::e2sm::label_info_list_l          label_info_list,
                                                      const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                                      const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                                      std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: RRU.PrbAvailDl supports only NO_LABEL label.");
    return meas_collected;
  }
  int mean_dl_prbs_used =
      std::accumulate(last_ue_metrics.begin(),
                      last_ue_metrics.end(),
                      0,
                      [](size_t sum, const scheduler_ue_metrics& metric) { return sum + metric.tot_dl_prbs_used; }) /
      nof_dl_slots;

  for (size_t i = 0; i < std::max(ues.size(), size_t(1)); ++i) {
    meas_record_item_c meas_record_item;
    meas_record_item.set_integer() = (nof_cell_prbs - mean_dl_prbs_used);
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_prb_avail_ul(const asn1::e2sm::label_info_list_l          label_info_list,
                                                      const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                                      const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                                      std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: RRU.PrbAvailUl supports only NO_LABEL label.");
    return meas_collected;
  }
  int mean_ul_prbs_used =
      std::accumulate(last_ue_metrics.begin(),
                      last_ue_metrics.end(),
                      0,
                      [](size_t sum, const scheduler_ue_metrics& metric) { return sum + metric.tot_ul_prbs_used; }) /
      nof_ul_slots;

  for (size_t i = 0; i < std::max(ues.size(), size_t(1)); ++i) {
    meas_record_item_c meas_record_item;
    meas_record_item.set_integer() = (nof_cell_prbs - mean_ul_prbs_used);
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_prb_used_dl(const asn1::e2sm::label_info_list_l          label_info_list,
                                                     const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                                     const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                                     std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: RRU.PrbUsedDl supports only NO_LABEL label.");
    return meas_collected;
  }

  if (ues.empty()) {
    double dl_prbs_used =
        std::accumulate(last_ue_metrics.begin(),
                        last_ue_metrics.end(),
                        0,
                        [](size_t sum, const scheduler_ue_metrics& metric) { return sum + metric.tot_dl_prbs_used; }) /
        nof_dl_slots;
    meas_record_item_c meas_record_item;
    meas_record_item.set_integer() = dl_prbs_used;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  for (auto& ue : ues) {
    gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
    uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
    meas_record_item_c  meas_record_item;
    meas_record_item.set_integer() = last_ue_metrics[ue_idx].mean_dl_prbs_used;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_prb_used_ul(const asn1::e2sm::label_info_list_l          label_info_list,
                                                     const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                                     const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                                     std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: RRU.PrbUsedUl supports only NO_LABEL label.");
    return meas_collected;
  }

  if (ues.empty()) {
    double ul_prbs_used =
        std::accumulate(last_ue_metrics.begin(),
                        last_ue_metrics.end(),
                        0,
                        [](size_t sum, const scheduler_ue_metrics& metric) { return sum + metric.tot_ul_prbs_used; }) /
        nof_ul_slots;
    meas_record_item_c meas_record_item;
    meas_record_item.set_integer() = ul_prbs_used;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  for (auto& ue : ues) {
    gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
    uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
    meas_record_item_c  meas_record_item;
    meas_record_item.set_integer() = last_ue_metrics[ue_idx].mean_ul_prbs_used;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_prb_use_perc_dl(const asn1::e2sm::label_info_list_l          label_info_list,
                                                         const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                                         const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                                         std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: RRU.PrbTotDl supports only NO_LABEL label.");
    return meas_collected;
  }

  if (ues.empty()) {
    double mean_dl_prbs_used =
        std::accumulate(last_ue_metrics.begin(),
                        last_ue_metrics.end(),
                        0,
                        [](size_t sum, const scheduler_ue_metrics& metric) { return sum + metric.tot_dl_prbs_used; }) /
        nof_dl_slots;
    meas_record_item_c meas_record_item;
    meas_record_item.set_integer() = mean_dl_prbs_used * 100 / nof_cell_prbs;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  for (auto& ue : ues) {
    gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
    uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
    meas_record_item_c  meas_record_item;
    meas_record_item.set_integer() = last_ue_metrics[ue_idx].mean_dl_prbs_used * 100 / nof_cell_prbs;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_prb_use_perc_ul(const asn1::e2sm::label_info_list_l          label_info_list,
                                                         const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                                         const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                                         std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: RRU.PrbTotUl supports only NO_LABEL label.");
    return meas_collected;
  }
  if (ues.empty()) {
    double mean_ul_prbs_used =
        std::accumulate(last_ue_metrics.begin(),
                        last_ue_metrics.end(),
                        0,
                        [](size_t sum, const scheduler_ue_metrics& metric) { return sum + metric.tot_ul_prbs_used; }) /
        nof_ul_slots;
    meas_record_item_c meas_record_item;
    meas_record_item.set_integer() = mean_ul_prbs_used * 100 / nof_cell_prbs;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  for (auto& ue : ues) {
    gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
    uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
    meas_record_item_c  meas_record_item;
    meas_record_item.set_integer() = last_ue_metrics[ue_idx].mean_ul_prbs_used * 100 / nof_cell_prbs;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  return meas_collected;
}
bool e2sm_kpm_du_meas_provider_impl::get_delay_ul(const asn1::e2sm::label_info_list_l          label_info_list,
                                                  const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                                  const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                                  std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::real);
  }
  scheduler_ue_metrics ue_metrics = last_ue_metrics[0];
  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: DRB.AirIfDelayUl supports only NO_LABEL label.");
    return meas_collected;
  }
  meas_record_item_c meas_record_item;
  meas_record_item.set_real().value = ue_metrics.ul_delay_ms;
  items.push_back(meas_record_item);
  meas_collected = true;
  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_prach_cell_count(const asn1::e2sm::label_info_list_l          label_info_list,
                                                          const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                                          const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                                          std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }

  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: RACH.PreambleDedCell supports only NO_LABEL label.");
    return meas_collected;
  }
  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = nof_ded_cell_preambles;
  items.push_back(meas_record_item);

  return meas_collected;
}

float e2sm_kpm_du_meas_provider_impl::bytes_to_kbits(float value)
{
  constexpr unsigned nof_bits_per_byte = 8;
  return (nof_bits_per_byte * value / 1e3);
}

bool e2sm_kpm_du_meas_provider_impl::get_drb_dl_mean_throughput(const asn1::e2sm::label_info_list_l     label_info_list,
                                                                const std::vector<asn1::e2sm::ue_id_c>& ues,
                                                                const std::optional<asn1::e2sm::cgi_c>  cell_global_id,
                                                                std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (ue_aggr_rlc_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: DRB.UEThpDl supports only NO_LABEL label.");
    return meas_collected;
  }
  double                       seconds = 1;
  std::map<uint16_t, unsigned> ue_throughput;
  for (auto& ue : ue_aggr_rlc_metrics) {
    size_t num_pdu_bytes_with_segmentation;
    switch (ue.second.front().tx.tx_low.mode) {
      case rlc_mode::um_bidir:
      case rlc_mode::um_unidir_dl:
        // get average from queue
        num_pdu_bytes_with_segmentation =
            std::accumulate(ue.second.begin(), ue.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
              return sum + metric.tx.tx_low.mode_specific.um.num_pdu_bytes_with_segmentation;
            });
        num_pdu_bytes_with_segmentation /= ue.second.size();
        break;
      case rlc_mode::am:
        num_pdu_bytes_with_segmentation =
            std::accumulate(ue.second.begin(), ue.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
              return sum + metric.tx.tx_low.mode_specific.am.num_pdu_bytes_with_segmentation;
            });
        num_pdu_bytes_with_segmentation /= ue.second.size();
        break;
      default:
        num_pdu_bytes_with_segmentation = 0;
    }
    auto num_pdu_bytes_no_segmentation =
        std::accumulate(ue.second.begin(), ue.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
          return sum + metric.tx.tx_low.num_pdu_bytes_no_segmentation;
        });
    num_pdu_bytes_no_segmentation /= ue.second.size();
    seconds = (float)std::chrono::duration_cast<std::chrono::milliseconds>(ue.second.back().metrics_period).count() /
              (float)1000;
    ue_throughput[ue.first] = bytes_to_kbits(num_pdu_bytes_no_segmentation + num_pdu_bytes_with_segmentation) / seconds;
  }
  if (ues.empty()) {
    meas_record_item_c meas_record_item;
    int                total_throughput = 0;
    for (auto& ue : ue_throughput) {
      total_throughput += ue.second;
    }
    meas_record_item.set_integer() = total_throughput;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  for (auto& ue : ues) {
    meas_record_item_c  meas_record_item;
    gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
    uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
    if (ue_throughput.count(ue_idx) == 0) {
      meas_record_item.set_no_value();
      items.push_back(meas_record_item);
      meas_collected = true;
      continue;
    }
    meas_record_item.set_integer() = ue_throughput[ue_idx];
    items.push_back(meas_record_item);
    meas_collected = true;
  }
  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_drb_ul_mean_throughput(const asn1::e2sm::label_info_list_l     label_info_list,
                                                                const std::vector<asn1::e2sm::ue_id_c>& ues,
                                                                const std::optional<asn1::e2sm::cgi_c>  cell_global_id,
                                                                std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (ue_aggr_rlc_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: DRB.UEThpUl supports only NO_LABEL label.");
    return meas_collected;
  }

  double                       seconds = 1;
  std::map<uint16_t, unsigned> ue_throughput;
  for (auto& ue : ue_aggr_rlc_metrics) {
    auto num_pdu_bytes =
        std::accumulate(ue.second.begin(), ue.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
          return sum + metric.rx.num_pdu_bytes;
        });
    num_pdu_bytes /= ue.second.size();
    seconds = (float)std::chrono::duration_cast<std::chrono::milliseconds>(ue.second.back().metrics_period).count() /
              (float)1000;
    ue_throughput[ue.first] = bytes_to_kbits(num_pdu_bytes) / seconds; // unit is kbps
  }
  if (ues.empty()) {
    meas_record_item_c meas_record_item;
    int                total_throughput = 0;
    for (auto& ue : ue_throughput) {
      total_throughput += ue.second;
    }
    meas_record_item.set_integer() = total_throughput;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  for (auto& ue : ues) {
    meas_record_item_c  meas_record_item;
    gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
    uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
    if (ue_throughput.count(ue_idx) == 0) {
      meas_record_item.set_no_value();
      items.push_back(meas_record_item);
      meas_collected = true;
      continue;
    }
    meas_record_item.set_integer() = ue_throughput[ue_idx];
    items.push_back(meas_record_item);
    meas_collected = true;
  }
  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_drb_ul_success_rate(const asn1::e2sm::label_info_list_l     label_info_list,
                                                             const std::vector<asn1::e2sm::ue_id_c>& ues,
                                                             const std::optional<asn1::e2sm::cgi_c>  cell_global_id,
                                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (ue_aggr_rlc_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: DRB.PacketSuccessRateUlgNBUu supports only NO_LABEL label.");
    return meas_collected;
  }
  if (cell_global_id.has_value()) {
    logger.debug("Metric: DRB.PacketSuccessRateUlgNBUu currently does not support cell_global_id filter.");
  }
  if (ues.empty()) {
    // E2 level measurements.
    meas_record_item_c meas_record_item;
    float              success_rate    = 0;
    uint32_t           total_lost_pdus = 0;
    uint32_t           total_pdus      = 0;
    for (auto& ue_metric : ue_aggr_rlc_metrics) {
      // rlc_metrics& rlc_metric = ue_metric.second;
      total_lost_pdus += std::accumulate(
          ue_metric.second.begin(), ue_metric.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
            return sum + metric.rx.num_lost_pdus;
          });
      total_pdus += std::accumulate(ue_metric.second.begin(),
                                    ue_metric.second.end(),
                                    0,
                                    [](size_t sum, const rlc_metrics& metric) { return sum + metric.rx.num_pdus; });
    }
    if (total_pdus) {
      success_rate = 1.0 * (total_pdus - total_lost_pdus) / total_pdus;
    }
    uint32_t success_rate_int      = success_rate * 100;
    meas_record_item.set_integer() = success_rate_int;
    items.push_back(meas_record_item);
    meas_collected = true;
  }

  for (auto& ue : ues) {
    meas_record_item_c  meas_record_item;
    gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
    uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
    if (ue_aggr_rlc_metrics.count(ue_idx) == 0) {
      meas_record_item.set_no_value();
      items.push_back(meas_record_item);
      meas_collected = true;
      continue;
    }
    float success_rate    = 0;
    float total_lost_pdus = 0;
    float total_pdus      = 0;
    auto  ue_metric       = ue_aggr_rlc_metrics[ue_idx];
    total_lost_pdus +=
        std::accumulate(ue_metric.begin(), ue_metric.end(), 0, [](size_t sum, const rlc_metrics& metric) {
          return sum + metric.rx.num_lost_pdus;
        });
    total_pdus += std::accumulate(ue_metric.begin(), ue_metric.end(), 0, [](size_t sum, const rlc_metrics& metric) {
      return sum + metric.rx.num_pdus;
    });

    if (total_pdus) {
      success_rate = 1.0 * (total_pdus - total_lost_pdus) / total_pdus;
    }
    uint32_t success_rate_int      = success_rate * 100;
    meas_record_item.set_integer() = success_rate_int;
    items.push_back(meas_record_item);
    meas_collected = true;
  }
  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_drb_rlc_packet_drop_rate_dl(
    const asn1::e2sm::label_info_list_l          label_info_list,
    const std::vector<asn1::e2sm::ue_id_c>&      ues,
    const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
    std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (ue_aggr_rlc_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }

  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: DRB.RlcPacketDropRateDl supports only NO_LABEL label.");
    return meas_collected;
  }

  if (cell_global_id.has_value()) {
    logger.debug("Metric: DRB.RlcPacketDropRateDl currently does not support cell_global_id filter.");
  }

  if (ues.empty()) {
    // E2 level measurements.
    meas_record_item_c meas_record_item;
    float              drop_rate          = 0;
    uint32_t           total_dropped_sdus = 0;
    uint32_t           total_tx_num_sdus  = 0;
    for (auto& rlc_metric : ue_aggr_rlc_metrics) {
      total_dropped_sdus += std::accumulate(
          rlc_metric.second.begin(), rlc_metric.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
            return sum + metric.tx.tx_high.num_dropped_sdus + metric.tx.tx_high.num_discarded_sdus;
          });
      total_tx_num_sdus += std::accumulate(
          rlc_metric.second.begin(), rlc_metric.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
            return sum + metric.tx.tx_high.num_sdus;
          });
    }
    if (total_tx_num_sdus) {
      drop_rate = 1.0 * total_dropped_sdus / total_tx_num_sdus;
    }
    uint32_t drop_rate_int         = drop_rate * 100;
    meas_record_item.set_integer() = drop_rate_int;
    items.push_back(meas_record_item);
    meas_collected = true;
  } else {
    // UE level measurements.
    for (auto& ue : ues) {
      meas_record_item_c  meas_record_item;
      gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
      uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
      if (ue_aggr_rlc_metrics.count(ue_idx) == 0) {
        meas_record_item.set_no_value();
        items.push_back(meas_record_item);
        meas_collected = true;
        continue;
      }
      float    drop_rate = 0;
      uint32_t total_dropped_sdus =
          std::accumulate(ue_aggr_rlc_metrics[ue_idx].begin(),
                          ue_aggr_rlc_metrics[ue_idx].end(),
                          0,
                          [](size_t sum, const rlc_metrics& metric) {
                            return sum + metric.tx.tx_high.num_dropped_sdus + metric.tx.tx_high.num_discarded_sdus;
                          });
      uint32_t total_tx_num_sdus =
          std::accumulate(ue_aggr_rlc_metrics[ue_idx].begin(),
                          ue_aggr_rlc_metrics[ue_idx].end(),
                          0,
                          [](size_t sum, const rlc_metrics& metric) { return sum + metric.tx.tx_high.num_sdus; });
      if (total_tx_num_sdus) {
        drop_rate = 1.0 * total_dropped_sdus / total_tx_num_sdus;
      }
      uint32_t drop_rate_int         = drop_rate * 100;
      meas_record_item.set_integer() = drop_rate_int;
      items.push_back(meas_record_item);
      meas_collected = true;
    }
  }
  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_drb_rlc_sdu_transmitted_volume_dl(
    const asn1::e2sm::label_info_list_l          label_info_list,
    const std::vector<asn1::e2sm::ue_id_c>&      ues,
    const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
    std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (ue_aggr_rlc_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }

  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: DRB.RlcSduTransmittedVolumeDL supports only NO_LABEL label.");
    return false;
  }

  if (cell_global_id.has_value()) {
    logger.debug("Metric: DRB.RlcSduTransmittedVolumeDL currently does not support cell_global_id filter.");
  }

  if (ues.empty()) {
    // E2 level measurements.
    meas_record_item_c meas_record_item;
    size_t             total_tx_num_sdu_bytes = 0;
    for (auto& rlc_metric : ue_aggr_rlc_metrics) {
      total_tx_num_sdu_bytes += std::accumulate(
          rlc_metric.second.begin(), rlc_metric.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
            return sum + metric.tx.tx_high.num_sdu_bytes;
          });
    }
    meas_record_item.set_integer() = total_tx_num_sdu_bytes * 8 / 1000; // unit is kbit
    items.push_back(meas_record_item);
    meas_collected = true;
  } else {
    // UE level measurements.
    for (auto& ue : ues) {
      meas_record_item_c  meas_record_item;
      gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
      uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
      if (ue_aggr_rlc_metrics.count(ue_idx) == 0) {
        meas_record_item.set_no_value();
        items.push_back(meas_record_item);
        meas_collected = true;
        continue;
      }
      int num_sdu_bytes =
          std::accumulate(ue_aggr_rlc_metrics[ue_idx].begin(),
                          ue_aggr_rlc_metrics[ue_idx].end(),
                          0,
                          [](size_t sum, const rlc_metrics& metric) { return sum + metric.tx.tx_high.num_sdu_bytes; });
      meas_record_item.set_integer() = num_sdu_bytes * 8 / 1000; // unit is kbit
      items.push_back(meas_record_item);
      meas_collected = true;
    }
  }
  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_drb_rlc_sdu_transmitted_volume_ul(
    const asn1::e2sm::label_info_list_l          label_info_list,
    const std::vector<asn1::e2sm::ue_id_c>&      ues,
    const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
    std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (ue_aggr_rlc_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }

  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: DRB.RlcSduTransmittedVolumeUL supports only NO_LABEL label.");
    return meas_collected;
  }

  if (cell_global_id.has_value()) {
    logger.debug("Metric: DRB.RlcSduTransmittedVolumeUL currently does not support cell_global_id filter.");
  }

  if (ues.empty()) {
    // E2 level measurements.
    meas_record_item_c meas_record_item;
    size_t             total_rx_num_sdu_bytes = 0;
    for (auto& rlc_metric : ue_aggr_rlc_metrics) {
      total_rx_num_sdu_bytes += std::accumulate(
          rlc_metric.second.begin(), rlc_metric.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
            return sum + metric.rx.num_sdu_bytes;
          });
    }
    meas_record_item.set_integer() = total_rx_num_sdu_bytes * 8 / 1000; // unit is kbit
    items.push_back(meas_record_item);
    meas_collected = true;
  } else {
    // UE level measurements.
    for (auto& ue : ues) {
      meas_record_item_c  meas_record_item;
      gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
      uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
      if (ue_aggr_rlc_metrics.count(ue_idx) == 0) {
        meas_record_item.set_no_value();
        items.push_back(meas_record_item);
        meas_collected = true;
        continue;
      }
      int num_sdu_bytes =
          std::accumulate(ue_aggr_rlc_metrics[ue_idx].begin(),
                          ue_aggr_rlc_metrics[ue_idx].end(),
                          0,
                          [](size_t sum, const rlc_metrics& metric) { return sum + metric.rx.num_sdu_bytes; });
      meas_record_item.set_integer() = num_sdu_bytes * 8 / 1000; // unit is kbit
      items.push_back(meas_record_item);
      meas_collected = true;
    }
  }
  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_drb_dl_rlc_sdu_latency(const asn1::e2sm::label_info_list_l     label_info_list,
                                                                const std::vector<asn1::e2sm::ue_id_c>& ues,
                                                                const std::optional<asn1::e2sm::cgi_c>  cell_global_id,
                                                                std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (ue_aggr_rlc_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::real);
  }

  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: DRB.RlcSduDelayDl supports only NO_LABEL label.");
    return meas_collected;
  }

  if (ues.empty()) {
    meas_record_item_c meas_record_item;
    float              av_ue_sdu_latency_us = 0;
    for (auto& rlc_metric : ue_aggr_rlc_metrics) {
      int tot_num_of_pulled_sdus = std::accumulate(
          rlc_metric.second.begin(), rlc_metric.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
            return sum + metric.tx.tx_low.num_of_pulled_sdus;
          });
      int tot_sum_sdu_latency_us = std::accumulate(
          rlc_metric.second.begin(), rlc_metric.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
            return sum + metric.tx.tx_low.sum_sdu_latency_us;
          });
      if (tot_num_of_pulled_sdus && tot_sum_sdu_latency_us) {
        av_ue_sdu_latency_us += (float)tot_sum_sdu_latency_us / (float)tot_num_of_pulled_sdus;
      }
    }
    if (av_ue_sdu_latency_us) {
      meas_record_item.set_real();
      meas_record_item.real().value = av_ue_sdu_latency_us / ue_aggr_rlc_metrics.size();
      items.push_back(meas_record_item);
      meas_collected = true;
    } else {
      logger.warning("Invalid RLC SDU latency value.");
      return meas_collected;
    }
  } else {
    for (auto& ue : ues) {
      meas_record_item_c  meas_record_item;
      gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
      uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
      if (ue_aggr_rlc_metrics.count(ue_idx) == 0) {
        meas_record_item.set_no_value();
        items.push_back(meas_record_item);
        meas_collected = true;
        continue;
      }
      int tot_sdu_latency_us = std::accumulate(
          ue_aggr_rlc_metrics[ue_idx].begin(),
          ue_aggr_rlc_metrics[ue_idx].end(),
          0,
          [](size_t sum, const rlc_metrics& metric) { return sum + metric.tx.tx_low.sum_sdu_latency_us; });
      int tot_num_sdus =
          std::accumulate(ue_aggr_rlc_metrics[ue_idx].begin(),
                          ue_aggr_rlc_metrics[ue_idx].end(),
                          0,
                          [](size_t sum, const rlc_metrics& metric) { return sum + metric.tx.tx_high.num_sdus; });
      if (tot_sdu_latency_us) {
        meas_record_item.set_real();
        meas_record_item.real().value = tot_sdu_latency_us / tot_num_sdus;
        items.push_back(meas_record_item);
        meas_collected = true;
      } else {
        logger.warning("Invalid RLC SDU latency value.");
      }
    }
  }
  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_drb_ul_rlc_sdu_latency(const asn1::e2sm::label_info_list_l     label_info_list,
                                                                const std::vector<asn1::e2sm::ue_id_c>& ues,
                                                                const std::optional<asn1::e2sm::cgi_c>  cell_global_id,
                                                                std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool meas_collected = false;
  if (ue_aggr_rlc_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::real);
  }

  if ((label_info_list.size() > 1 or
       (label_info_list.size() == 1 and not label_info_list[0].meas_label.no_label_present))) {
    logger.debug("Metric: DRB.RlcDelayUl supports only NO_LABEL label.");
    return meas_collected;
  }

  if (ues.empty()) {
    meas_record_item_c meas_record_item;
    float              av_ue_sdu_latency_us = 0;
    for (auto& rlc_metric : ue_aggr_rlc_metrics) {
      int tot_num_sdus = std::accumulate(
          rlc_metric.second.begin(), rlc_metric.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
            return sum + metric.rx.num_sdus;
          });
      int tot_sdu_latency_us = std::accumulate(
          rlc_metric.second.begin(), rlc_metric.second.end(), 0, [](size_t sum, const rlc_metrics& metric) {
            return sum + metric.rx.sdu_latency_us;
          });
      if (tot_num_sdus && tot_sdu_latency_us) {
        av_ue_sdu_latency_us += (float)tot_sdu_latency_us / (float)tot_num_sdus;
      }
    }
    if (av_ue_sdu_latency_us) {
      meas_record_item.set_real();
      meas_record_item.real().value = (float)av_ue_sdu_latency_us / ue_aggr_rlc_metrics.size();
      items.push_back(meas_record_item);
      meas_collected = true;
    } else {
      logger.warning("Invalid RLC SDU latency value.");
      return meas_collected;
    }
  } else {
    for (auto& ue : ues) {
      meas_record_item_c  meas_record_item;
      gnb_cu_ue_f1ap_id_t gnb_cu_ue_f1ap_id = int_to_gnb_cu_ue_f1ap_id(ue.gnb_du_ue_id().gnb_cu_ue_f1ap_id);
      uint32_t            ue_idx            = f1ap_ue_id_provider.get_ue_index(gnb_cu_ue_f1ap_id);
      if (ue_aggr_rlc_metrics.count(ue_idx) == 0) {
        meas_record_item.set_no_value();
        items.push_back(meas_record_item);
        meas_collected = true;
        continue;
      }
      int tot_sdu_latency =
          std::accumulate(ue_aggr_rlc_metrics[ue_idx].begin(),
                          ue_aggr_rlc_metrics[ue_idx].end(),
                          0,
                          [](size_t sum, const rlc_metrics& metric) { return sum + metric.rx.sdu_latency_us; });
      int tot_num_sdus =
          std::accumulate(ue_aggr_rlc_metrics[ue_idx].begin(),
                          ue_aggr_rlc_metrics[ue_idx].end(),
                          0,
                          [](size_t sum, const rlc_metrics& metric) { return sum + metric.rx.num_sdus; });
      if (tot_sdu_latency) {
        meas_record_item.set_real();
        meas_record_item.real().value = tot_sdu_latency / tot_num_sdus;
        items.push_back(meas_record_item);
        meas_collected = true;
      } else {
        logger.warning("Invalid RLC SDU latency value.");
      }
    }
  }
  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_brate_dl(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_real().value = ue_metrics.dl_brate_kbps;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_brate_ul(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_real().value = ue_metrics.ul_brate_kbps;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_mcs_dl(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = (int) ue_metrics.dl_mcs.to_uint();
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_mcs_ul(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = (int)ue_metrics.ul_mcs.to_uint();
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_pusch_snr(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = (int)ue_metrics.pusch_snr_db;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_ri(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  // [issue] Improve the handling of std::optional
  meas_record_item.set_integer() = ue_metrics.ri_stats.get_nof_observations() > 0
                                       ? static_cast<uint64_t>(std::roundf(ue_metrics.ri_stats.get_mean()))
                                       : 0;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_pci(const asn1::e2sm::label_info_list_l          label_info_list,
                                              const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                              const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                              std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = (uint16_t) ue_metrics.pci;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_rnti(const asn1::e2sm::label_info_list_l          label_info_list,
                                              const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                              const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                              std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = (uint16_t) ue_metrics.rnti;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_ta(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  // [issue] Improve the handling of std::optional
  meas_record_item.set_real().value = ue_metrics.last_ta.has_value() ? ue_metrics.last_ta.value().to_seconds() : 0;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_phr(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  // [issue] Improve the handling of std::optional
  meas_record_item.set_integer() = ue_metrics.last_phr.has_value() ? ue_metrics.last_phr.value() : 0;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_nof_ok_ul(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = ue_metrics.ul_nof_ok;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_nof_ok_dl(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = ue_metrics.dl_nof_ok;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_nof_nok_dl(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = ue_metrics.dl_nof_nok;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_nof_nok_ul(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = ue_metrics.ul_nof_nok;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_bsr(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = ue_metrics.bsr;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}

bool e2sm_kpm_du_meas_provider_impl::get_dl_bs(const asn1::e2sm::label_info_list_l          label_info_list,
                                             const std::vector<asn1::e2sm::ue_id_c>&      ues,
                                             const std::optional<asn1::e2sm::cgi_c>       cell_global_id,
                                             std::vector<asn1::e2sm::meas_record_item_c>& items)
{
  bool                 meas_collected = false;
  if (last_ue_metrics.empty()) {
    return handle_no_meas_data_available(ues, items, asn1::e2sm::meas_record_item_c::types::options::integer);
  }
  scheduler_ue_metrics ue_metrics     = last_ue_metrics[0];

  meas_record_item_c meas_record_item;
  meas_record_item.set_integer() = ue_metrics.dl_bs;
  items.push_back(meas_record_item);
  meas_collected = true;

  return meas_collected;
}


