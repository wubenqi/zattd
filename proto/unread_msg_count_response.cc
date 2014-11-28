// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/unread_msg_count_response.h"  

bool UnreadMsgCountResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> to_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(UserUnreadMsgCount, user_unread_list_);

  return !is.Fail();
}

bool UnreadMsgCountResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << to_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(user_unread_list_);

  return !os->Fail();
}
