// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_change_member_request.h"

bool GroupChangeMemberRequest::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_
    >> req_user_id_
    >> group_id_;

  PARSE_BASICTYPE_ARRAY_IMPLICIT(uint32, user_list_);

  return !is.Fail();
}

bool GroupChangeMemberRequest::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << change_type_
    << req_user_id_
    << group_id_;

  SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(user_list_);

  return !os->Fail();
}
