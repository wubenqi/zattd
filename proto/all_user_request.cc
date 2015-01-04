// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/all_user_request.h"

bool AllUserRequest::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_;

  return !is.Fail();
}

bool AllUserRequest::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << req_user_id_;

  return !os->Fail();
}
