// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_MSG_LIST_RESPONSE_H_
#define PROTO_MSG_LIST_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class MsgListResponse : public BaseTeamTalkPDU {
public:
  MsgListResponse() :
    BaseTeamTalkPDU(MESSAGE_MSG_LIST_RESPONSE, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~MsgListResponse() {
    STLDeleteElements(&msg_list_);
  }

  PROPERTY_BASIC_TYPE_DECLARE(uint32, request_cmd_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, from_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, to_user_id);
  PROPERTY_OBJECTPTR_ARRAY_DECLARE(ServerMsg, msg_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() +
      sizeof(request_cmd_id_) + sizeof(from_user_id_) + sizeof(to_user_id_) +
      CalculateContainerByteSize(msg_list_);
  }

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 	request_cmd_id_;
  uint32	from_user_id_;
  uint32	to_user_id_;
  std::vector<ServerMsg*> msg_list_;
};

#endif // PROTO_MSG_LIST_RESPONSE_H_

