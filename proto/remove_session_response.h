// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_REMOVE_SESSION_RESPONSE_H_
#define PROTO_REMOVE_SESSION_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class RemoveSessionResponse : public BaseTeamTalkPDU {
public:
  RemoveSessionResponse() :
    BaseTeamTalkPDU(MESSAGE_REMOVE_SESSION_RESPONSE, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~RemoveSessionResponse() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, result);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, session_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, session_type);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + sizeof(req_user_id_) + sizeof(result_) + sizeof(session_id_) + sizeof(session_type_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 req_user_id_;
  uint32	result_;		// 0 - success, 1 - fail
  uint32 	session_id_;
  uint32	session_type_;	//
};

#endif // PROTO_REMOVE_SESSION_RESPONSE_H_
