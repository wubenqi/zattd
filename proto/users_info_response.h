// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_USER_INFO_RESPONSE_H_
#define PROTO_USER_INFO_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class UsersInfoResponse : public BaseTeamTalkPDU {
public:
  explicit UsersInfoResponse(uint32 message_type = MESSAGE_USERS_INFO_RESPONSE) :
    BaseTeamTalkPDU(message_type, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~UsersInfoResponse() {
    STLDeleteElements(&user_info_list_);
  }

  //////////////////////////////////////////////////////////////////////////
  PROPERTY_BASIC_TYPE_DECLARE(uint32, from_user_id);
  PROPERTY_OBJECTPTR_ARRAY_DECLARE(UserInfo, user_info_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + sizeof(from_user_id_) + CalculateContainerByteSize(user_info_list_);
  }

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 from_user_id_;
  std::vector<UserInfo*> user_info_list_;
};

#endif // PROTO_USER_INFO_RESPONSE_H_
