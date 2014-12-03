// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_DEPARMENT_RESPONSE_H_
#define PROTO_DEPARMENT_RESPONSE_H_

#include "proto/base_teamtalk_pdu.h"

class DepartmentResponse : public BaseTeamTalkPDU {
public:
  DepartmentResponse() :
    BaseTeamTalkPDU(MESSAGE_DEPARTMENT_RESPONSE, BaseAttachData::kAttachDataTypeDB) {}

  virtual ~DepartmentResponse() {
    STLDeleteElements(&depart_list_);
  }

   PROPERTY_BASIC_TYPE_DECLARE(uint32, req_user_id);
   PROPERTY_OBJECTPTR_ARRAY_DECLARE(DepartmentInfo, depart_list);
// 
  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const;

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 req_user_id_;
  std::vector<DepartmentInfo*> depart_list_;
};

#endif // PROTO_DEPARMENT_RESPONSE_H_
