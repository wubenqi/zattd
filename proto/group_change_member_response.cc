// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_change_member_response.h"

uint32 GroupChangeMemberResponse::ByteSize() const {
  return BaseTeamTalkPDU::ByteSize() +
    sizeof(req_user_id_) +
    sizeof(result_) +
    sizeof(group_id_) +
    sizeof(change_type_) +
    CalculateContainerByteSize(user_list_);
}

bool GroupChangeMemberResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> req_user_id_
    >> result_
    >> group_id_
    >> change_type_;

  PARSE_BASICTYPE_ARRAY_IMPLICIT(uint32, user_list_);

  return !is.Fail();
}

bool GroupChangeMemberResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << req_user_id_
    << result_
    << group_id_
    << change_type_;

  SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(user_list_);

  return !os->Fail();
}
