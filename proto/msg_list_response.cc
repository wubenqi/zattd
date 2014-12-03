// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/msg_list_response.h"  

namespace {

uint32 ByteSize(const ServerMsg& server_msg) {
  return sizeof(server_msg.from_user_id) +
    SIZEOF_STRING(server_msg.from_name) +
    SIZEOF_STRING(server_msg.from_nick_name) +
    SIZEOF_STRING(server_msg.from_avatar_url) +
    sizeof(server_msg.create_time) +
    sizeof(server_msg.msg_type) +
    SIZEOF_STRING(server_msg.msg_data);
}

bool ParseFromByteStream(ServerMsg* server_msg, const net::ByteStream& is) {
  is >> server_msg->from_user_id;
  is.ReadString(server_msg->from_name);
  is.ReadString(server_msg->from_nick_name);
  is.ReadString(server_msg->from_avatar_url);
  is >> server_msg->create_time
    >> server_msg->msg_type;
  is.ReadString(server_msg->msg_data);

  return !is.Fail();
}

bool SerializeToByteStream(const ServerMsg& server_msg, net::ByteStream* os) {
  (*os) << server_msg.from_user_id;
  os->WriteString(server_msg.from_name);
  os->WriteString(server_msg.from_nick_name);
  os->WriteString(server_msg.from_avatar_url);
  (*os) << server_msg.create_time
    << server_msg.msg_type;
  os->WriteString(server_msg.msg_data);

  return !os->Fail();
}

}

uint32 MsgListResponse::ByteSize() const {
  uint32 size = BaseTeamTalkPDU::ByteSize();
  size += sizeof(request_cmd_id_) + sizeof(from_user_id_) + sizeof(to_user_id_);
  CalculateContainerByteSize2(size, msg_list_);
  return size;
}


bool MsgListResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> request_cmd_id_
    >> from_user_id_
    >> to_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(ServerMsg, msg_list_);

  return !is.Fail();
}

bool MsgListResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << request_cmd_id_
    << from_user_id_
    << to_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(msg_list_);

  return !os->Fail();
}
