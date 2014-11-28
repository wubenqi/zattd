// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_USER_INFO_REQUEST_H_
#define PROTO_USER_INFO_REQUEST_H_

#include "proto/base_teamtalk_pdu.h"

class UsersInfoRequest : public BaseTeamTalkPDU {
public:
  UsersInfoRequest() :
    BaseTeamTalkPDU(MESSAGE_USERS_INFO_REQUEST, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~UsersInfoRequest() {}

  //////////////////////////////////////////////////////////////////////////
  PROPERTY_BASIC_TYPE_DECLARE(uint32, from_user_id);
  PROPERTY_BASIC_TYPE_ARRAY_DECLARE(uint32, user_id_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + sizeof(from_user_id_) + CalculateContainerByteSize(user_id_list_);
  }

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 from_user_id_;
  std::vector<uint32> user_id_list_;
};

#endif // PROTO_USER_INFO_REQUEST_H_
