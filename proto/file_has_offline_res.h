// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_FILE_HAS_OFFLINE_RES_H_
#define PROTO_FILE_HAS_OFFLINE_RES_H_

#include "proto/base_teamtalk_pdu.h"

class FileHasOfflineRes : public BaseTeamTalkPDU {
public:
  FileHasOfflineRes() :
    BaseTeamTalkPDU(MESSAGE_FILE_HAS_OFFLINE_RES, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~FileHasOfflineRes() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
  PROPERTY_OBJECTPTR_ARRAY_DECLARE(OfflineFile, file_list);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const;

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 req_user_id_;
  std::vector<OfflineFile*> file_list_;
};

#endif // PROTO_FILE_HAS_OFFLINE_REQ_H_
