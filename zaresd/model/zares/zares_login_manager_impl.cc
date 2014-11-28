// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/zares/zares_login_manager_impl.h"

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/stringprintf.h"
#include "db/conn_pool_manager.h"

bool ZAresLoginManagerImpl::Auth(const std::string& user_name, const std::string& password) {
  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  // 1. 检查密码是否正确
  std::string sql;
  // SELECT pwd FROM imusers WHERE uname=%s
  base::SStringPrintf(&sql, "SELECT pwd FROM imusers WHERE uname='%s'", user_name.c_str());
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  bool is_authed = true;
  if (answ.get() != NULL) {
    if (answ->FetchRow()) {
      std::string pwd;
      answ->GetColumn(0, &pwd);
      if (pwd != password) {
        is_authed = false;
        LOG(ERROR) << "user_name[" << user_name << "]'s passwd[" << password << "] is invalid!!!";
      }
    } else {
      LOG(ERROR) << "user_name[" << user_name << "] not found in db;";
    }
  }
  return is_authed;
}
