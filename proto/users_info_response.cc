// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/users_info_response.h"

// bool UsersInfoResponse::ParseFromByteStream(const net::ByteStream& is) {
//   is >> from_user_id_;
//   PARSE_OBJECTPTR_ARRAY_IMPLICIT(UserInfo, user_info_list_);
// 
//   return !is.Fail();
// }
// 
// bool UsersInfoResponse::SerializeToByteStream(net::ByteStream* os) const {
//   (*os) << from_user_id_;
//   SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(user_info_list_);
// 
//   return !os->Fail();
// }

namespace {

uint32 ByteSize(const UserInfo& user_info) {
  return sizeof(user_info.user_id) +
    SIZEOF_STRING(user_info.name) +
    SIZEOF_STRING(user_info.nick_name) +
    SIZEOF_STRING(user_info.avatar_url) +
    SIZEOF_STRING(user_info.title) +
    SIZEOF_STRING(user_info.position) +
    sizeof(user_info.role_status) +
    sizeof(user_info.sex) +
    sizeof(user_info.depart_id) +
    sizeof(user_info.job_num) +
    SIZEOF_STRING(user_info.telphone) +
    SIZEOF_STRING(user_info.email);
}

bool ParseFromByteStream(UserInfo* user_info, const net::ByteStream& is) {
  is >> user_info->user_id;
  is.ReadString(user_info->name);
  is.ReadString(user_info->nick_name);
  is.ReadString(user_info->avatar_url);
  is.ReadString(user_info->title);
  is.ReadString(user_info->position);
  is >> user_info->role_status
    >> user_info->sex
    >> user_info->depart_id
    >> user_info->job_num;
  is.ReadString(user_info->telphone);
  is.ReadString(user_info->email);

  return !is.Fail();
}

bool SerializeToByteStream(const UserInfo& user_info,  net::ByteStream* os) {
  (*os) << user_info.user_id;
  os->WriteString(user_info.name);
  os->WriteString(user_info.nick_name);
  os->WriteString(user_info.avatar_url);
  os->WriteString(user_info.title);
  os->WriteString(user_info.position);
  (*os) << user_info.role_status
    << user_info.sex
    << user_info.depart_id
    << user_info.job_num;
  os->WriteString(user_info.telphone);
  os->WriteString(user_info.email);

  return !os->Fail();
}

}

uint32 UsersInfoResponse::ByteSize() const {
  uint32 size = BaseTeamTalkPDU::ByteSize();
  size += sizeof(from_user_id_);
  CalculateContainerByteSize2(size, user_info_list_);
  return size;
}


bool UsersInfoResponse::ParseFromByteStream(const net::ByteStream& is) {
  is >> from_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(UserInfo, user_info_list_);

  return !is.Fail();
}

bool UsersInfoResponse::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << from_user_id_;
  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(user_info_list_);

  return !os->Fail();
}
