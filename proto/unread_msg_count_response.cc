// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/unread_msg_count_response.h"  

namespace {

uint32 ByteSize(const UserUnreadMsgCount& user_unread_msg_count) {
  return sizeof(user_unread_msg_count.from_user_id) + sizeof(user_unread_msg_count.unread_msg_count);
}

bool ParseFromByteStream(UserUnreadMsgCount* user_unread_msg_count, const net::ByteStream& is) {
  is >> user_unread_msg_count->from_user_id
    >> user_unread_msg_count->unread_msg_count;

  return !is.Fail();
}

bool SerializeToByteStream(const UserUnreadMsgCount& user_unread_msg_count, net::ByteStream* os) {
  (*os) << user_unread_msg_count.from_user_id
    << user_unread_msg_count.unread_msg_count;

  return !os->Fail();
}

}

uint32 UnreadMsgCountResponse::ByteSize() const {
  uint32 size = BaseTeamTalkPDU::ByteSize();
  size += sizeof(to_user_id_);
  CalculateContainerByteSize2(size, user_unread_list_);
  return size;
}

bool UnreadMsgCountResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> to_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(UserUnreadMsgCount, user_unread_list_);

  return !is.Fail();
}

bool UnreadMsgCountResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << to_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(user_unread_list_);

  return !os->Fail();
}
