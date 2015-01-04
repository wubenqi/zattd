// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_MSG_READ_ACK_H_
#define PROTO_MSG_READ_ACK_H_

#include "proto/base_teamtalk_pdu.h"

class MsgReadAck : public BaseTeamTalkPDU {
public:
  MsgReadAck() :
    BaseTeamTalkPDU(MESSAGE_MSG_READ_ACK) {}

  virtual ~MsgReadAck() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, request_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, from_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, to_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, client_type);
 
  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() +
      sizeof(request_id_) + sizeof(from_user_id_) + sizeof(to_user_id_) + sizeof(client_type_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 request_id_;
  uint32 from_user_id_;
  uint32 to_user_id_;
  uint32 client_type_;
};


#endif // PROTO_MSG_READ_ACK_H_
