// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_VALIDATE_RESPONSE_H_
#define PROTO_VALIDATE_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class ValidateResponse : public BaseTeamTalkPDU {
public:
  ValidateResponse() :
    BaseTeamTalkPDU(MESSAGE_VALIDATE_RESPONSE, BaseAttachData::kAttachDataTypeDB),
    user_(NULL) {}

  virtual ~ValidateResponse() {
    if (user_) {
      delete user_;
      user_ = NULL;
    }
  }

  PROPERTY_OBJECT_DECLARE(std::string, user_name);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, result);
  PROPERTY_OBJECTPTR_DECLARE(UserInfo, user);

  virtual uint32 ByteSize() const;

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  std::string user_name_;
  uint32	result_;	    // 0 -- success, non-0 -- fail reason
  UserInfo* user_;		  // if result != 0, no this item
};

#endif // PROTO_VALIDATE_RESPONSE_H_
