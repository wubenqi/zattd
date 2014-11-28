// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_ZARES_ZARES_LOGIN_MANAGER_IMPL_H_
#define ZARESD_MODEL_ZARES_ZARES_LOGIN_MANAGER_IMPL_H_

#include "zaresd/model/login_manager.h"

namespace db {
class CdbConnPoolManager;
}

class ZAresLoginManagerImpl : public LoginManager {
public:
  ZAresLoginManagerImpl(db::CdbConnPoolManager* db_conn_pool)
    : db_conn_pool_(db_conn_pool) {}
  virtual ~ZAresLoginManagerImpl() {}

  // 登陆的验证接口
  // uname:
  // passwd已加密密码
  virtual bool Auth(const std::string& user_name, const std::string& password);

private:
  db::CdbConnPoolManager* db_conn_pool_;
};

#endif
