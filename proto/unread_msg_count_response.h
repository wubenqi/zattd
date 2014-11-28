// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_UNREAD_MSG_COUNT_RESPONSE_H_
#define PROTO_UNREAD_MSG_COUNT_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class UnreadMsgCountResponse : public BaseTeamTalkPDU {
public:
  UnreadMsgCountResponse() :
    BaseTeamTalkPDU(MESSAGE_UNREAD_MSG_COUNT_RESPONSE, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~UnreadMsgCountResponse() {
    STLDeleteElements(&user_unread_list_);
  }

  PROPERTY_BASIC_TYPE_DECLARE(uint32, to_user_id);
  PROPERTY_OBJECTPTR_ARRAY_DECLARE(UserUnreadMsgCount, user_unread_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + sizeof(to_user_id_) + CalculateContainerByteSize(user_unread_list_);
  }

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 to_user_id_;
  std::vector<UserUnreadMsgCount*> user_unread_list_;
};

#endif // PROTO_UNREAD_MSG_COUNT_RESPONSE_H_
