// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_ALL_USER_REQUEST_H_
#define PROTO_ALL_USER_REQUEST_H_

#include "proto/base_teamtalk_pdu.h"

class AllUserRequest : public BaseTeamTalkPDU {
public:
  AllUserRequest() :
    BaseTeamTalkPDU(MESSAGE_ALL_USER_REQUEST, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~AllUserRequest() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + sizeof(req_user_id_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 req_user_id_;
};

#endif // PROTO_ALL_USER_REQUEST_H_
