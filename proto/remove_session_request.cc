// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/remove_session_request.h"

bool RemoveSessionRequest::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_
    >> session_id_
    >> session_type_;

  return !is.Fail();
}

bool RemoveSessionRequest::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << req_user_id_
    << session_id_
    << session_type_;

  return !os->Fail();
}
