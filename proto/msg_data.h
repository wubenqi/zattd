// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_MSG_DATA_H_
#define PROTO_MSG_DATA_H_

#include "proto/base_teamtalk_pdu.h"

class MsgData : public BaseTeamTalkPDU {
public:
  MsgData() :
    BaseTeamTalkPDU(MESSAGE_MSG_DATA, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~MsgData() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, request_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, from_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, to_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, create_time);
  PROPERTY_BASIC_TYPE_DECLARE(uint8, msg_type);
  PROPERTY_OBJECT_DECLARE(std::string, msg_data);
  
  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() +
      sizeof(request_id_) + sizeof(from_user_id_) + sizeof(to_user_id_) + sizeof(create_time_) + sizeof(msg_type_) + SIZEOF_STRING(msg_data_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 request_id_;
  uint32 from_user_id_;
  uint32 to_user_id_;
  uint32 create_time_;
  uint8  msg_type_;
  std::string msg_data_;
};

#endif // PROTO_MSG_DATA_H_
