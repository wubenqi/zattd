// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_FILE_HAS_OFFLINE_REQ_H_
#define PROTO_FILE_HAS_OFFLINE_REQ_H_

#include "proto/base_teamtalk_pdu.h"

class FileHasOfflineReq : public BaseTeamTalkPDU {
public:
  FileHasOfflineReq() :
    BaseTeamTalkPDU(MESSAGE_FILE_HAS_OFFLINE_REQ, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~FileHasOfflineReq() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, user_id);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + sizeof(user_id_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 user_id_;
};

#endif // PROTO_FILE_HAS_OFFLINE_REQ_H_
