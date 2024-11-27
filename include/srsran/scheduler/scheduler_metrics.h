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

#pragma once

#include "srsran/adt/span.h"
#include "srsran/ran/pci.h"
#include "srsran/ran/phy_time_unit.h"
#include "srsran/ran/rnti.h"
#include "srsran/ran/sch/sch_mcs.h"
#include "srsran/ran/slot_point.h"
#include "srsran/support/stats.h"
#include <optional>

namespace srsran {

/// \brief Snapshot of the metrics for a UE.
struct scheduler_ue_metrics {
  pci_t                        pci;
  rnti_t                       rnti;
  sch_mcs_index                dl_mcs;
  unsigned                     tot_dl_prbs_used;
  double                       mean_dl_prbs_used;
  double                       dl_brate_kbps;
  unsigned                     dl_nof_ok;
  unsigned                     dl_nof_nok;
  float                        pusch_snr_db;
  float                        pusch_rsrp_db;
  float                        pucch_snr_db;
  sch_mcs_index                ul_mcs;
  unsigned                     tot_ul_prbs_used;
  double                       mean_ul_prbs_used;
  double                       ul_brate_kbps;
  double                       ul_delay_ms;
  unsigned                     ul_nof_ok;
  unsigned                     ul_nof_nok;
  unsigned                     bsr;
  unsigned                     dl_bs;
  std::optional<phy_time_unit> last_ta;
  std::optional<int>           last_phr;
  /// CQI statistics over the metrics report interval.
  sample_statistics<unsigned> cqi_stats; // Channel Quality Indicator reported by the UE (1-15)
  /// RI statistics over the metrics report interval.
  sample_statistics<unsigned> ri_stats;
};

/// \brief Event that occurred in the cell of the scheduler.
struct scheduler_cell_event {
  enum class event_type { ue_add, ue_reconf, ue_rem };

  slot_point slot;
  rnti_t     rnti = rnti_t::INVALID_RNTI;
  event_type type;
};

/// \brief Snapshot of the metrics for a cell and its UEs.
struct scheduler_cell_metrics {
  /// Latency histogram number of bins.
  static constexpr unsigned latency_hist_bins = 10;
  /// Distance between histogram bins.
  static constexpr unsigned nof_usec_per_bin = 50;
  /// Number of cell PRBs.
  unsigned nof_prbs = 0;
  /// Number of full downlink slots.
  unsigned nof_dl_slots = 0;
  /// Number of full uplink slots.
  unsigned nof_ul_slots = 0;
  /// Number of PRACH preambles detected.
  unsigned nof_prach_preambles = 0;

  unsigned                                nof_error_indications = 0;
  std::chrono::microseconds               average_decision_latency{0};
  std::array<unsigned, latency_hist_bins> latency_histogram{0};
  std::vector<scheduler_cell_event>       events;
  std::vector<scheduler_ue_metrics>       ue_metrics;
};

/// \brief Notifier interface used by scheduler to report metrics.
class scheduler_metrics_notifier
{
public:
  virtual ~scheduler_metrics_notifier() = default;

  /// \brief This method will be called periodically by the scheduler to report the latest UE metrics statistics.
  virtual void report_metrics(const scheduler_cell_metrics& report) = 0;
};

} // namespace srsran
