// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_dialog_list_response.h"

namespace {

uint32 ByteSize(const GroupInfo& group_info) {
  return sizeof(group_info.group_id) +
    SIZEOF_STRING(group_info.group_name) +
    SIZEOF_STRING(group_info.group_avatar) +
    sizeof(group_info.group_type) +
    sizeof(group_info.group_creator_id) +
    sizeof(group_info.group_updated) +
    CalculateContainerByteSize(group_info.group_memeber_list);
}
//
//is >> m_group_list[i].group_id;
//m_group_list[i].group_name = is.ReadString(m_group_list[i].group_name_len);
//m_group_list[i].group_avatar = is.ReadString(m_group_list[i].group_avatar_len);
//is >> m_group_list[i].group_type;
//is >> m_group_list[i].group_creator_id;
//if (m_pdu_header.command_id == IM_PDU_TYPE_GROUP_DIALOG_LIST_RESPONSE) {
//  is >> m_group_list[i].group_updated;
//} else {
//  m_group_list[i].group_updated = 0;
//}
//
//uint32_t user_cnt;
//uint32_t user_id;
//is >> user_cnt;
//for (uint32_t j = 0; j < user_cnt; j++) {
//  is >> user_id;
//  m_group_list[i].group_memeber_list.push_back(user_id);
//}


bool SerializeToByteStream(const GroupInfo& group_info,  net::ByteStream* os) {
  (*os) << group_info.group_id;
  os->WriteString(group_info.group_name);
  os->WriteString(group_info.group_avatar);
  (*os) << group_info.group_type
    << group_info.group_creator_id
    << group_info.group_updated;
  SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(group_info.group_memeber_list);

  return !os->Fail();
}

}

uint32 GroupDialogListResponse::ByteSize() const {
  uint32 size = BaseTeamTalkPDU::ByteSize() + sizeof(req_user_id_) + sizeof(uint32);
  for (size_t i=0; i<group_list_.size(); ++i) {
    size += ::ByteSize(*group_list_[i]);
  }
  return size;
  // return BaseTeamTalkPDU::ByteSize() + sizeof(req_user_id_) + CalculateContainerByteSize(group_list_);
}

bool GroupDialogListResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> req_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(GroupInfo, group_list_);

  return !is.Fail();
}

bool GroupDialogListResponse::SerializeToByteStream(net::ByteStream* os) const {
  uint32 size = group_list_.size();
  (*os) << req_user_id_
    << size;

  for (size_t i=0; i<size; ++i) {
    ::SerializeToByteStream(*group_list_[i], os);
  }

  // SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(group_list_);

  return !os->Fail();
}

