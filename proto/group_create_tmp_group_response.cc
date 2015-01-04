// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_create_tmp_group_response.h"

uint32 GroupCreateTmpGroupResponse::ByteSize() const {
  return BaseTeamTalkPDU::ByteSize() +
    sizeof(req_user_id_) +
    sizeof(result_) +
    sizeof(group_id_) +
    SIZEOF_STRING(group_name_) +
    CalculateContainerByteSize(user_list_);
}

bool GroupCreateTmpGroupResponse::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_
    >> result_
    >> group_id_;

  is.ReadString(group_name_);

  PARSE_BASICTYPE_ARRAY_IMPLICIT(uint32, user_list_);

  return !is.Fail();
}

bool GroupCreateTmpGroupResponse::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << req_user_id_
    << result_
    << group_id_;

  os->WriteString(group_name_);

  SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(user_list_);

  return !os->Fail();
}
