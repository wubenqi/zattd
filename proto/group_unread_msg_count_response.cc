// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_unread_msg_count_response.h"  

bool GroupUnreadMsgCountResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> req_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(GroupUnreadMsgCount, group_unread_list_);

  return !is.Fail();
}

bool GroupUnreadMsgCountResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << req_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(group_unread_list_);

  return !os->Fail();
}
