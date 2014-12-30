// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/zares/zares_group_manager_impl.h"

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/stringprintf.h"
#include "base/strings/string_number_conversions.h"
#include "base2/string_util2.h"
#include "base2/time2.h"

#include "db/database_util.h"

#include "db/conn_pool_manager.h"


namespace {

struct UserStatus {
  uint32 status;
  uint32 user_id;
};

bool ParseFromDatabase(GroupInfo* group_info, const db::QueryAnswer& answ) {
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
    DB_GET_RETURN_COLUMN(kColumn_GroupID, group_info->group_id);
    DB_GET_RETURN_COLUMN(kColumn_GroupName, group_info->group_name);
    DB_GET_RETURN_COLUMN(kColumn_Avatar, group_info->group_avatar);
    DB_GET_RETURN_COLUMN(kColumn_CreateUserID, group_info->group_creator_id);
    DB_GET_RETURN_COLUMN(kColumn_GroupType, group_info->group_type);
    DB_GET_RETURN_COLUMN(kColumn_Updated, group_info->group_updated);
  } while (0);

  return result;
}

}

size_t ZAresGroupManagerImpl::GetGroupsByUserId(uint32 user_id, bool is_fixed_group, std::vector<GroupInfo*>* groups) {
  if (groups == NULL || user_id == 0) {
    LOG(ERROR) << "groups is NULL or user_id is 0!!!!";
    return 0;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  std::string sql = base::StringPrintf(
      "SELECT groupId,groupName,avatar,createUserId,groupType,updated FROM IMGroup WHERE groupId IN "
      "(SELECT groupId FROM (SELECT groupId FROM IMGroupRelation WHERE userId=%d AND status>=1 %s ORDER BY created DESC, id DESC LIMIT %d) AS tp)",
      user_id,
      (is_fixed_group ? " AND groupType = 1 " : ""),
      (is_fixed_group ? 200 : 5000));

  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    while(answ->FetchRow()) {
      GroupInfo* group = new GroupInfo();
      ::ParseFromDatabase(group, *answ);
      groups->push_back(group);
    }
  } else {
    LOG(ERROR) << "Empty query result, user_id = " << user_id;
  }
  return groups->size();
}

size_t ZAresGroupManagerImpl::GetGroupIdsByUserId(uint32 user_id, bool is_fixed_group, std::vector<uint32>* group_ids) {
  if (group_ids == NULL || user_id == 0) {
    LOG(ERROR) << "group_ids is NULL or user_id is 0!!!!";
    return 0;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  std::string sql = base::StringPrintf(
    "SELECT groupId FROM IMGroup WHERE groupId IN "
    "(SELECT groupId FROM (SELECT groupId FROM IMGroupRelation WHERE userId=%d AND status>=1 %s ORDER BY created DESC, id DESC LIMIT %d) AS tp)",
    user_id,
    (is_fixed_group ? " AND groupType = 1 " : ""),
    (is_fixed_group ? 200 : 5000));

  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    while(answ->FetchRow()) {
      uint32 group_id;
      answ->GetColumn(0, &group_id);
      group_ids->push_back(group_id);
    }
  } else {
    LOG(ERROR) << "Empty query result, user_id = " << user_id;
  }
  return group_ids->size();
}

size_t ZAresGroupManagerImpl::GetGroupMembers(const std::vector<uint32>& group_ids, GroupRelationInfoListMap* group_relations_map) {
  if (group_relations_map == NULL || group_ids.empty()) {
    LOG(ERROR) << "group_relations_map is NULL or group_ids is empty()!!!!";
    return 0;
  }

  std::string s_group_ids;
  JoinString(group_ids, ',', &s_group_ids);

  std::string sql = base::StringPrintf(
      "SELECT groupId,userId FROM IMGroupRelation WHERE groupId in (%s) AND status >= 1 ORDER BY created ASC LIMIT 10000", s_group_ids.c_str());

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    while(answ->FetchRow()) {
      GroupRelationInfo relation;
      answ->GetColumn(0, &relation.group_id);
      answ->GetColumn(1, &relation.user_id);

      GroupRelationInfoListMap::iterator it = group_relations_map->find(relation.group_id);
      if (it!=group_relations_map->end()) {
        it->second.push_back(relation);
      } else {
        GroupRelationInfoList relation_list;
        std::pair<GroupRelationInfoListMap::iterator, bool> ret = group_relations_map->insert(std::make_pair(relation.group_id, relation_list));
        ret.first->second.push_back(relation);
      }
    }
  } else {
    // LOG(ERROR) << "Empty query result, user_id = " << user_id;
  }

  return group_relations_map->size();
}

size_t ZAresGroupManagerImpl::GetGroupMembers(uint32 group_id, GroupRelationInfoList* group_relations) {
  if (group_relations == NULL || group_id == 0) {
    LOG(ERROR) << "group_relations_map is NULL or group_ids is empty()!!!!";
    return 0;
  }

  std::string sql = base::StringPrintf(
    "SELECT groupId,userId FROM IMGroupRelation WHERE groupId=%d AND status >= 1 ORDER BY created ASC LIMIT 10000", group_id);

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    while(answ->FetchRow()) {
      GroupRelationInfo relation;
      answ->GetColumn(0, &relation.group_id);
      answ->GetColumn(1, &relation.user_id);
      group_relations->push_back(relation);
    }
  } else {
    // LOG(ERROR) << "Empty query result, user_id = " << user_id;
  }

  return group_relations->size();
}

const GroupInfo* ZAresGroupManagerImpl::GetGroupInfo(uint32 group_id, GroupInfo* group) {
  if (group == NULL || group_id == 0) {
    LOG(ERROR) << "group is NULL or group_ids is empty()!!!!";
    return NULL;
  }

  std::string sql = base::StringPrintf(
    "SELECT groupId,groupName,avatar,createUserId,groupType,updated FROM IMGroup WHERE groupId=%d AND status>=1", group_id);

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    if(answ->FetchRow()) {
      ::ParseFromDatabase(group, *answ);
      return group;
    }
  } else {
    // LOG(ERROR) << "Empty query result, user_id = " << user_id;
  }

  return NULL;
}

size_t ZAresGroupManagerImpl::GetRecentGroupsByUserId(uint32 user_id, std::vector<GroupInfo*>* groups) {
  if (groups == NULL || user_id == 0) {
    LOG(ERROR) << "groups is NULL or user_id is 0!!!!";
    return 0;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  std::string sql = base::StringPrintf(
      "SELECT groupId,groupName,avatar,createUserId,groupType,updated FROM IMGroup WHERE groupId IN "
      "(SELECT groupId FROM (SELECT groupId FROM IMGroupRelation WHERE userId=%d AND status=1 ORDER BY updated DESC, id DESC LIMIT 100) AS tp)",
      user_id);

  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    while(answ->FetchRow()) {
      GroupInfo* group = new GroupInfo();
      ::ParseFromDatabase(group, *answ);
      groups->push_back(group);
    }
  } else {
    LOG(ERROR) << "Empty query result, user_id = " << user_id;
  }
  return groups->size();
}

bool ZAresGroupManagerImpl::CreateGroup(uint32 create_user_id, const std::string& group_name, uint32 group_type,
                                        const std::string& avatar, const std::string& adesc, const std::vector<uint32>& member_user_ids, GroupInfo* group) {
  if (create_user_id == 0 || group_name.empty() || group_type == 0) {
    return false;
  } 

  group->group_id = 0;
  group->group_creator_id = create_user_id;
  group->group_name = group_name;
  group->group_avatar = avatar;
  group->group_type = group_type;
  group->group_updated = base::NowMSTime()/1000;

  db::QueryParam p;
  uint32 now = base::NowMSTime()/1000;
  p.AddParam(group_name.c_str());
  p.AddParam(avatar.c_str());
  p.AddParam(adesc.c_str());
  p.AddParam(&create_user_id);
  p.AddParam(&group_type);
  p.AddParam(&now);
  p.AddParam(&now);
  
  std::string sql;
  // INSERT INTO IMGroup(`groupName`,`avatar`,`adesc`,`createUserId`,`groupType`,`memberCnt`,`created`,`updated`) VALUES(:1,:2,:3,:4,:5,0,:7,:8)
  MakeQueryString("INSERT INTO IMGroup(`groupName`,`avatar`,`adesc`,`createUserId`,`groupType`,`memberCnt`,`created`,`updated`) VALUES(:1,:2,:3,:4,:5,0,:7,:8)", &p, &sql);

  uint64 group_id = 0;
  {
    db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
    group_id = db_conn->ExecuteInsertID(sql);
    if (group_id>0) {
      group->group_id = group_id;
      group->group_creator_id = create_user_id;
      group->group_name = group_name;
      group->group_avatar = avatar;
      group->group_type = group_type;
      group->group_updated = base::NowMSTime();
    }
  }

  if (group_id > 0) {
    return JoinGroup(member_user_ids, group_id, *group);
  }

  return false;
}


bool ZAresGroupManagerImpl::JoinGroup(const std::vector<uint32>& user_ids, uint32 group_id, const GroupInfo& group) {
  if (user_ids.empty() || group_id == 0) {
    return false;
  }

  if (group_id != group.group_id) {
    return false;
  }

  uint32 now = base::NowMSTime();
  std::map<uint32, UserStatus> user_statuss;

  std::string s_user_ids;
  JoinString(user_ids, ',', &s_user_ids);
  std::string sql = base::StringPrintf("SELECT status,userId FROM IMGroupRelation WHERE groupId = %d AND userId IN (%s) GROUP BY userId ORDER BY id", group_id, s_user_ids.c_str());

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));
  if (answ.get()) {
    while (answ->FetchRow()) {
      UserStatus user_status;
      answ->GetColumn(0, &user_status.status);
      answ->GetColumn(1, &user_status.user_id);
      user_statuss.insert(std::make_pair(user_status.user_id, user_status));
    }
  }
  
  // 创建关系
  sql = "INSERT INTO IMGroupRelation(`groupId`, `userId`, `title`, `groupType`, `created`, `updated`) VALUES ";
  bool is_first = true;
  // 1. 检查数据库中是否存在数据
  for (size_t i=0; i<user_ids.size(); ++i) {
    std::map<uint32, UserStatus>::iterator it = user_statuss.find(user_ids[i]);
    if (it==user_statuss.end()) {
      if (!is_first) {
        sql.append(", ");
      } else {
        is_first = false;
      }
      base::StringAppendF(&sql, "(%d,%d,%d,%d,%d,%d)", group_id, user_ids[i], (group.group_creator_id==user_ids[i] ? 1 : 0), group.group_type, now, now);
    }
  }

  int insert_count = 0;
  
  if (!is_first) {
    insert_count = db_conn->Execute(sql);
  }

  // 更新关系
  sql.clear();
  for (std::map<uint32, UserStatus>::iterator it=user_statuss.begin(); it!=user_statuss.end(); ++it) {
    if (it->second.status == 0) {
      if (!sql.empty()) {
        sql.push_back(',');
      }
      sql.append(base::UintToString(it->first));
    }
  }

  int update_count = 0;
  if (!sql.empty()) {
    sql = base::StringPrintf("UPDATE IMGroupRelation SET status = 1 WHERE groupId = %d AND userId IN (%s)", group_id, sql.c_str());
    update_count = db_conn->Execute(sql);
  }

  // 更新群计数
  sql = base::StringPrintf("UPDATE IMGroup SET memberCnt = memberCnt + %d WHERE groupId = %d LIMIT 1", (insert_count+update_count), group_id);
  db_conn->Execute(sql);
  return true;
}

bool ZAresGroupManagerImpl::QuitGroup(uint32 request_user_id, const std::vector<uint32>& quit_user_ids, uint32 group_id, const GroupInfo& group) {
  if (quit_user_ids.empty() || group_id == 0 || request_user_id == 0 || group_id == 0) {
    return false;
  }

  // 群不存在或不是群创建者
  if (request_user_id != group.group_creator_id || group_id != group.group_id) {
    return false;
  }

  uint32 now = base::NowMSTime();
  std::map<uint32, UserStatus> user_statuss;

  std::string s_quit_user_ids;
  JoinString(quit_user_ids, ',', &s_quit_user_ids);
  std::string sql = base::StringPrintf("SELECT status,userId FROM IMGroupRelation WHERE groupId = %d AND userId in (%s) GROUP BY userId ORDER BY id", group_id, s_quit_user_ids.c_str());

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));
  if (answ.get()) {
    while (answ->FetchRow()) {
      UserStatus user_status;
      answ->GetColumn(0, &user_status.status);
      answ->GetColumn(1, &user_status.user_id);
      user_statuss.insert(std::make_pair(user_status.user_id, user_status));
    }
  }

  int update_count = 0;
  // 更新关系
  sql.clear();
  for (std::map<uint32, UserStatus>::iterator it=user_statuss.begin(); it!=user_statuss.end(); ++it) {
    if (it->second.status != 0) {
      if (!sql.empty()) {
        sql.push_back(',');
      }
      sql.append(base::UintToString(it->first));
    }
  }

  if (!sql.empty()) {
    sql = base::StringPrintf("UPDATE IMGroupRelation SET status = 0, updated=%d  WHERE groupId = %d AND userId IN (%s)", now, group_id, sql.c_str());
    update_count = db_conn->Execute(sql);
  }

  // 更新群计数
  // update IMGroup set memberCnt = memberCnt - ? , updated = ? where groupId = ? limit 1
  sql = base::StringPrintf("UPDATE IMGroup SET memberCnt = memberCnt - %d, updated = %d WHERE groupId = %d LIMIT 1", update_count, now, group_id);
  db_conn->Execute(sql);

  return true;
}
