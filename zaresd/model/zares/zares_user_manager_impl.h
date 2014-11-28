// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_ZARES_ZARES_USER_MANAGER_IMPL_H_
#define ZARESD_MODEL_ZARES_ZARES_USER_MANAGER_IMPL_H_

#include "zaresd/model/user_manager.h"

namespace db {
class CdbConnPoolManager;
}

class ZAresUserManagerImpl : public UserManager {
public:
  ZAresUserManagerImpl(db::CdbConnPoolManager* db_conn_pool)
    : db_conn_pool_(db_conn_pool) {}
  virtual ~ZAresUserManagerImpl() {}

  //////////////////////////////////////////////////////////////////////////
  virtual const UserInfo* GetUserInfo(const uint32 user_id, UserInfo* user_info);

  // 获取一组用户的信息
  virtual bool GetUserInfo(const std::vector<uint32> user_ids, std::vector<UserInfo*>* user_infos);

  // from UserManager
  virtual const UserInfo* GetUserInfo(const std::string& user_name, UserInfo* user_info) ;

  // 获取一组用户的信息
  virtual bool GetUserInfo(const std::vector<std::string>& user_names, std::vector<UserInfo*>* user_infos);

  // 
  virtual bool GetAllUserInfo(std::vector<UserInfo*>* user_infos);

private:
  db::CdbConnPoolManager* db_conn_pool_;
};

#endif
