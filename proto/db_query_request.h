// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_DB_QUERY_REQUEST_H_
#define PROTO_DB_QUERY_REQUEST_H_

#include "proto/base_teamtalk_pdu.h"

class DBQueryRequest : public BaseTeamTalkPDU {
public:
  DBQueryRequest() :
    BaseTeamTalkPDU(MESSAGE_DB_QUERY_REQUEST, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~DBQueryRequest() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, seq_no);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, user_id);
  PROPERTY_OBJECT_DECLARE(std::string, query_data);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + sizeof(seq_no_) + sizeof(user_id_) + SIZEOF_STRING(query_data_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 seq_no_;
  uint32 user_id_;
  std::string query_data_;
};

#endif // PROTO_DB_QUERY_REQUEST_H_
