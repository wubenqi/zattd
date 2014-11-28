// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/friend_list_response.h"

bool FriendListResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> from_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(FriendInfo, friend_lists_);

  return !is.Fail();
}

bool FriendListResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << from_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(friend_lists_);

  return !os->Fail();
}
