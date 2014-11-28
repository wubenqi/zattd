// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/db_write_response.h"

bool DBWriteResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> request_id_
    >> result_
    >> request_pdu_type_
    >> from_id_
    >> to_id_;

  return !is.Fail();
}

bool DBWriteResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << request_id_
    << result_
    << request_pdu_type_
    << from_id_
    << to_id_;

  return !os->Fail();
}

