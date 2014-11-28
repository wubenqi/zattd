// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/zares/zares_relationship_manager_impl.h"

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/stringprintf.h"
#include "db/conn_pool_manager.h"

bool ZAresRelationshipManagerImpl::GetRecentContactByUserId(uint32 user_id, int limit, std::vector<FriendInfo*>* friends) {
  if (friends == NULL || user_id == 0) {
    LOG(ERROR) << "friends is NULL or user_id is 0!!!!";
    return false;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  std::string sql = StringPrintf(
      "SELECT relateid,frienduserid,status,created,updated FROM imrecentcontact WHERE userid = %d AND status = 0 ORDER BY updated desc, relateId DESC LIMIT 100",
      user_id
    );

  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));
  if (answ.get() != NULL) {
    while (answ->FetchRow()) {
      FriendInfo* user = new FriendInfo();
      CHECK(user);
      user->ParseFromDatabase(*answ);
      friends->push_back(user);
    }
  } else {
    return false;
  }

  return true;
}

bool ZAresRelationshipManagerImpl::DeleteRecentContactByUserId(uint32 user_id, uint32 friend_user_id) {
  // db::BaseDatabase* db_conn = context->GetDatabaseConncetion();
  std::string sql;
  base::SStringPrintf(&sql, "UPDATE imrecentcontact SET status = 1 WHERE userid = %d and frienduserid = %d limit 1",
      user_id,friend_user_id
    );

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  return 0 == db_conn->Execute(sql);
}

uint32 ZAresRelationshipManagerImpl::GetRelateId(uint32 user_AId, uint32 user_BId) {
  uint32 relate_id = (uint32)-1;

  if (user_AId == 0 || user_BId == 0) {
    LOG(ERROR) << "user_AId or user_BId is 0";
    return relate_id;
  }

  uint32 small_user_id;
  uint32 big_user_id;
  // 取用户Id小的在前的relateId作为两个人的relateId
  if (user_AId > user_BId) {
    small_user_id = user_BId;
    big_user_id = user_AId;
  } else {
    small_user_id = user_AId;
    big_user_id = user_BId;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  std::string sql;
  base::SStringPrintf(&sql, "SELECT relateId FROM IMRecentContact WHERE userId = %i and friendUserId = %i limit 1", small_user_id, big_user_id);
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));
  if (answ.get() != NULL) {
    if (answ->FetchRow()) {
      answ->GetColumn(0, &relate_id);
    }
  } else {
    LOG(ERROR) << "";
  }

  return relate_id;
}
