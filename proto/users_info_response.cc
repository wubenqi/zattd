// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/users_info_response.h"

bool UsersInfoResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> from_user_id_;
  PARSE_OBJECTPTR_ARRAY_IMPLICIT(UserInfo, user_info_list_);

  return !is.Fail();
}

bool UsersInfoResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << from_user_id_;
  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(user_info_list_);

  return !os->Fail();
}
