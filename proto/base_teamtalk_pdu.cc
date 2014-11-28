// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/base_teamtalk_pdu.h"

#include "base/logging.h"

#ifdef ZARESD_SERVER_LIB
#include "db/base_database.h"
#endif

//////////////////////////////////////////////////////////////////////////
uint32 UserInfo::ByteSize() const {
  return sizeof(user_id) +
    SIZEOF_STRING(name) +
    SIZEOF_STRING(nick_name) +
    SIZEOF_STRING(avatar_url) +
    SIZEOF_STRING(title) +
    SIZEOF_STRING(position) +
    sizeof(role_status) +
    sizeof(sex) +
    sizeof(depart_id) +
    sizeof(job_num) +
    SIZEOF_STRING(telphone) +
    SIZEOF_STRING(email) +
    sizeof(user_updated);
}

bool UserInfo::ParseFromByteStream(const net::ByteStream& is) {
  is >> user_id;
  is.ReadString(name);
  is.ReadString(nick_name);
  is.ReadString(avatar_url);
  is.ReadString(title);
  is.ReadString(position);
  is >> role_status
    >> sex
    >> depart_id
    >> job_num;
  is.ReadString(telphone);
  is.ReadString(email);
  is >> user_updated;

  return !is.Fail();
}

bool UserInfo::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << user_id;
  os->WriteString(name);
  os->WriteString(nick_name);
  os->WriteString(avatar_url);
  os->WriteString(title);
  os->WriteString(position);
  (*os) << role_status
    << sex
    << depart_id
    << job_num;
  os->WriteString(telphone);
  os->WriteString(email);
  (*os) << user_updated;

  return !os->Fail();
}

#ifdef ZARESD_SERVER_LIB
// "SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE uname=%s"
bool UserInfo::ParseFromDatabase(const db::QueryAnswer& answ) {
  enum {
    kColumn_Name = 0,
    kColumn_UsrID,
    kColumn_Status,
    kColumn_Title,
    kColumn_DepartID,
    kColumn_Sex,
    kColumn_JobNumber,
    kColumn_Telephone,
    kColumn_Mail,
    kColumn_Position,
    kColumn_Avatar,
    kColumn_NickName,
  };

  bool result  = true;
  do {
    DB_GET_RETURN_COLUMN(kColumn_Name, name);
    DB_GET_RETURN_COLUMN(kColumn_UsrID, user_id);
    DB_GET_RETURN_COLUMN(kColumn_Status, role_status);
    DB_GET_RETURN_COLUMN(kColumn_Title, title);
    DB_GET_RETURN_COLUMN(kColumn_DepartID, depart_id);
    DB_GET_RETURN_COLUMN(kColumn_Sex, sex);
    DB_GET_RETURN_COLUMN(kColumn_JobNumber, job_num);
    DB_GET_RETURN_COLUMN(kColumn_Telephone, telphone);
    DB_GET_RETURN_COLUMN(kColumn_Mail, email);
    DB_GET_RETURN_COLUMN(kColumn_Position, position);
    DB_GET_RETURN_COLUMN(kColumn_Avatar, avatar_url);
    DB_GET_RETURN_COLUMN(kColumn_NickName, nick_name);
  } while (0);

  return result;
}
#endif

#ifdef ZARESD_SERVER_LIB
// .1..4
// "SELECT relateid,frienduserid,status,created,updated FROM imrecentcontact WHERE userid = %d AND status = 0 ORDER BY updated desc, relateId DESC LIMIT 100";
bool FriendInfo::ParseFromDatabase(const db::QueryAnswer& answ) {
  enum {
    kColumn_RelateID = 0,
    kColumn_FriendUserID,
    kColumn_Status,
    kColumn_Created,
    kColumn_Updated,
  };

  bool result  = true;
  do {
    DB_GET_RETURN_COLUMN(kColumn_FriendUserID, friend_user_id);
    DB_GET_RETURN_COLUMN(kColumn_Updated, updated);
  } while (0);

  return result;
}
#endif

//////////////////////////////////////////////////////////////////////////
uint32 DepartmentInfo::ByteSize() const {
  return sizeof(depart_id) + SIZEOF_STRING(title) + SIZEOF_STRING(description) + sizeof(parent_depart_id) + sizeof(leader) + sizeof(status);
}

bool DepartmentInfo::ParseFromByteStream(const net::ByteStream& is) {
  is >> depart_id;
  is.ReadString(title);
  is.ReadString(description);
  is >> parent_depart_id
    >> leader
    >> status;

  return !is.Fail();
}

bool DepartmentInfo::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << depart_id;
  os->WriteString(title);
  os->WriteString(description);
  (*os) << parent_depart_id
    << leader
    << status;

  return !os->Fail();
}

#ifdef ZARESD_SERVER_LIB
// SELECT id,title,leader,pid,status,desc FROM imdepartment WHERE status = 0
bool DepartmentInfo::ParseFromDatabase(const db::QueryAnswer& answ) {
  enum {
    kColumn_ID = 0,
    kColumn_Title,
    kColumn_Leader,
    kColumn_PID,
    kColumn_Status,
    kColumn_Desc,
  };

  bool result  = true;
  do {
    DB_GET_RETURN_COLUMN(kColumn_ID, depart_id);
    DB_GET_RETURN_COLUMN(kColumn_Title, title);
    DB_GET_RETURN_COLUMN(kColumn_Leader, leader);
    DB_GET_RETURN_COLUMN(kColumn_PID, parent_depart_id);
    DB_GET_RETURN_COLUMN(kColumn_Status, status);
    DB_GET_RETURN_COLUMN(kColumn_Desc, description);
  } while (0);

  return result;
}
#endif


//////////////////////////////////////////////////////////////////////////
uint32 ServerMsg::ByteSize() const {
  return sizeof(from_user_id) +
    SIZEOF_STRING(from_name) +
    SIZEOF_STRING(from_nick_name) +
    SIZEOF_STRING(from_avatar_url) +
    sizeof(create_time) +
    sizeof(msg_type) +
    SIZEOF_STRING(msg_data);
}

bool ServerMsg::ParseFromByteStream(const net::ByteStream& is) {
  is >> from_user_id;
  is.ReadString(from_name);
  is.ReadString(from_nick_name);
  is.ReadString(from_avatar_url);
  is >> create_time
    >> msg_type;
  is.ReadString(msg_data);

  return !is.Fail();
}

bool ServerMsg::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << from_user_id;
  os->WriteString(from_name);
  os->WriteString(from_nick_name);
  os->WriteString(from_avatar_url);
  (*os) << create_time
    << msg_type;
  os->WriteString(msg_data);

  return !os->Fail();
}

//////////////////////////////////////////////////////////////////////////
const BaseAttachData* BaseTeamTalkPDU::GetAttachData() const {
  return attach_data_;
}

BaseAttachData* BaseTeamTalkPDU::MutableAttachData() {
  if (attach_data_ == NULL) {
    attach_data_ = BaseAttachData::CreateAttachData(attach_data_type_);
  }

  return attach_data_;
}

bool BaseTeamTalkPDU::ParseFromByteStream(const net::ByteStream& is) {
  return true;
}

bool BaseTeamTalkPDU::SerializeToByteStream(net::ByteStream* os) const {
  return true;
}

template <>
uint32 CalculateContainerByteSize(const std::vector<uint32>& container) {
  return container.empty() ? 0 : sizeof(uint32)+container.size()*sizeof(uint32);
}
