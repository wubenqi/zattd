// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_unread_msg_count_response.h"  

namespace {

uint32 ByteSize(const GroupUnreadMsgCount& group_unread_msg_count) {
  return sizeof(group_unread_msg_count.group_id) + sizeof(group_unread_msg_count.unread_msg_count);
}

bool ParseFromByteStream(GroupUnreadMsgCount* group_unread_msg_count, const net::ByteStream& is) {
  is >> group_unread_msg_count->group_id
    >> group_unread_msg_count->unread_msg_count;

  return !is.Fail();
}

bool SerializeToByteStream(const GroupUnreadMsgCount& group_unread_msg_count, net::ByteStream* os) {
  (*os) << group_unread_msg_count.group_id
    << group_unread_msg_count.unread_msg_count;

  return !os->Fail();
}

}

uint32 GroupUnreadMsgCountResponse::ByteSize() const {
  uint32 size = BaseTeamTalkPDU::ByteSize();
  size += sizeof(req_user_id_);
  CalculateContainerByteSize2(size, group_unread_list_);
  return size;
}

bool GroupUnreadMsgCountResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> req_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(GroupUnreadMsgCount, group_unread_list_);

  return !is.Fail();
}

bool GroupUnreadMsgCountResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << req_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(group_unread_list_);

  return !os->Fail();
}
