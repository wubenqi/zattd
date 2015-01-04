// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/msg_data.h"

bool MsgData::ParseFromByteStream(const base::ByteStream& is) {
  is >> request_id_
    >> from_user_id_
    >> to_user_id_
    >> create_time_
    >> msg_type_;
  is.ReadString(msg_data_);

  return !is.Fail();
}

bool MsgData::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << request_id_
    << from_user_id_
    << to_user_id_
    << create_time_
    << msg_type_;
  os->WriteString(msg_data_);

  return !os->Fail();
}
