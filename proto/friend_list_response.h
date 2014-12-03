// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_HISTORY_LIST_RESPONSE_H_
#define PROTO_HISTORY_LIST_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class FriendListResponse : public BaseTeamTalkPDU {
public:
  FriendListResponse() :
    BaseTeamTalkPDU(MESSAGE_FRIEND_LIST_RESPONSE, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~FriendListResponse() {
    STLDeleteElements(&friend_lists_);
  }

   PROPERTY_BASIC_TYPE_DECLARE(uint32, from_user_id);
   PROPERTY_OBJECTPTR_ARRAY_DECLARE(FriendInfo, friend_lists);
// 
  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const;

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 from_user_id_;
  std::vector<FriendInfo*> friend_lists_;
};

#endif // PROTO_HISTORY_LIST_RESPONSE_H_
