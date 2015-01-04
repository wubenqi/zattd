// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_GROUP_USER_LIST_RESPONSE_H_
#define PROTO_GROUP_USER_LIST_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class GroupUserListResponse : public BaseTeamTalkPDU {
public:
  GroupUserListResponse() :
    BaseTeamTalkPDU(MESSAGE_GROUP_USER_LIST_RESPONSE, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~GroupUserListResponse() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, group_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, result);
  PROPERTY_OBJECT_DECLARE(std::string, group_name);
  PROPERTY_OBJECT_DECLARE(std::string, group_avatar);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, group_creator_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, group_type);
  PROPERTY_BASIC_TYPE_ARRAY_DECLARE(uint32, user_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const;

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32	req_user_id_;
  uint32	group_id_;
  // 0--success, other--group not exist
  // the following fields only return when result = 0;
  uint32	result_;	
  std::string group_name_;
  std::string group_avatar_;
  uint32 	group_type_;
  uint32 	group_creator_id_;
  std::vector<uint32> user_list_;
};

#endif
