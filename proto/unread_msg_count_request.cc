// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/unread_msg_count_request.h"

bool UnreadMsgCountRequest::ParseFromByteStream(const net::ByteStream& is) {
  is >> user_id_
    >> client_type_;

  return !is.Fail();
}

bool UnreadMsgCountRequest::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << user_id_
    << client_type_;

  return !os->Fail();
}
