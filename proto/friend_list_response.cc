// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/friend_list_response.h"

namespace {

uint32 ByteSize(const FriendInfo& friend_info) {
  return sizeof(friend_info.friend_user_id) + sizeof(friend_info.updated);
}

bool ParseFromByteStream(FriendInfo* friend_info, const net::ByteStream& is) {
  is >> friend_info->friend_user_id
    >> friend_info->updated;

  return !is.Fail();
}

bool SerializeToByteStream(const FriendInfo& friend_info, net::ByteStream* os) {
  (*os) << friend_info.friend_user_id
    << friend_info.updated;

  return !os->Fail();
}

}

uint32 FriendListResponse::ByteSize() const {
  uint32 size = BaseTeamTalkPDU::ByteSize();
  size += sizeof(from_user_id_);
  CalculateContainerByteSize2(size, friend_lists_);
  return size;
}

bool FriendListResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> from_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(FriendInfo, friend_lists_);

  return !is.Fail();
}

bool FriendListResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << from_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(friend_lists_);

  return !os->Fail();
}
