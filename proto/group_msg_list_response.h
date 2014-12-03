// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_GROUP_MSG_LIST_RESPONSE_H_
#define PROTO_GROUP_MSG_LIST_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class GroupMsgListResponse : public BaseTeamTalkPDU {
public:
  GroupMsgListResponse() :
    BaseTeamTalkPDU(MESSAGE_GROUP_MSG_LIST_RESPONSE, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~GroupMsgListResponse() {
    STLDeleteElements(&msg_list_);
  }

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, request_cmd_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, group_id);
  PROPERTY_OBJECTPTR_ARRAY_DECLARE(GroupMsg, msg_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const;

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 	req_user_id_;
  uint32 	request_cmd_id_;
  uint32	group_id_;
  std::vector<GroupMsg*> msg_list_;
};

#endif // PROTO_GROUP_MSG_LIST_RESPONSE_H_
