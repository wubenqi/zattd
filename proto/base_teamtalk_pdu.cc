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
    SIZEOF_STRING(nick_name) +
    SIZEOF_STRING(avatar_url) +
    SIZEOF_STRING(title) +
    SIZEOF_STRING(position) +
    sizeof(role_status) +
    sizeof(sex) +
    sizeof(depart_id) +
    sizeof(job_num) +
    SIZEOF_STRING(telphone) +
    SIZEOF_STRING(email);
}

bool UserInfo::ParseFromByteStream(const net::ByteStream& is) {
  is >> user_id;
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

  return !is.Fail();
}

bool UserInfo::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << user_id;
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
uint32 GroupInfo::ByteSize() const {
  return sizeof(group_id) +
    SIZEOF_STRING(group_name) +
    SIZEOF_STRING(group_avatar) +
    sizeof(group_creator_id) +
    sizeof(group_type) +
    sizeof(group_updated) +
    CalculateContainerByteSize(group_memeber_list);
}

bool GroupInfo::ParseFromByteStream(const net::ByteStream& is) {
  is >> group_id;
  is.ReadString(group_name);
  is.ReadString(group_avatar);
  is >> group_type
    >> group_creator_id
    
    >> group_updated;
  uint32 group_memeber_list_size = 0;
  is >> group_memeber_list_size;
  for (size_t i=0; i<group_memeber_list_size; ++i) {
    uint32 group_memeber_id = 0;
    is >> group_memeber_id;
    group_memeber_list.push_back(group_memeber_id);
  }
  return !is.Fail();
}

bool GroupInfo::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << group_id;
  os->WriteString(group_name);
  os->WriteString(group_avatar);
  (*os) << group_creator_id
    << group_type
    << group_updated
    << group_memeber_list.size();
  for (size_t i=0; i<group_memeber_list.size(); ++i) {
    (*os) << group_memeber_list[i];
  }
  return true;
}

#ifdef ZARESD_SERVER_LIB
bool GroupInfo::ParseFromDatabase(const db::QueryAnswer& answ) {
  // "SELECT groupId,groupName,avatar,createUserId,groupType,updated FROM IMGroup WHERE groupId IN "
  //   "(SELECT groupId FROM IMGroupRelation WHERE userId=%d AND status>=1 %s ORDER BY created DESC, id DESC LIMIT %d)",
  enum {
    kColumn_GroupID = 0,
    kColumn_GroupName,
    kColumn_Avatar,
    kColumn_CreateUserID,
    kColumn_GroupType,
    kColumn_Updated,
  };

  bool result  = true;
  do {
    DB_GET_RETURN_COLUMN(kColumn_GroupID, group_id);
    DB_GET_RETURN_COLUMN(kColumn_GroupName, group_name);
    DB_GET_RETURN_COLUMN(kColumn_Avatar, group_avatar);
    DB_GET_RETURN_COLUMN(kColumn_CreateUserID, group_creator_id);
    DB_GET_RETURN_COLUMN(kColumn_GroupType, group_type);
    DB_GET_RETURN_COLUMN(kColumn_Updated, group_updated);
  } while (0);

  return result;
}
#endif

//////////////////////////////////////////////////////////////////////////
bool BaseTeamTalkPDU::ParseFromArray(const void* data, uint32 data_len) {
  net::ByteStream is(data, data_len);
  bool result = ParseFromByteStream(is);
  if (result && HasAttachData()) {
    is.ReadString(attach_data_);
    result = !is.Fail();
    // result = MutableAttachData()->ParseFromByteStream(is);
  }
  return result;
}

bool BaseTeamTalkPDU::SerializeToArray(void* data, uint32 data_len) const {
  net::ByteStream os(data, data_len);
  bool result = SerializeToByteStream(&os);
  if (result && HasAttachData()) {
    os.WriteString(attach_data_);
    // result = attach_data_->SerializeToByteStream(&os);
    result = !os.Fail();
  }
  return result;
}

//const BaseAttachData* BaseTeamTalkPDU::GetAttachData() const {
//  return attach_data_;
//}
//
//BaseAttachData* BaseTeamTalkPDU::MutableAttachData() {
//  if (attach_data_ == NULL) {
//    attach_data_ = BaseAttachData::CreateAttachData(attach_data_type_);
//  }
//
//  return attach_data_;
//}

bool BaseTeamTalkPDU::ParseFromByteStream(const net::ByteStream& is) {
  return true;
}

bool BaseTeamTalkPDU::SerializeToByteStream(net::ByteStream* os) const {
  return true;
}

void BaseTeamTalkPDU::SetAttachData(const std::string& data) {
  DCHECK(HasAttachData()) << "Attach_data_type must kAttachDataTypeDB or kAttachDataTypePdu";
  if (HasAttachData()) {
    attach_data_ = data;
  }
}

void BaseTeamTalkPDU::SetAttachData(const char*data, uint32 data_len) {
  DCHECK(HasAttachData()) << "Attach_data_type must kAttachDataTypeDB or kAttachDataTypePdu";
  if (HasAttachData()) {
    attach_data_.assign(data, data_len);
  }
}

const std::string* BaseTeamTalkPDU::GetAttachData() const {
  if (HasAttachData()) {
    return &attach_data_;
  } else {
    return NULL;
  }
}

std::string* BaseTeamTalkPDU::MutableAttachData() {
  if (HasAttachData()) {
    return &attach_data_;
  } else {
    return NULL;
  }
}

template <>
uint32 CalculateContainerByteSize(const std::vector<uint32>& container) {
  return container.empty() ? 0 : sizeof(uint32)+container.size()*sizeof(uint32);
}

