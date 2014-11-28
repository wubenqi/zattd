// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_create_normal_group_notify.h"

bool GroupCreateNormalGroupNotify::ParseFromByteStream(const net::ByteStream& is) {
  is >> group_id_;

  is.ReadString(group_name_);
  is.ReadString(avatar_name_);

  PARSE_BASICTYPE_ARRAY_IMPLICIT(uint32, user_list_);

  return !is.Fail();
}

bool GroupCreateNormalGroupNotify::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << group_id_;

  os->WriteString(group_name_);
  os->WriteString(avatar_name_);

  SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(user_list_);

  return !os->Fail();
}
