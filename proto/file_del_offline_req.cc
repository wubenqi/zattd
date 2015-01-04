// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/file_del_offline_req.h"

bool FileDelOfflineReq::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_
    >> from_id_
    >> to_id_;

  is.ReadString(task_id_);

  return !is.Fail();
}

bool FileDelOfflineReq::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << req_user_id_
    << from_id_
    << to_id_;

  os->WriteString(task_id_);

  return !os->Fail();
}
