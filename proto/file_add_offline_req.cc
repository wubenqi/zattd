// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/file_add_offline_req.h"

bool FileAddOfflineReq::ParseFromByteStream(const net::ByteStream& is) {
  is >> req_user_id_
    >> from_id_
    >> to_id_;

  is.ReadString(task_id_);
  is.ReadString(file_name_);

  is >> file_size_;

  return !is.Fail();
}

bool FileAddOfflineReq::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << req_user_id_
    << from_id_
    << to_id_;

  os->WriteString(task_id_);
  os->WriteString(file_name_);

  (*os) << file_size_;

  return !os->Fail();
}
