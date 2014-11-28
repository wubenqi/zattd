// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_GROUP_CHANGE_MEMBER_REQUEST_H_
#define PROTO_GROUP_CHANGE_MEMBER_REQUEST_H_

#include "proto/base_teamtalk_pdu.h"

class GroupChangeMemberRequest : public BaseTeamTalkPDU {
public:
  GroupChangeMemberRequest() :
    BaseTeamTalkPDU(MESSAGE_GROUP_CHANGE_MEMBER_REQUEST, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~GroupChangeMemberRequest() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, change_type);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, group_id);
  PROPERTY_BASIC_TYPE_ARRAY_DECLARE(uint32, user_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() +
      sizeof(change_type_) +
      sizeof(req_user_id_) +
      sizeof(group_id_) +
      CalculateContainerByteSize(user_list_);
  }

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 change_type_;
  uint32 req_user_id_;
  uint32 group_id_;
  std::vector<uint32> user_list_;
};

#endif // PROTO_GROUP_CHANGE_MEMBER_REQUEST_H_



