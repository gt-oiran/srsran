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
#include "srsran/support/stats.h"
#include <optional>

namespace srsran {

/// \brief Snapshot of the metrics for a UE.
struct scheduler_ue_metrics {
  pci_t                        pci; // Physical Cell Identifier
  unsigned                     nof_prbs; // Number of PRBs
  rnti_t                       rnti; // Radio Network Temporary Identifier (UE identifier)
  sch_mcs_index                dl_mcs; // Dl Modulation and coding scheme (0-28)
  double                       dl_prbs_used; // Number of dl used PRBs
  double                       dl_brate_kbps; // Ul bitrate
  unsigned                     dl_nof_ok; // Dl Number of packets successfully sent
  unsigned                     dl_nof_nok; // Dl Number of packets dropped
  float                        pusch_snr_db; // PUSCH SINR (Signal-to-Interference-plus-Noise Ratio)
  float                        pusch_rsrp_db; // Reference Signal Received Power
  float                        pucch_snr_db; 
  sch_mcs_index                ul_mcs; // Ul Modulation and coding scheme (0-28)
  double                       ul_prbs_used; // Number of ul used PRBs
  double                       ul_brate_kbps; // Ul bitrate
  unsigned                     ul_nof_ok; // Ul Number of packets successfully sent
  unsigned                     ul_nof_nok; // Ul Number of packets dropped
  unsigned                     bsr; // Buffer Status Report, data waiting to be transmitted as reported by the UE (bytes)
  unsigned                     dl_bs; // Downlink Buffer Status, data waiting to be transmitted as reported by the gNB (bytes)
  std::optional<phy_time_unit> last_ta; // Timing Advance in microseconds
  std::optional<int>           last_phr; // Power Headroom as reported by the UE

  /// CQI statistics over the metrics report interval.
  sample_statistics<unsigned> cqi_stats; // Channel Quality Indicator reported by the UE (1-15)
  /// RI statistics over the metrics report interval.
  sample_statistics<unsigned> ri_stats; // Rank Indicator as reported by the UE
};

/// \brief Snapshot of the metrics for a cell and its UEs.
struct scheduler_cell_metrics {
  /// Latency histogram number of bins.
  constexpr static unsigned latency_hist_bins = 10;
  /// Distance between histogram bins.
  constexpr static unsigned nof_usec_per_bin = 50;

  unsigned                                nof_error_indications = 0;
  std::chrono::microseconds               average_decision_latency{0};
  std::array<unsigned, latency_hist_bins> latency_histogram{0};
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
