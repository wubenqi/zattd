// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/department_response.h"

namespace {

uint32 ByteSize(const DepartmentInfo& department_info) {
  return sizeof(department_info.depart_id) +
    SIZEOF_STRING(department_info.title) + 
    SIZEOF_STRING(department_info.description) +
    sizeof(department_info.parent_depart_id) +
    sizeof(department_info.leader) +
    sizeof(department_info.status);
}

bool ParseFromByteStream(DepartmentInfo* department_info, const base::ByteStream& is) {
  is >> department_info->depart_id;
  is.ReadString(department_info->title);
  is.ReadString(department_info->description);
  is >> department_info->parent_depart_id
    >> department_info->leader
    >> department_info->status;

  return !is.Fail();
}

bool SerializeToByteStream(const DepartmentInfo& department_info, base::ByteStream* os) {
  (*os) << department_info.depart_id;
  os->WriteString(department_info.title);
  os->WriteString(department_info.description);
  (*os) << department_info.parent_depart_id
    << department_info.leader
    << department_info.status;

  return !os->Fail();
}

}

uint32 DepartmentResponse::ByteSize() const {
  uint32 size = BaseTeamTalkPDU::ByteSize();
  size += sizeof(req_user_id_);
  CalculateContainerByteSize2(size, depart_list_);
  return size;
}

bool DepartmentResponse::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(DepartmentInfo, depart_list_);

  return !is.Fail();
}

bool DepartmentResponse::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << req_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(depart_list_);

  return !os->Fail();
}
