// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_FILE_DEL_OFFLINE_REQ_H_
#define PROTO_FILE_DEL_OFFLINE_REQ_H_

#include "proto/base_teamtalk_pdu.h"

class FileDelOfflineReq : public BaseTeamTalkPDU {
public:
  FileDelOfflineReq() :
    BaseTeamTalkPDU(MESSAGE_FILE_DEL_OFFLINE_REQ, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~FileDelOfflineReq() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, from_id);
  PROPERTY_BASIC_TYPE_DECLARE(uint32, to_id);
  PROPERTY_OBJECT_DECLARE(std::string, task_id);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() +
      sizeof(req_user_id_) +
      sizeof(from_id_) +
      sizeof(to_id_) +
      SIZEOF_STRING(task_id_);
  }

protected:
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;

  uint32 req_user_id_;
  uint32 from_id_;
  uint32 to_id_;
  std::string task_id_;
};

#endif // PROTO_FILE_ADD_OFFLINE_REQ_H_
