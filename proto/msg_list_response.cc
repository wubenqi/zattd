// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/msg_list_response.h"  

bool MsgListResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> request_cmd_id_
    >> from_user_id_
    >> to_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(ServerMsg, msg_list_);

  return !is.Fail();
}

bool MsgListResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << request_cmd_id_
    << from_user_id_
    << to_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(msg_list_);

  return !os->Fail();
}
