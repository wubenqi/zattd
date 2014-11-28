// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/unread_msg_request.h"

bool UnreadMsgRequest::ParseFromByteStream(const net::ByteStream& is) {
  is >> from_user_id_
    >> to_user_id_;

  return !is.Fail();
}

bool UnreadMsgRequest::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << from_user_id_
    << to_user_id_;

  return !os->Fail();
}
