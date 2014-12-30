// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/zares/zares_relationship_manager_impl.h"

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/stringprintf.h"
#include "base2/time2.h"
#include "base/strings/string_number_conversions.h"

#include "db/database_util.h"
#include "db/conn_pool_manager.h"

#include "zaresd/const_zaresd_defines.h"

namespace {

// .1..4
// "SELECT relateid,frienduserid,status,created,updated FROM imrecentcontact WHERE userid = %d AND status = 0 ORDER BY updated desc, relateId DESC LIMIT 100";
bool ParseFromDatabase(FriendInfo* friend_info, const db::QueryAnswer& answ) {
  enum {
    kColumn_RelateID = 0,
    kColumn_FriendUserID,
    kColumn_Status,
    kColumn_Created,
    kColumn_Updated,
  };

  bool result  = true;
  do {
    DB_GET_RETURN_COLUMN(kColumn_FriendUserID, friend_info->friend_user_id);
    DB_GET_RETURN_COLUMN(kColumn_Updated, friend_info->updated);
  } while (0);

  return result;
}

}
bool ZAresRelationshipManagerImpl::GetRecentContactByUserId(uint32 user_id, int limit, std::vector<FriendInfo*>* friends) {
  if (friends == NULL || user_id == 0) {
    LOG(ERROR) << "friends is NULL or user_id is 0!!!!";
    return false;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  std::string sql = base::StringPrintf(
      "SELECT relateId,friendUserId,status,created,updated FROM IMRecentContact WHERE userId = %d AND status = 0 ORDER BY updated DESC, relateId DESC LIMIT 100",
      user_id
    );

  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));
  if (answ.get() != NULL) {
    while (answ->FetchRow()) {
      FriendInfo* friend_info = new FriendInfo();
      CHECK(friend_info);
      ParseFromDatabase(friend_info, *answ);
      friends->push_back(friend_info);
    }
  } else {
    return false;
  }

  return true;
}

bool ZAresRelationshipManagerImpl::DeleteRecentContactByUserId(uint32 user_id, uint32 friend_user_id) {
  // db::BaseDatabase* db_conn = context->GetDatabaseConncetion();
  std::string sql;
  base::SStringPrintf(&sql, "UPDATE IMRecentContact SET status = 1 WHERE userId = %d AND friendUserId = %d LIMIT 1",
      user_id,friend_user_id
    );

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  return 0 == db_conn->Execute(sql);
}

uint32 ZAresRelationshipManagerImpl::GetRelateId(uint32 user_AId, uint32 user_BId) {
  uint32 relate_id = kInvalidID;

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

bool ZAresRelationshipManagerImpl::CheckAndUpdateRelation(uint32 usera_id, uint32 userb_id) {
  if (usera_id == 0 ||userb_id == 0) {
      return true;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  uint32 relate_id = 0;
  std::string relate_ids;

  db::QueryParam p;
  p.AddParam(&usera_id);
  p.AddParam(&userb_id);
  p.AddParam(&usera_id);
  p.AddParam(&userb_id);

  std::string sql;
  db::MakeQueryString("SELECT relateId,status FROM IMRecentContact WHERE (userId=:1 AND friendUserId=:2) OR (userId=:3 AND friendUserId=:4) LIMIT 2", &p, &sql);
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));
  if (answ.get() != NULL) {
    while (answ->FetchRow()) {
      uint32 status = 0;
      answ->GetColumn(0, &relate_id);
      answ->GetColumn(1, &status);
      if (status != 0) {
        if (!relate_ids.empty()) {
          relate_ids.push_back(',');
        }
        relate_ids.append(base::UintToString(relate_id));
      }
    }
  } else {
    LOG(ERROR) << "";
  }

  bool is_sucess = false;
  if (!relate_ids.empty()) {
    sql = base::StringPrintf("UPDATE IMRecentContact SET status = 0 WHERE relateId in (%s) LIMIT 4", relate_ids.c_str());
    is_sucess = ( 0 == db_conn->Execute(sql));
  }

  return is_sucess;
}

// 加为好友，互相关系，一次插两条
uint32 ZAresRelationshipManagerImpl::AddFriendship(uint32 usera_id, uint32 userb_id) {
  if (usera_id == 0 || userb_id == 0) {
      return kInvalidID;
  }

  // 已存在关系
  uint32 relate_id = GetRelateId(usera_id, userb_id);
  if (relate_id != kInvalidID) {
      return relate_id;
  }

  uint32 mid;
  // 取用户Id小的在前的relateId作为两个人的relateId,轻度洁癖君表示尽量保证这个关系Id比另一条记录小
  if (usera_id > userb_id) {
      mid = usera_id;
      usera_id = userb_id;
      userb_id = mid;
  }

  uint32 ctime = base::NowMSTime()/1000;
  int default_status = 0;
  uint32 id = kInvalidID;

  db::QueryParam p;
  std::string sql;
  if (usera_id != userb_id) {
    p.AddParam(&usera_id);
    p.AddParam(&userb_id);
    p.AddParam(&default_status);
    p.AddParam(&ctime);
    p.AddParam(&ctime);
    p.AddParam(&userb_id);
    p.AddParam(&usera_id);
    p.AddParam(&default_status);
    p.AddParam(&ctime);
    p.AddParam(&ctime);
    MakeQueryString("INSERT INTO IMRecentContact(`userId`,`friendUserId`,`status`,`created`,`updated`) VALUES(:1, :2, :3, :4, :5),(:6, :7, :8, :9, :10)", &p, &sql);
  } else {
    p.AddParam(&usera_id);
    p.AddParam(&userb_id);
    p.AddParam(&default_status);
    p.AddParam(&ctime);
    p.AddParam(&ctime);
    MakeQueryString("INSERT INTO IMRecentContact(`userId`,`friendUserId`,`status`,`created`,`updated`) VALUES(:1, :2, :3, :4, :5)", &p, &sql);
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  return static_cast<uint32>(db_conn->ExecuteInsertID(sql));
}
