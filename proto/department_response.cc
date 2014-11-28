// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/department_response.h"

bool DepartmentResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> req_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(DepartmentInfo, depart_list_);

  return !is.Fail();
}

bool DepartmentResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << req_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(depart_list_);

  return !os->Fail();
}
