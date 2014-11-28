// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/msg_read_ack.h"

bool MsgReadAck::ParseFromByteStream(const net::ByteStream& is) {
  is >> request_id_
    >> from_user_id_
    >> to_user_id_;

  return !is.Fail();
}

bool MsgReadAck::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << request_id_
    << from_user_id_
    << to_user_id_;

  return !os->Fail();
}
