// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/department_request.h"

bool DeparmentRequest::ParseFromByteStream(const net::ByteStream& is) {
  is >> req_user_id_;

  return !is.Fail();
}

bool DeparmentRequest::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << req_user_id_;

  return !os->Fail();
}
