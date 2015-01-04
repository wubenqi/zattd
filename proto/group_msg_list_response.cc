// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/group_msg_list_response.h"  

namespace {

uint32 ByteSize(const GroupMsg& group_msg) {
  return sizeof(group_msg.from_user_id) +
    sizeof(group_msg.create_time) +
    SIZEOF_STRING(group_msg.msg_content);
}

bool ParseFromByteStream(GroupMsg* group_msg, const base::ByteStream& is) {
  is >> group_msg->from_user_id
    >> group_msg->create_time;
  is.ReadString(group_msg->msg_content);

  return !is.Fail();
}

bool SerializeToByteStream(const GroupMsg& group_msg, base::ByteStream* os) {
  (*os) << group_msg.from_user_id
    << group_msg.create_time;
  os->WriteString(group_msg.msg_content);

  return !os->Fail();
}

}

uint32 GroupMsgListResponse::ByteSize() const {
  uint32 size = BaseTeamTalkPDU::ByteSize();
  size += sizeof(req_user_id_) + sizeof(request_cmd_id_) + sizeof(group_id_);
  CalculateContainerByteSize2(size, msg_list_);
  return size;
}

bool GroupMsgListResponse::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_
    >> request_cmd_id_
    >> group_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(GroupMsg, msg_list_);

  return !is.Fail();
}

bool GroupMsgListResponse::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << req_user_id_
    << request_cmd_id_
    << group_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(msg_list_);

  return !os->Fail();
}
