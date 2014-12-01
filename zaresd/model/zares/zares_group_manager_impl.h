// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_ZARES_ZARES_GROUP_MANAGER_IMPL_H_
#define ZARESD_MODEL_ZARES_ZARES_GROUP_MANAGER_IMPL_H_

#include "zaresd/model/group_manager.h"

namespace db {
class CdbConnPoolManager;
}

class ZAresGroupManagerImpl : public GroupManager {
public:
  ZAresGroupManagerImpl(db::CdbConnPoolManager* db_conn_pool) :
    db_conn_pool_(db_conn_pool) {}
  virtual ~ZAresGroupManagerImpl() {}

  // 获取某用户加入的群个数
  virtual size_t GetGroupsByUserId(uint32 user_id, bool is_fixed_group, std::vector<GroupInfo*>* groups);
  virtual size_t GetGroupIdsByUserId(uint32 user_id, bool is_fixed_group, std::vector<uint32>* group_ids);

  virtual size_t GetGroupMembers(const std::vector<uint32>& group_ids, GroupRelationInfoListMap* group_relations_map);
  // 获取单个群的成员关系列表
  virtual size_t GetGroupMembers(uint32 group_id, GroupRelationInfoList* group_relations);

  // 获取某用户加入的群个数,最多100个
  // virtual size_t GetGroupsByUserId(uint32 user_id, GroupRelationInfoList* group_relations) = 0;

  // 获取单个群组的信息
  virtual const GroupInfo* GetGroupInfo(uint32 groupId, GroupInfo* group);

  // 获取某用户加入的群个数,最多100个
  virtual size_t GetRecentGroupsByUserId(uint32 user_id, std::vector<GroupInfo*>* groups);

  // 创建群
  virtual bool CreateGroup(uint32 create_user_id, const std::string& group_name, uint32 group_type,
    const std::string& avatar, const std::string& adesc, const std::vector<uint32>& member_user_ids, GroupInfo* group);

  // 加入群
  virtual bool JoinGroup(const std::vector<uint32>& user_ids, uint32 group_id, const GroupInfo& group);

  // 退出群
  virtual bool QuitGroup(uint32 request_user_id, const std::vector<uint32>& quit_user_ids, uint32 group_id, const GroupInfo& group);

private:
  db::CdbConnPoolManager* db_conn_pool_;

};

#endif
