// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_ALL_USER_RESPONSE_H_
#define PROTO_ALL_USER_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class AllUserResponse : public BaseTeamTalkPDU {
public:
  AllUserResponse() :
      BaseTeamTalkPDU(MESSAGE_ALL_USER_RESPONSE, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~AllUserResponse() {
    STLDeleteElements(&user_info_list_);
  }

  //////////////////////////////////////////////////////////////////////////
  PROPERTY_BASIC_TYPE_DECLARE(uint32, from_user_id);
  PROPERTY_OBJECTPTR_ARRAY_DECLARE(UserInfo, user_info_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const;

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 from_user_id_;
  std::vector<UserInfo*> user_info_list_;
};

#endif // PROTO_ALL_USER_REQUEST_H_
