// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_DB_WRITE_RESPONSE_H_
#define PROTO_DB_WRITE_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class DBWriteResponse : public BaseTeamTalkPDU {
public:
  DBWriteResponse() :
    BaseTeamTalkPDU(MESSAGE_DB_WRITE_RESPONSE) {}

  virtual ~DBWriteResponse() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, request_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, result);
  PROPERTY_BASIC_TYPE_DECLARE(uint16, request_pdu_type);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, from_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, to_id);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() +
      sizeof(request_id_) + sizeof(result_) + sizeof(request_pdu_type_) + sizeof(from_id_) + sizeof(to_id_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32	request_id_;
  uint32	result_;
  uint16	request_pdu_type_;
  uint32	from_id_;
  uint32	to_id_;
};



#endif // PROTO_DB_WRITE_RESPONSE_H_
