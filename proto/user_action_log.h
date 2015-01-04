// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_USER_ACTION_LOG_H_
#define PROTO_USER_ACTION_LOG_H_

#include "proto/base_teamtalk_pdu.h"

class UserActionLog : public BaseTeamTalkPDU {
public:
  enum UserActionType {
    USER_ACTION_TYPE_LOGIN 	= 100,
    USER_ACTION_TYPE_LOGOUT	= 101,
    USER_ACTION_TYPE_FAIL	= 102,
    USER_ACTION_TYPE_KICK	= 103,
    USER_ACTION_TYPE_ONLINE	= 104,
    USER_ACTION_TYPE_LEAVE	= 105,
  };

  UserActionLog() :
    BaseTeamTalkPDU(MESSAGE_USER_ACTION_LOG) {}

  virtual ~UserActionLog() {}

  //////////////////////////////////////////////////////////////////////////
  PROPERTY_BASIC_TYPE_DECLARE(uint32, source);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, protocol);
  PROPERTY_OBJECT_DECLARE(std::string, ip);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, action_type);
  PROPERTY_OBJECT_DECLARE(std::string, os_type);
  PROPERTY_OBJECT_DECLARE(std::string, user_agent);
  PROPERTY_OBJECT_DECLARE(std::string, flash_ver);
  PROPERTY_OBJECT_DECLARE(std::string, client_ver);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() +
      sizeof(source_) +
      sizeof(protocol_) +
      SIZEOF_STRING(ip_) +
      sizeof(user_id_) +
      sizeof(action_type_) +
      SIZEOF_STRING(os_type_) +
      SIZEOF_STRING(user_agent_) +
      SIZEOF_STRING(flash_ver_) +
      SIZEOF_STRING(client_ver_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 source_;
  uint32 protocol_;
  std::string ip_;
  uint32 user_id_;
  uint32 action_type_;
  std::string os_type_;
  std::string user_agent_;
  std::string flash_ver_;
  std::string client_ver_;
};

#endif // PROTO_USER_ACTION_LOG_H_
