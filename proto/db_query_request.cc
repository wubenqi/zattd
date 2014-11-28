// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/db_query_request.h"

bool DBQueryRequest::ParseFromByteStream(const net::ByteStream& is) {
  is >> seq_no_
    >> user_id_;
  is.ReadString(query_data_);

  return !is.Fail();
}

bool DBQueryRequest::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << seq_no_
    << user_id_;
  os->WriteString(query_data_);

  return !os->Fail();
}
