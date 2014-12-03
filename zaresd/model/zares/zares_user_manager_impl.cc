// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/zares/zares_user_manager_impl.h"

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/stringprintf.h"
#include "base2/string_util2.h"

#include "db/conn_pool_manager.h"

namespace {

// "SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE uname=%s"
bool ParseFromDatabase(UserInfo* user_info, const db::QueryAnswer& answ) {
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
    DB_GET_RETURN_COLUMN(kColumn_Name, user_info->name);
    DB_GET_RETURN_COLUMN(kColumn_UsrID, user_info->user_id);
    DB_GET_RETURN_COLUMN(kColumn_Status, user_info->role_status);
    DB_GET_RETURN_COLUMN(kColumn_Title, user_info->title);
    DB_GET_RETURN_COLUMN(kColumn_DepartID, user_info->depart_id);
    DB_GET_RETURN_COLUMN(kColumn_Sex, user_info->sex);
    DB_GET_RETURN_COLUMN(kColumn_JobNumber, user_info->job_num);
    DB_GET_RETURN_COLUMN(kColumn_Telephone, user_info->telphone);
    DB_GET_RETURN_COLUMN(kColumn_Mail, user_info->email);
    DB_GET_RETURN_COLUMN(kColumn_Position, user_info->position);
    DB_GET_RETURN_COLUMN(kColumn_Avatar, user_info->avatar_url);
    DB_GET_RETURN_COLUMN(kColumn_NickName, user_info->nick_name);
  } while (0);

  return result;
}

}

//////////////////////////////////////////////////////////////////////////
const UserInfo* ZAresUserManagerImpl::GetUserInfo(const uint32 user_id, UserInfo* user_info) {
  if (user_info == NULL || user_id == 0) {
    LOG(ERROR) << "user_info is NULL or user_id is 0!!!!";
    return NULL;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  // SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE uname=%s
  std::string sql = base::StringPrintf(
      "SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE id=%d",
      user_id);
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get() && answ->FetchRow()) {
    ::ParseFromDatabase(user_info, *answ);
    return user_info;
  } else {
    LOG(ERROR) << "Empty query result, user_id = " << user_id;
  }
  return NULL;
}

bool ZAresUserManagerImpl::GetUserInfo(const std::vector<uint32> user_ids, std::vector<UserInfo*>* user_infos) {
  if (user_infos == NULL || user_ids.empty()) {
    LOG(ERROR) << "user_infos is NULL or user_id is empty()!!!!";
    return false;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  std::string s_user_ids;
  JoinString(user_ids, ',', &s_user_ids);

  // SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE uname=%s
  std::string sql = base::StringPrintf(
      "SELECT uname,id,status,title,departId,sex,jobNumber,telphone,mail,position,avatar,nickName FROM IMUsers WHERE id IN (%s)",
      s_user_ids.c_str());
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    while (answ->FetchRow()) {
      UserInfo* user_info = new UserInfo();
      ParseFromDatabase(user_info, *answ);
      user_infos->push_back(user_info);
    }
    return true;
  } else {
    LOG(ERROR) << "Empty query result, user_ids in (" << s_user_ids << ")";
  }
  return false;
}

const UserInfo* ZAresUserManagerImpl::GetUserInfo(const std::string& user_name, UserInfo* user_info) {
  if (user_info == NULL || user_name.empty()) {
    LOG(ERROR) << "user_info is NULL or user_name is empty!!!!";
    return NULL;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  // SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE uname=%s
  std::string sql = base::StringPrintf(
      "SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE uname in('%s')",
      user_name.c_str());
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get() && answ->FetchRow()) {
    ParseFromDatabase(user_info, *answ);
    return user_info;
  } else {
    LOG(ERROR) << "Empty query result, user_name = " << user_name;
  }
  return NULL;
}

// 获取一组用户的信息
bool ZAresUserManagerImpl::GetUserInfo(const std::vector<std::string>& user_names, std::vector<UserInfo*>* user_infos) {
  if (user_infos == NULL || user_names.empty()) {
    LOG(ERROR) << "user_infos is NULL or user_names is empty()!!!!";
    return false;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  
  // std::string s_user_names = base::JoinString(user_names, ',');
  // SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE uname=%s
  std::string sql = base::StringPrintf(
      "SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE id in (%s)",
      JoinString(user_names, ',').c_str());
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    while (answ->FetchRow()) {
      UserInfo* user_info = new UserInfo();
      ParseFromDatabase(user_info, *answ);
      user_infos->push_back(user_info);
    }
    return true;
  } else {
    LOG(ERROR) << "Empty query result, user_names in(" << JoinString(user_names, ',') << ")";
  }
  return false;
}


bool ZAresUserManagerImpl::GetAllUserInfo(std::vector<UserInfo*>* user_infos) {
  DCHECK(user_infos);

  if (user_infos == NULL) {
    return false;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  // 最多取5000个用户
  // SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE status = 0 LIMIT 5000"
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query("SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE status = 0 LIMIT 5000"));
  if (answ.get() != NULL) {
    while (answ->FetchRow()) {
      UserInfo* user_info = new UserInfo();
      ParseFromDatabase(user_info, *answ);
      user_infos->push_back(user_info);
    }

    return true;
  }

  return false;
}
