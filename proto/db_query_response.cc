// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/db_query_response.h"

bool DBQueryResponse::ParseFromByteStream(const base::ByteStream& is) {
  is >> seq_no_
    >> user_id_;
  is.ReadString(result_data_);

  return !is.Fail();
}

bool DBQueryResponse::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << seq_no_
    << user_id_;
  os->WriteString(result_data_);

  return !os->Fail();
}
