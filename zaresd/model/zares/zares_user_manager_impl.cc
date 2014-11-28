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
    user_info->ParseFromDatabase(*answ);
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
      "SELECT uname,id,status,title,departid,sex,jobnumber,telphone,mail,position,avatar,nickname FROM imusers WHERE id in (%s)",
      s_user_ids.c_str());
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    while (answ->FetchRow()) {
      UserInfo* user_info = new UserInfo();
      user_info->ParseFromDatabase(*answ);
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
    user_info->ParseFromDatabase(*answ);
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
      user_info->ParseFromDatabase(*answ);
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
      UserInfo* user = new UserInfo();
      // all_user_response.add_user_info_list();
      user->ParseFromDatabase(*answ);
    }

    return true;
  }

  return false;
}
