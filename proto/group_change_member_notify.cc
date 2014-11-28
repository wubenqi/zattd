// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_change_member_notify.h"

bool GroupChangeMemberNotify::ParseFromByteStream(const net::ByteStream& is) {
  is >> group_id_;

  PARSE_BASICTYPE_ARRAY_IMPLICIT(uint32, user_list_);

  return !is.Fail();
}

bool GroupChangeMemberNotify::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << group_id_;

  SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(user_list_);

  return !os->Fail();
}
