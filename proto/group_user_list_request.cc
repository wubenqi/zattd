// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_user_list_request.h"

bool GroupUserListRequest::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_
    >> group_id_;

  return !is.Fail();
}

bool GroupUserListRequest::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << req_user_id_
    << group_id_;

  return !os->Fail();
}
