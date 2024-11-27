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

#include "f1ap_test_message_validators.h"
#include "../../../lib/f1ap/asn1_helpers.h"
#include "../tests/test_doubles/rrc/rrc_test_message_validators.h"
#include "srsran/asn1/f1ap/common.h"
#include "srsran/asn1/f1ap/f1ap_pdu_contents.h"
#include "srsran/f1ap/f1ap_message.h"

using namespace srsran;
using namespace asn1::f1ap;

#define TRUE_OR_RETURN(cond)                                                                                           \
  if (not(cond))                                                                                                       \
    return false;

static bool is_packable(const f1ap_message& msg)
{
  byte_buffer   temp_pdu;
  asn1::bit_ref bref{temp_pdu};
  return msg.pdu.pack(bref) == asn1::SRSASN_SUCCESS;
}

bool srsran::test_helpers::is_init_ul_rrc_msg_transfer_valid(const f1ap_message&                       msg,
                                                             rnti_t                                    rnti,
                                                             const std::optional<nr_cell_global_id_t>& nci)
{
  TRUE_OR_RETURN(msg.pdu.type() == asn1::f1ap::f1ap_pdu_c::types_opts::init_msg);
  TRUE_OR_RETURN(msg.pdu.init_msg().proc_code == ASN1_F1AP_ID_INIT_UL_RRC_MSG_TRANSFER);
  const asn1::f1ap::init_ul_rrc_msg_transfer_s& rrcmsg = msg.pdu.init_msg().value.init_ul_rrc_msg_transfer();

  TRUE_OR_RETURN(to_rnti(rrcmsg->c_rnti) == rnti);

  if (nci.has_value() and cgi_from_asn1(rrcmsg->nr_cgi).value() != nci) {
    return false;
  }

  return true;
}

bool srsran::test_helpers::is_valid_dl_rrc_message_transfer(const f1ap_message& msg)
{
  TRUE_OR_RETURN(msg.pdu.type() == asn1::f1ap::f1ap_pdu_c::types_opts::init_msg);
  TRUE_OR_RETURN(msg.pdu.init_msg().proc_code == ASN1_F1AP_ID_DL_RRC_MSG_TRANSFER);
  TRUE_OR_RETURN(is_packable(msg));

  return true;
}

const byte_buffer& srsran::test_helpers::get_rrc_container(const f1ap_message& msg)
{
  if (msg.pdu.init_msg().proc_code == ASN1_F1AP_ID_UE_CONTEXT_SETUP) {
    return msg.pdu.init_msg().value.ue_context_setup_request()->rrc_container;
  }

  if (msg.pdu.init_msg().proc_code == ASN1_F1AP_ID_UE_CONTEXT_MOD) {
    return msg.pdu.init_msg().value.ue_context_mod_request()->rrc_container;
  }

  return msg.pdu.init_msg().value.dl_rrc_msg_transfer()->rrc_container;
}

byte_buffer srsran::test_helpers::get_du_to_cu_container(const f1ap_message& msg)
{
  if (msg.pdu.init_msg().proc_code == ASN1_F1AP_ID_INIT_UL_RRC_MSG_TRANSFER) {
    return msg.pdu.init_msg().value.init_ul_rrc_msg_transfer()->du_to_cu_rrc_container_present
               ? msg.pdu.init_msg().value.init_ul_rrc_msg_transfer()->du_to_cu_rrc_container.copy()
               : byte_buffer{};
  }
  return byte_buffer{};
}

bool srsran::test_helpers::is_valid_dl_rrc_message_transfer_with_msg4(const f1ap_message& msg)
{
  TRUE_OR_RETURN(is_valid_dl_rrc_message_transfer(msg));

  const asn1::f1ap::dl_rrc_msg_transfer_s& rrcmsg = msg.pdu.init_msg().value.dl_rrc_msg_transfer();
  TRUE_OR_RETURN(rrcmsg->srb_id <= srb_id_to_uint(srb_id_t::srb1));

  if (int_to_srb_id(rrcmsg->srb_id) == srb_id_t::srb0) {
    // RRC Setup.
    TRUE_OR_RETURN(not rrcmsg->old_gnb_du_ue_f1ap_id_present);
    TRUE_OR_RETURN(test_helpers::is_valid_rrc_setup(rrcmsg->rrc_container));

  } else if (int_to_srb_id(rrcmsg->srb_id) == srb_id_t::srb1) {
    // Remove PDCP header
    byte_buffer dl_dcch = rrcmsg->rrc_container.deep_copy().value();
    dl_dcch.trim_head(2);
    TRUE_OR_RETURN(test_helpers::is_valid_rrc_reestablishment(dl_dcch));

    // RRC Reestablishment.
    TRUE_OR_RETURN(rrcmsg->old_gnb_du_ue_f1ap_id_present);
    TRUE_OR_RETURN(rrcmsg->gnb_du_ue_f1ap_id != rrcmsg->old_gnb_du_ue_f1ap_id);
  }

  return true;
}

bool srsran::test_helpers::is_ul_rrc_msg_transfer_valid(const f1ap_message& msg, srb_id_t srb_id)
{
  if (not(msg.pdu.type() == asn1::f1ap::f1ap_pdu_c::types_opts::init_msg and
          msg.pdu.init_msg().proc_code == ASN1_F1AP_ID_UL_RRC_MSG_TRANSFER)) {
    return false;
  }
  const asn1::f1ap::ul_rrc_msg_transfer_s& rrcmsg = msg.pdu.init_msg().value.ul_rrc_msg_transfer();
  if (rrcmsg->srb_id != srb_id_to_uint(srb_id) or rrcmsg->rrc_container.empty()) {
    return false;
  }
  return true;
}

bool srsran::test_helpers::is_valid_ue_context_setup_request(const f1ap_message& msg)
{
  TRUE_OR_RETURN(msg.pdu.type() == asn1::f1ap::f1ap_pdu_c::types_opts::init_msg);
  TRUE_OR_RETURN(msg.pdu.init_msg().proc_code == ASN1_F1AP_ID_UE_CONTEXT_SETUP);
  TRUE_OR_RETURN(is_packable(msg));

  return true;
}

bool srsran::test_helpers::is_valid_ue_context_setup_request_with_ue_capabilities(const f1ap_message& msg)
{
  TRUE_OR_RETURN(is_valid_ue_context_setup_request(msg));
  TRUE_OR_RETURN(
      msg.pdu.init_msg().value.ue_context_setup_request()->cu_to_du_rrc_info.ue_cap_rat_container_list.size() > 0);
  return true;
}

bool srsran::test_helpers::is_ue_context_setup_response_valid(const f1ap_message& msg)
{
  if (not(msg.pdu.type() == asn1::f1ap::f1ap_pdu_c::types_opts::successful_outcome and
          msg.pdu.successful_outcome().proc_code == ASN1_F1AP_ID_UE_CONTEXT_SETUP)) {
    return false;
  }
  const asn1::f1ap::ue_context_setup_resp_s& resp = msg.pdu.successful_outcome().value.ue_context_setup_resp();
  if (not resp->drbs_setup_list_present) {
    return false;
  }
  return true;
}

bool srsran::test_helpers::is_valid_ue_context_modification_request(const f1ap_message& msg)
{
  TRUE_OR_RETURN(msg.pdu.type() == asn1::f1ap::f1ap_pdu_c::types_opts::init_msg);
  TRUE_OR_RETURN(msg.pdu.init_msg().proc_code == ASN1_F1AP_ID_UE_CONTEXT_MOD);
  TRUE_OR_RETURN(is_packable(msg));

  return true;
}

bool srsran::test_helpers::is_valid_ue_context_modification_response(const f1ap_message&    msg,
                                                                     ue_context_mod_context context)
{
  TRUE_OR_RETURN(msg.pdu.type() == asn1::f1ap::f1ap_pdu_c::types_opts::successful_outcome);
  TRUE_OR_RETURN(msg.pdu.successful_outcome().proc_code == ASN1_F1AP_ID_UE_CONTEXT_MOD);
  TRUE_OR_RETURN(is_packable(msg));

  const asn1::f1ap::ue_context_mod_resp_s& resp = msg.pdu.successful_outcome().value.ue_context_mod_resp();

  TRUE_OR_RETURN(resp->drbs_setup_mod_list_present == (resp->drbs_setup_mod_list.size() > 0));
  TRUE_OR_RETURN(resp->drbs_modified_list_present == (resp->drbs_modified_list.size() > 0));

  // Reestablishment case.
  if (context == ue_context_mod_context::reestablistment) {
    // See ORAN-WG5.C.1 6.10.1, intra-DU Reestablishment, UE Context Modification Response
    TRUE_OR_RETURN(not resp->drbs_setup_mod_list_present);
    for (const auto& drb : resp->drbs_modified_list) {
      TRUE_OR_RETURN(drb->drbs_modified_item().dl_up_tnl_info_to_be_setup_list.size() > 0);
      TRUE_OR_RETURN(drb->drbs_modified_item().ie_exts_present and
                     drb->drbs_modified_item().ie_exts.rlc_status_present and
                     drb->drbs_modified_item().ie_exts.rlc_status.reest_ind.value == reest_ind_opts::reestablished);
    }
  }

  return true;
}

bool srsran::test_helpers::is_valid_ue_context_modification_response(const f1ap_message&    resp_msg,
                                                                     const f1ap_message&    req_msg,
                                                                     ue_context_mod_context context)
{
  TRUE_OR_RETURN(is_valid_ue_context_modification_request(req_msg));
  TRUE_OR_RETURN(is_valid_ue_context_modification_response(resp_msg, context));

  const asn1::f1ap::ue_context_mod_request_s& mod_req  = req_msg.pdu.init_msg().value.ue_context_mod_request();
  const asn1::f1ap::ue_context_mod_resp_s&    mod_resp = resp_msg.pdu.successful_outcome().value.ue_context_mod_resp();
  TRUE_OR_RETURN(mod_req->drbs_to_be_setup_mod_list.size() ==
                 mod_resp->drbs_setup_mod_list.size() + mod_resp->drbs_failed_to_be_setup_mod_list.size());
  TRUE_OR_RETURN(mod_req->drbs_to_be_modified_list.size() ==
                 mod_resp->drbs_modified_list.size() + mod_resp->drbs_failed_to_be_modified_list.size());
  for (const auto& drb : mod_resp->drbs_setup_mod_list) {
    auto drb_req_it = std::find_if(
        mod_req->drbs_to_be_setup_mod_list.begin(), mod_req->drbs_to_be_setup_mod_list.end(), [&drb](const auto& e) {
          return drb->drbs_setup_mod_item().drb_id == e->drbs_to_be_setup_mod_item().drb_id;
        });
    TRUE_OR_RETURN(drb_req_it != mod_req->drbs_to_be_setup_mod_list.end());
    TRUE_OR_RETURN(drb->drbs_setup_mod_item().dl_up_tnl_info_to_be_setup_list.size() ==
                   drb_req_it->value().drbs_to_be_setup_mod_item().ul_up_tnl_info_to_be_setup_list.size());
  }

  return true;
}

bool srsran::test_helpers::is_valid_ue_context_release_command(const f1ap_message& msg)
{
  TRUE_OR_RETURN(msg.pdu.type() == asn1::f1ap::f1ap_pdu_c::types_opts::init_msg);
  TRUE_OR_RETURN(msg.pdu.init_msg().proc_code == ASN1_F1AP_ID_UE_CONTEXT_RELEASE);
  TRUE_OR_RETURN(is_packable(msg));

  return true;
}

bool srsran::test_helpers::is_valid_paging(const f1ap_message& msg)
{
  TRUE_OR_RETURN(msg.pdu.type() == asn1::f1ap::f1ap_pdu_c::types_opts::init_msg);
  TRUE_OR_RETURN(msg.pdu.init_msg().proc_code == ASN1_F1AP_ID_PAGING);
  TRUE_OR_RETURN(is_packable(msg));

  return true;
}
