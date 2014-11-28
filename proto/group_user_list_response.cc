// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_user_list_response.h"

bool GroupUserListResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> req_user_id_
    >> group_id_
    >> result_;
  is.ReadString(group_name_);
  is.ReadString(group_avatar_);
  is >> group_type_
    >> group_creator_id_;

  PARSE_BASICTYPE_ARRAY_IMPLICIT(uint32, user_list_);

  return !is.Fail();
}

bool GroupUserListResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << req_user_id_
    << group_id_
    << result_;

  os->WriteString(group_name_);
  os->WriteString(group_avatar_);

  (*os) << group_type_
    << group_creator_id_;

  SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(user_list_);

  return !os->Fail();
}
