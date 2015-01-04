// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_GROUP_HISTORY_MSG_REQUEST_H_
#define PROTO_GROUP_HISTORY_MSG_REQUEST_H_

#include "proto/base_teamtalk_pdu.h"

class GroupHistoryMsgRequest : public BaseTeamTalkPDU {
public:
  GroupHistoryMsgRequest() :
    BaseTeamTalkPDU(MESSAGE_HISTORY_MSG_REQUEST, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~GroupHistoryMsgRequest() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, group_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, msg_offset);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, msg_count);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() +
      sizeof(req_user_id_) + sizeof(group_id_) + sizeof(msg_offset_) + sizeof(msg_count_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 req_user_id_;
  uint32 group_id_;
  uint32 msg_offset_;
  uint32 msg_count_;
};

#endif // PROTO_HISTORY_LIST_REQUEST_H_
