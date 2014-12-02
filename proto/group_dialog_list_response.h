// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_GROUP_DIALOG_LIST_RESPONSE_H_
#define PROTO_GROUP_DIALOG_LIST_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class GroupDialogListResponse : public BaseTeamTalkPDU {
public:
  GroupDialogListResponse() :
    BaseTeamTalkPDU(MESSAGE_GROUP_DIALOG_LIST_RESPONSE, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~GroupDialogListResponse() {
    STLDeleteElements(&group_list_);
  }

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_OBJECTPTR_ARRAY_DECLARE(GroupInfo, group_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const;

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 		req_user_id_;
  std::vector<GroupInfo*> group_list_;
};

#endif
