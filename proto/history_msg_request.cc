// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/history_msg_request.h"

bool HistoryMsgRequest::ParseFromByteStream(const base::ByteStream& is) {
  is >> from_user_id_
    >> to_user_id_
    >> msg_offset_
    >> msg_count_;

  return !is.Fail();
}

bool HistoryMsgRequest::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << from_user_id_
    << to_user_id_
    << msg_offset_
    << msg_count_;

  return !os->Fail();
}
