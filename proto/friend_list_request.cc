// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/friend_list_request.h"

bool FriendListRequest::ParseFromByteStream(const base::ByteStream& is) {
  is >> user_id_;

  return !is.Fail();
}

bool FriendListRequest::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << user_id_;

  return !os->Fail();
}
