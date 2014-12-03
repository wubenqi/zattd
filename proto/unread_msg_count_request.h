// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_UNREAD_MSG_COUNT_REQUEST_H_
#define PROTO_UNREAD_MSG_COUNT_REQUEST_H_

#include "proto/base_teamtalk_pdu.h"

class UnreadMsgCountRequest : public BaseTeamTalkPDU {
public:
  UnreadMsgCountRequest() :
    BaseTeamTalkPDU(MESSAGE_UNREAD_MSG_COUNT_REQUEST, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~UnreadMsgCountRequest() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, client_type);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + sizeof(user_id_) + sizeof(client_type_);
  }

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 user_id_;
  uint32 client_type_;
};

#endif // PROTO_UNREAD_MSG_COUNT_REQUEST_H_
