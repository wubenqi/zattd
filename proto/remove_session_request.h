// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_REMOVE_SESSION_REQUEST_H_
#define PROTO_REMOVE_SESSION_REQUEST_H_

#include "proto/base_teamtalk_pdu.h"

class RemoveSessionRequest : public BaseTeamTalkPDU {
public:
  RemoveSessionRequest() :
    BaseTeamTalkPDU(MESSAGE_REMOVE_SESSION_REQUEST, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~RemoveSessionRequest() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, session_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, session_type);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + sizeof(req_user_id_) + sizeof(session_id_) + sizeof(session_type_);
  }

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 req_user_id_;
  uint32 session_id_;
  uint32 session_type_;
};

#endif // PROTO_REMOVE_SESSION_REQUEST_H_
