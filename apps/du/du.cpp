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

#include "srsran/gtpu/gtpu_config.h"
#include "srsran/support/cpu_features.h"
#include "srsran/support/event_tracing.h"
#include "srsran/support/signal_handling.h"
#include "srsran/support/versioning/build_info.h"
#include "srsran/support/versioning/version.h"

#include "srsran/f1u/du/split_connector/f1u_split_connector_factory.h"
#include "srsran/gtpu/gtpu_demux_factory.h"

#include "srsran/support/io/io_broker_factory.h"

#include "adapters/f1_gateways.h"
#include "srsran/support/backtrace.h"
#include "srsran/support/config_parsers.h"

#include "du_appconfig.h"
#include "du_appconfig_cli11_schema.h"
#include "du_appconfig_translators.h"
#include "du_appconfig_validators.h"

#include "apps/services/worker_manager.h"
#include "apps/units/flexible_du/split_dynamic/dynamic_du_factory.h"

#include "apps/du/adapters/e2_gateways.h"
#include "apps/services/e2/e2_metric_connector_manager.h"
#include "srsran/e2/gateways/e2_connection_client.h"

// Include ThreadSanitizer (TSAN) options if thread sanitization is enabled.
// This include is not unused - it helps prevent false alarms from the thread sanitizer.
#include "du_appconfig_yaml_writer.h"

#include "srsran/support/tsan_options.h"

#include <atomic>

#include "apps/services/application_message_banners.h"
#include "apps/services/application_tracer.h"
#include "apps/services/buffer_pool/buffer_pool_manager.h"
#include "apps/services/core_isolation_manager.h"
#include "apps/services/metrics/metrics_manager.h"
#include "apps/services/metrics/metrics_notifier_proxy.h"
#include "apps/services/stdin_command_dispatcher.h"
#include "apps/units/flexible_du/du_high/du_high_config.h"
#include "apps/units/flexible_du/du_high/pcap_factory.h"
#include "apps/units/flexible_du/flexible_du_application_unit.h"

#include "srsran/du/du_power_controller.h"

#ifdef DPDK_FOUND
#include "srsran/hal/dpdk/dpdk_eal_factory.h"
#endif

using namespace srsran;

/// \file
/// \brief Application of a distributed unit (DU) that is split from the CU-CP and CU-UP via the F1 interface.

static std::string config_file;

/// Flag that indicates if the application is running or being shutdown.
static std::atomic<bool> is_app_running = {true};
/// Maximum number of configuration files allowed to be concatenated in the command line.
static constexpr unsigned MAX_CONFIG_FILES = 10;

static void populate_cli11_generic_args(CLI::App& app)
{
  fmt::memory_buffer buffer;
  format_to(buffer, "srsRAN 5G DU version {} ({})", get_version(), get_build_hash());
  app.set_version_flag("-v,--version", srsran::to_c_str(buffer));
  app.set_config("-c,", config_file, "Read config from file", false)->expected(1, MAX_CONFIG_FILES);
}

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

/// Function to call when an error is reported by the application.
static void app_error_report_handler()
{
  srslog::flush();
}

static void initialize_log(const std::string& filename)
{
  srslog::sink* log_sink = (filename == "stdout") ? srslog::create_stdout_sink() : srslog::create_file_sink(filename);
  if (log_sink == nullptr) {
    report_error("Could not create application main log sink.\n");
  }
  srslog::set_default_sink(*log_sink);
  srslog::init();
}

static void register_app_logs(const logger_appconfig& log_cfg, flexible_du_application_unit& du_app_unit)
{
  // Set log-level of app and all non-layer specific components to app level.
  for (const auto& id : {"ALL", "SCTP-GW", "IO-EPOLL", "UDP-GW", "PCAP"}) {
    auto& logger = srslog::fetch_basic_logger(id, false);
    logger.set_level(log_cfg.lib_level);
    logger.set_hex_dump_max_size(log_cfg.hex_max_size);
  }

  auto& app_logger = srslog::fetch_basic_logger("GNB", false);
  app_logger.set_level(srslog::basic_levels::info);
  app_services::application_message_banners::log_build_info(app_logger);
  app_logger.set_level(log_cfg.config_level);
  app_logger.set_hex_dump_max_size(log_cfg.hex_max_size);

  auto& config_logger = srslog::fetch_basic_logger("CONFIG", false);
  config_logger.set_level(log_cfg.config_level);
  config_logger.set_hex_dump_max_size(log_cfg.hex_max_size);

  auto& metrics_logger = srslog::fetch_basic_logger("METRICS", false);
  metrics_logger.set_level(log_cfg.metrics_level);
  metrics_logger.set_hex_dump_max_size(log_cfg.hex_max_size);

  auto& e2ap_logger = srslog::fetch_basic_logger("E2AP", false);
  e2ap_logger.set_level(log_cfg.e2ap_level);
  e2ap_logger.set_hex_dump_max_size(log_cfg.hex_max_size);

  // Register units logs.
  du_app_unit.on_loggers_registration();
}

int main(int argc, char** argv)
{
  // Set the application error handler.
  set_error_handler(app_error_report_handler);

  static constexpr std::string_view app_name = "DU";
  app_services::application_message_banners::announce_app_and_version(app_name);

  // Set interrupt and cleanup signal handlers.
  register_interrupt_signal_handler(interrupt_signal_handler);
  register_cleanup_signal_handler(cleanup_signal_handler);

  // Enable backtrace.
  enable_backtrace();

  // Setup and configure config parsing.
  CLI::App app("srsDU application");
  app.config_formatter(create_yaml_config_parser());
  app.allow_config_extras(CLI::config_extras_mode::error);
  // Fill the generic application arguments to parse.
  populate_cli11_generic_args(app);

  du_appconfig du_cfg;
  // Configure CLI11 with the DU application configuration schema.
  configure_cli11_with_du_appconfig_schema(app, du_cfg);

  auto du_app_unit = create_flexible_du_application_unit("du");
  du_app_unit->on_parsing_configuration_registration(app);

  // Set the callback for the app calling all the autoderivation functions.
  app.callback([&app, &du_cfg, &du_app_unit]() {
    autoderive_du_parameters_after_parsing(app, du_cfg);
    du_app_unit->on_configuration_parameters_autoderivation(app);
  });

  // Parse arguments.
  CLI11_PARSE(app, argc, argv);

  // Check the modified configuration.
  if (!validate_appconfig(du_cfg) ||
      !du_app_unit->on_configuration_validation((du_cfg.expert_execution_cfg.affinities.isolated_cpus)
                                                    ? du_cfg.expert_execution_cfg.affinities.isolated_cpus.value()
                                                    : os_sched_affinity_bitmask::available_cpus())) {
    report_error("Invalid configuration detected.\n");
  }

  // Set up logging.
  initialize_log(du_cfg.log_cfg.filename);
  register_app_logs(du_cfg.log_cfg, *du_app_unit);

  // Log input configuration.
  srslog::basic_logger& config_logger = srslog::fetch_basic_logger("CONFIG");
  if (config_logger.debug.enabled()) {
    YAML::Node node;
    fill_du_appconfig_in_yaml_schema(node, du_cfg);
    du_app_unit->dump_config(node);
    config_logger.debug("Input configuration (all values): \n{}", YAML::Dump(node));
  } else {
    config_logger.info("Input configuration (only non-default values): \n{}", app.config_to_str(false, false));
  }

  srslog::basic_logger&            du_logger = srslog::fetch_basic_logger("DU");
  app_services::application_tracer app_tracer;
  if (not du_cfg.log_cfg.tracing_filename.empty()) {
    app_tracer.enable_tracer(du_cfg.log_cfg.tracing_filename, du_logger);
  }

  app_services::core_isolation_manager core_isolation_mngr;
  if (du_cfg.expert_execution_cfg.affinities.isolated_cpus) {
    if (!core_isolation_mngr.isolate_cores(*du_cfg.expert_execution_cfg.affinities.isolated_cpus)) {
      report_error("Failed to isolate specified CPUs");
    }
  }

#ifdef DPDK_FOUND
  std::unique_ptr<dpdk::dpdk_eal> eal;
  if (du_cfg.hal_config) {
    // Prepend the application name in argv[0] as it is expected by EAL.
    eal = dpdk::create_dpdk_eal(std::string(argv[0]) + " " + du_cfg.hal_config->eal_args,
                                srslog::fetch_basic_logger("EAL", false));
  }
#endif

  // Setup size of byte buffer pool.
  app_services::buffer_pool_manager buffer_pool_service(du_cfg.buffer_pool_config);

  // Log CPU architecture.
  cpu_architecture_info::get().print_cpu_info(du_logger);

  // Check and log included CPU features and check support by current CPU
  if (cpu_supports_included_features()) {
    du_logger.debug("Required CPU features: {}", get_cpu_feature_info());
  } else {
    // Quit here until we complete selection of the best matching implementation for the current CPU at runtime.
    du_logger.error("The CPU does not support the required CPU features that were configured during compile time: {}",
                    get_cpu_feature_info());
    report_error("The CPU does not support the required CPU features that were configured during compile time: {}\n",
                 get_cpu_feature_info());
  }

  // Check some common causes of performance issues and print a warning if required.
  check_cpu_governor(du_logger);
  check_drm_kms_polling(du_logger);

  // Instantiate worker manager.
  worker_manager_config worker_manager_cfg;
  du_app_unit->fill_worker_manager_config(worker_manager_cfg);
  fill_du_worker_manager_config(worker_manager_cfg, du_cfg);

  worker_manager workers{worker_manager_cfg};

  // Set layer-specific pcap options.
  const auto& low_prio_cpu_mask = du_cfg.expert_execution_cfg.affinities.low_priority_cpu_cfg.mask;

  // Create IO broker.
  io_broker_config           io_broker_cfg(low_prio_cpu_mask);
  std::unique_ptr<io_broker> epoll_broker = create_io_broker(io_broker_type::epoll, io_broker_cfg);

  flexible_du_pcaps du_pcaps = create_du_pcaps(du_app_unit->get_du_high_unit_config().pcaps, workers);

  // Instantiate F1-C client gateway.
  std::unique_ptr<srs_du::f1c_connection_client> f1c_gw = create_f1c_client_gateway(
      du_cfg.f1ap_cfg.cu_cp_address, du_cfg.f1ap_cfg.bind_address, *epoll_broker, *du_pcaps.f1ap);

  // Create manager of timers for DU, which will be driven by the PHY slot ticks.
  timer_manager app_timers{256};

  // Create F1-U connector
  // TODO: Simplify this and use factory.
  gtpu_demux_creation_request du_f1u_gtpu_msg       = {};
  du_f1u_gtpu_msg.cfg.warn_on_drop                  = true;
  du_f1u_gtpu_msg.gtpu_pcap                         = du_pcaps.f1u.get();
  std::unique_ptr<gtpu_demux> du_f1u_gtpu_demux     = create_gtpu_demux(du_f1u_gtpu_msg);
  udp_network_gateway_config  du_f1u_gw_config      = {};
  du_f1u_gw_config.bind_address                     = du_cfg.nru_cfg.bind_address;
  du_f1u_gw_config.bind_port                        = GTPU_PORT;
  du_f1u_gw_config.reuse_addr                       = false;
  du_f1u_gw_config.pool_occupancy_threshold         = du_cfg.nru_cfg.pool_threshold;
  std::unique_ptr<srs_cu_up::ngu_gateway> du_f1u_gw = srs_cu_up::create_udp_ngu_gateway(
      du_f1u_gw_config,
      *epoll_broker,
      workers.get_du_high_executor_mapper(0).ue_mapper().mac_ul_pdu_executor(to_du_ue_index(0)));
  std::unique_ptr<srs_du::f1u_du_udp_gateway> du_f1u_conn = srs_du::create_split_f1u_gw(
      {du_f1u_gw.get(), du_f1u_gtpu_demux.get(), *du_pcaps.f1u, GTPU_PORT, du_cfg.nru_cfg.ext_addr});

  // Set up the JSON log channel used by metrics.
  srslog::sink& json_sink =
      srslog::fetch_udp_sink(du_cfg.metrics_cfg.addr, du_cfg.metrics_cfg.port, srslog::create_json_formatter());

  // Instantiate E2AP client gateway.
  std::unique_ptr<e2_connection_client> e2_gw =
      create_du_e2_client_gateway(du_cfg.e2_cfg, *epoll_broker, *du_pcaps.e2ap);

  app_services::metrics_notifier_proxy_impl metrics_notifier_forwarder;
  du_unit_dependencies                      du_dependencies;
  du_dependencies.workers            = &workers;
  du_dependencies.f1c_client_handler = f1c_gw.get();
  du_dependencies.f1u_gw             = du_f1u_conn.get();
  du_dependencies.timer_mng          = &app_timers;
  du_dependencies.mac_p              = du_pcaps.mac.get();
  du_dependencies.rlc_p              = du_pcaps.rlc.get();
  du_dependencies.e2_client_handler  = e2_gw.get();
  du_dependencies.json_sink          = &json_sink;
  du_dependencies.metrics_notifier   = &metrics_notifier_forwarder;

  auto du_inst_and_cmds = du_app_unit->create_flexible_du_unit(du_dependencies);
  // Only DU has metrics now.
  app_services::metrics_manager metrics_mngr(
      srslog::fetch_basic_logger("GNB"), *workers.metrics_hub_exec, du_inst_and_cmds.metrics);
  // Connect the forwarder to the metrics manager.
  metrics_notifier_forwarder.connect(metrics_mngr);

  srs_du::du& du_inst = *du_inst_and_cmds.unit;

  // Register the commands.
  app_services::stdin_command_dispatcher command_parser(*epoll_broker, du_inst_and_cmds.commands);

  // Start processing.
  du_inst.get_power_controller().start();
  {
    app_services::application_message_banners app_banner(app_name);

    while (is_app_running) {
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
  }

  // Stop DU activity.
  du_inst.get_power_controller().stop();

  du_logger.info("Closing PCAP files...");
  du_pcaps.close();
  du_logger.info("PCAP files successfully closed.");

  du_logger.info("Stopping executors...");
  workers.stop();
  du_logger.info("Executors closed successfully.");

  srslog::flush();

  return 0;
}
