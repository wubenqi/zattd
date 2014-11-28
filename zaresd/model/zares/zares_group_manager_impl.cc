// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/zares/zares_group_manager_impl.h"

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/stringprintf.h"
#include "base2/string_util2.h"
#include "base2/time2.h"

#include "db/database_util.h"

#include "db/conn_pool_manager.h"

size_t ZAresGroupManagerImpl::GetGroupsByUserId(uint32 user_id, bool is_fixed_group, std::vector<GroupInfo*>* groups) {
  if (groups == NULL || user_id == 0) {
    LOG(ERROR) << "groups is NULL or user_id is 0!!!!";
    return 0;
  }

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  std::string sql = base::StringPrintf(
      "SELECT groupId,groupName,avatar,createUserId,groupType,updated FROM IMGroup WHERE groupId IN "
      "(SELECT groupId FROM IMGroupRelation WHERE userId=%d AND status>=1 %s ORDER BY created DESC, id DESC LIMIT %d)",
      user_id,
      (is_fixed_group ? " AND groupType = 1 " : ""),
      (is_fixed_group ? 200 : 5000));

  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    while(answ->FetchRow()) {
      GroupInfo* group = new GroupInfo();
      group->ParseFromDatabase(*answ);
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
    "(SELECT groupId FROM IMGroupRelation WHERE userId=%d AND status>=1 %s ORDER BY created DESC, id DESC LIMIT %d)",
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
      "SELECT groupId,userId FROM IMGroupRelation WHERE groupId in (%s) AND status >= 1 OEDER BY created ASC LIMIT 10000", s_group_ids.c_str());

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
    "SELECT groupId,userId FROM IMGroupRelation WHERE groupId=%d AND status >= 1 OEDER BY created ASC LIMIT 10000", group_id);

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
    "SELECT groupId,groupName,avatar,createUserId,groupType,updated FROM IMGroup WHERE group_id=%d AND ststus>=1", group_id);

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    if(answ->FetchRow()) {
      group->ParseFromDatabase(*answ);
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
      "(SELECT groupId FROM IMGroupRelation WHERE userId=%d AND status=1 %s ORDER BY updated DESC, id DESC LIMIT 100)",
      user_id);

  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));

  if (answ.get()) {
    while(answ->FetchRow()) {
      GroupInfo* group = new GroupInfo();
      group->ParseFromDatabase(*answ);
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

  #define kCreateGroupQuery "INSERT INTO IMGroup(`groupName`,`avatar`,`adesc`,`createUserId`,`groupType`,`memberCnt`,`created`,`updated`) VALUES(:1,:2,:3,:4,:5,0,:7,:8)"

  group->group_id = 0;
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
  MakeQueryString(kCreateGroupQuery, &p, &sql);

  uint64 group_id = 0;
  {
    db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
    uint64 group_id = db_conn->ExecuteInsertID(sql);
    if (group_id>0) {
      group->group_id = group_id;
      group->group_name = group_name;
      group->group_avatar = avatar;
      group->group_type = group_type;
      group->group_updated = base::NowMSTime()/1000;
    }
  }

  if (group_id > 0) {
    return JoinGroup(member_user_ids, group_id, *group);
  }

  return false;
}

bool ZAresGroupManagerImpl::JoinGroup(const std::vector<uint32>& user_ids, uint32 group_id, const GroupInfo& group) {
#if 0
  logger.info("seisei join group! groupId:" + groupId);
  if (userIds == null || userIds.length <= 0 || groupId <= 0) {
    return false;
  }
  if (group == null || group.getGroupId() != groupId) { // 群不存在
    group = this.getGroupInfo(groupId); // 获得群信息
    if (group == null || group.getGroupId() != groupId) {
      return false;
    }
  }

  Map<Integer, Integer> mapUserIds = MoguUtil.distinctToMap(userIds); // 去重

  DBManager dbManager = DBManager.getInstance();
  Connection conn = dbManager.getConnection(DBPoolName.macim_master);
  PreparedStatement statement = null;
  ResultSet rs = null;
  int time = (int) (System.currentTimeMillis() / 1000);
  int countAddedNum = 0;
  try {
    logger.info("seisei join group! select phase");
    String selectClause = MoguUtil.getArgsHolder(mapUserIds.size());
    String sqlGetRelation = "select * from IMGroupRelation where groupId = ? and userId in (";
    sqlGetRelation += selectClause + ") group by userId order by id";

    statement = conn.prepareStatement(sqlGetRelation);
    statement.setInt(1, groupId);
    Iterator<Integer> itr = mapUserIds.keySet().iterator();
    int i = 1;
    while (itr.hasNext()) {
      statement.setObject(++i, itr.next());
    }
    rs = statement.executeQuery();

    List<Integer> updateUids = new ArrayList<Integer>();
    int uid = 0;
    int status;
    while (rs.next()) {
      status = rs.getInt("status");
      uid = rs.getInt("userId");
      mapUserIds.remove(uid); // 表里已经有了就不用插入了
      if (status == 0) { // 之前退出过更新就可以了
        updateUids.add(uid);
      }
    }
    rs.close();
    statement.close();

    // 创建关系
    int createUserId = group.getCreateUserId();
    int groupType = group.getGroupType();
    int insertSize = mapUserIds.size();
    int insertCount = 0;
    if (insertSize > 0) {
      logger.info("seisei join group! add phase");
      String addClause = MoguUtil.getArgsHolder("(?, ?, ?, ?, ?, ?)",
        ",", insertSize);
      String sqlAddRelation = "insert into IMGroupRelation(`groupId`, `userId`, `title`, `groupType`, `created`, `updated`) "
        + "values " + addClause;
      statement = conn.prepareStatement(sqlAddRelation);
      Iterator<Integer> iter = mapUserIds.values().iterator();
      int index = 1;
      while (iter.hasNext()) {
        uid = iter.next();
        statement.setInt(index++, groupId);
        statement.setInt(index++, uid);
        statement.setInt(index++, createUserId == uid ? 1 : 0);
        statement.setInt(index++, groupType);
        statement.setInt(index++, time);
        statement.setInt(index++, time);
      }
      insertCount = statement.executeUpdate();
      statement.close();
    }

    // 更新关系
    int updateSize = updateUids.size();
    int updateCount = 0;
    if (updateSize > 0) {
      logger.info("seisei join group! update phase");
      String updateClause = MoguUtil.getArgsHolder(insertSize);
      String sqlUpdateRelation = "update IMGroupRelation set status = 1 where groupId = ? and userId in (";
      sqlUpdateRelation += updateClause + ")";
      statement = conn.prepareStatement(sqlUpdateRelation);
      int index = 1;
      statement.setInt(index++, groupId);
      for (int j = 0; j < updateSize; j++) {
        statement.setInt(index++, updateUids.get(j));
      }
      updateCount = statement.executeUpdate();
      statement.close();
    }

    // 更新群计数
    countAddedNum = insertCount + updateCount;
    if (countAddedNum > 0) {
      logger.info("seisei join group! update count phase");
      String sqlUpdateMemberCnt = "update IMGroup set memberCnt = memberCnt + ? where groupId = ? limit 1";
      statement = conn.prepareStatement(sqlUpdateMemberCnt);
      statement.setInt(1, countAddedNum);
      statement.setInt(2, groupId);
      statement.executeUpdate();
    }
  } catch (SQLException e) {
    throw e;
  } finally {
    dbManager.release(DBPoolName.macim_master, conn, statement, rs);
  }
  if (countAddedNum > 0) { // 成功
    return true;
  }
  return false;
#endif

  return true;
}

bool ZAresGroupManagerImpl::QuitGroup(uint32 request_user_id, uint32 group_id, const std::vector<uint32>& quit_user_ids) {
#if 0
  if (requestUserId <= 0 || userIds == null || userIds.length <= 0
    || groupId <= 0) {
      return false;
  }
  if (group == null || group.getGroupId() != groupId
    || requestUserId != group.getCreateUserId()) { // 群不存在或不是群创建者
      group = this.getGroupInfo(groupId);
      if (group == null || group.getGroupId() != groupId
        || requestUserId != group.getCreateUserId()) {
          return false;
      }
  }

  Map<Integer, Integer> mapUserIds = MoguUtil.distinctToMap(userIds); // 去重

  DBManager dbManager = DBManager.getInstance();
  Connection conn = dbManager.getConnection(DBPoolName.macim_master);
  PreparedStatement statement = null;
  ResultSet rs = null;
  int time = (int) (System.currentTimeMillis() / 1000);
  int countDelete = 0;
  try {
    String selectClause = MoguUtil.getArgsHolder(mapUserIds.size());
    String sqlGetRelation = "select * from IMGroupRelation where groupId = ? and userId in (";
    sqlGetRelation += selectClause + ") group by userId";
    statement = conn.prepareStatement(sqlGetRelation);
    statement.setInt(1, groupId);
    Iterator<Integer> itr = mapUserIds.keySet().iterator();
    int i = 1;
    while (itr.hasNext()) {
      statement.setInt(++i, itr.next());
    }
    rs = statement.executeQuery();

    List<Integer> updateUids = new ArrayList<Integer>();
    int status;
    int uid = 0;
    while (rs.next()) {
      status = rs.getInt("status");
      uid = rs.getInt("userId"); // 在表里，表明是该群成员
      if (status != 0) { // 在表里，而且未退出群更新状态为退出群就可以了
        updateUids.add(uid);
      }
    }

    // 更新关系
    int updateSize = updateUids.size();
    if (updateSize > 0) {
      String updateClause = MoguUtil.getArgsHolder(updateSize);
      String sqlUpdateRelation = "update IMGroupRelation set status = 0, updated = ? where groupId = ? and userId in (";
      sqlUpdateRelation += updateClause + ")";
      statement = conn.prepareStatement(sqlUpdateRelation);
      int index = 1;
      statement.setInt(index++, time);
      statement.setInt(index++, groupId);
      for (int j = 0; j < updateSize; j++) {
        statement.setInt(index++, updateUids.get(j));
      }
      countDelete = statement.executeUpdate();
    }

    // 更新群计数
    if (countDelete > 0) {
      String sqlUpdateMemberCnt = "update IMGroup set memberCnt = memberCnt - ? , updated = ? where groupId = ? limit 1";
      statement = conn.prepareStatement(sqlUpdateMemberCnt);
      int index = 1;
      statement.setInt(index++, countDelete);
      statement.setInt(index++, time);
      statement.setInt(index++, groupId);
      statement.executeUpdate();
    }
  } catch (SQLException e) {
    throw e;
  } finally {
    dbManager.release(DBPoolName.macim_master, conn, statement, rs);
  }
  if (countDelete > 0) { // 成功
    return true;
  }
  return false;

#endif

  return true;
}
