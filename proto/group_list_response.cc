// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_list_response.h"

namespace {

static uint32 ByteSize(const GroupInfo& group_info) {
  return sizeof(group_info.group_id) +
    SIZEOF_STRING(group_info.group_name) +
    SIZEOF_STRING(group_info.group_avatar) +
    sizeof(group_info.group_type) +
    sizeof(group_info.group_creator_id) +
    // sizeof(group_info.group_updated) +
    CalculateContainerByteSize(group_info.group_memeber_list);
}

static bool ParseFromByteStream(GroupInfo* group_info, const base::ByteStream& is) {
  is >> group_info->group_id;
  is.ReadString(group_info->group_name);
  is.ReadString(group_info->group_avatar);
  is >> group_info->group_type
    >> group_info->group_creator_id;
    // >> group_info->group_updated;
  PARSE_BASICTYPE_ARRAY_IMPLICIT(uint32, group_info->group_memeber_list);

  return !is.Fail();
}

static bool SerializeToByteStream(const GroupInfo& group_info,  base::ByteStream* os) {
  (*os) << group_info.group_id;
  os->WriteString(group_info.group_name);
  os->WriteString(group_info.group_avatar);
  (*os) << group_info.group_type
    << group_info.group_creator_id;
  //  << group_info.group_updated;
  SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(group_info.group_memeber_list);

  return !os->Fail();
}

}

uint32 GroupListResponse::ByteSize() const {
  uint32 size = BaseTeamTalkPDU::ByteSize();
  size += sizeof(req_user_id_);
  CalculateContainerByteSize2(size, group_list_);
  return size;
}

bool GroupListResponse::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(GroupInfo, group_list_);

  return !is.Fail();
}

bool GroupListResponse::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << req_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(group_list_);

  return !os->Fail();
}

