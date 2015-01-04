// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/users_info_request.h"

bool UsersInfoRequest::ParseFromByteStream(const base::ByteStream& is) {
  uint32 user_id_list_size = 0;

  is >> from_user_id_;

  PARSE_BASICTYPE_ARRAY_IMPLICIT(uint32, user_id_list_);

  return !is.Fail();
}

bool UsersInfoRequest::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << from_user_id_;

  SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(user_id_list_);

  return !os->Fail();
}
