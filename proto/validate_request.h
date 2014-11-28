// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_VALIDATE_REQUEST_H_
#define PROTO_VALIDATE_REQUEST_H_

#include "proto/base_teamtalk_pdu.h"

// #define PROTO_BASIC_TYPE_SIZEOF()

class ValidateRequest : public BaseTeamTalkPDU {
public:
  ValidateRequest() :
    BaseTeamTalkPDU(MESSAGE_VALIDATE_REQUEST, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~ValidateRequest() {}

  PROPERTY_OBJECT_DECLARE(std::string, user_name);
  PROPERTY_OBJECT_DECLARE(std::string, password);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + SIZEOF_STRING(user_name_) + SIZEOF_STRING(password_);
  }

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  std::string user_name_;
  std::string password_;
};

#endif // PROTO_VALIDATE_REQUEST_H_
