// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_create_tmp_group_request.h"

bool GroupCreateTmpGroupRequest::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_;

  is.ReadString(group_name_);
  is.ReadString(group_avatar_);

  PARSE_BASICTYPE_ARRAY_IMPLICIT(uint32, user_list_);

  return !is.Fail();
}

bool GroupCreateTmpGroupRequest::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << req_user_id_;

  os->WriteString(group_name_);
  os->WriteString(group_avatar_);

  SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(user_list_);

  return !os->Fail();
}
