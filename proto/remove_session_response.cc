// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/remove_session_response.h"

bool RemoveSessionResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> req_user_id_
    >> result_
    >> session_id_
    >> session_type_;

  return !is.Fail();
}

bool RemoveSessionResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << req_user_id_
    << result_
    << session_id_
    << session_type_;

  return !os->Fail();
}
