// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_list_response.h"

bool GroupListResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> req_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(GroupInfo, group_list_);

  return !is.Fail();
}

bool GroupListResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << req_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(group_list_);

  return !os->Fail();
}
