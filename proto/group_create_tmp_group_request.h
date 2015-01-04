// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_GROUP_CREATE_TMP_GROUP_REQUEST_H_
#define PROTO_GROUP_CREATE_TMP_GROUP_REQUEST_H_

#include "proto/base_teamtalk_pdu.h"

class GroupCreateTmpGroupRequest : public BaseTeamTalkPDU {
public:
  GroupCreateTmpGroupRequest() :
    BaseTeamTalkPDU(MESSAGE_GROUP_CREATE_TMP_GROUP_REQUEST, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~GroupCreateTmpGroupRequest() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_OBJECT_DECLARE(std::string, group_name);
  PROPERTY_OBJECT_DECLARE(std::string, group_avatar);
  PROPERTY_BASIC_TYPE_ARRAY_DECLARE(uint32, user_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() +
      sizeof(req_user_id_) +
      SIZEOF_STRING(group_name_) +
      SIZEOF_STRING(group_avatar_) +
      CalculateContainerByteSize(user_list_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 req_user_id_;
  std::string group_name_;
  std::string group_avatar_;
  std::vector<uint32> user_list_;
};

#endif // PROTO_GROUP_CREATE_TMP_GROUP_REQUEST_H_

