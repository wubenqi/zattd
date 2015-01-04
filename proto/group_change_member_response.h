// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_GROUP_CHANGE_MEMBER_RESPONSE_H_
#define PROTO_GROUP_CHANGE_MEMBER_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class GroupChangeMemberResponse : public BaseTeamTalkPDU {
public:
  GroupChangeMemberResponse() :
    BaseTeamTalkPDU(MESSAGE_GROUP_CHANGE_MEMBER_RESPONSE, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~GroupChangeMemberResponse() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, result);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, group_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, change_type);
  PROPERTY_BASIC_TYPE_ARRAY_DECLARE(uint32, user_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const;

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 req_user_id_;
  uint32 result_;
  uint32 group_id_;
  uint32 change_type_;
  std::vector<uint32> user_list_;
};

#endif // PROTO_GROUP_CREATE_TMP_GROUP_REQUEST_H_
