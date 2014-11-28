// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_COUNTER_MANAGER_H_
#define ZARESD_MODEL_COUNTER_MANAGER_H_

#include "base/basictypes.h"

#include <vector>
#include <map>

class Counter {
public:
  inline uint32 user_id() const { return user_id_; }
  inline void set_user_id(uint32 val) { user_id_ = val; }

  inline const std::map<uint32, uint32>& unread_count() const { return unread_count_; }
  inline const std::map<uint32, uint32>& msg_count() const { return msg_count_; }

private:
  uint32 user_id_;
  std::map<uint32, uint32> unread_count_;
  std::map<uint32, uint32> msg_count_;
};

struct GroupCounterItem {
  uint32 user_id;
  uint32 group_id;
  uint32 group_total_count; // 群总消息数
  uint32 user_unread_count; // 用户在该群中的未读消息数
  uint32 last_message_id;
};

class CounterManager {
public:
  virtual ~CounterManager() {}

  // 获得用户所有的未读消息
  virtual bool GetUnreadMsgCount(uint32 user_id, Counter* unread_msg_count) = 0;

  // 清除用户来自某好友的未读消息计数
  virtual bool ClearUserUnreadItemCount(uint32 user_id, uint32 friend_user_id) = 0;

  // 获得用户来自他的某好友的未读消息
  virtual size_t GetUserFriendUnreadCount(uint32 user_id, uint32 friend_user_id) = 0;

  // 返回某用户在某个群里的未读消息计数
  virtual size_t GetUserGroupUnreadCount(uint32 user_id, const std::vector<uint32>& group_ids, std::map<uint32, uint32>* unreads) = 0;

  // 根据用户ID和其对话的用户ID删除用户(前者)的所有已读对话消息,单向数据
  virtual bool DeleteUserReadedDialogMessages(uint32 user_id, uint32 friend_user_id) = 0;

  //////////////////////////////////////////////////////////////////////////
  // 返回某用户在某群里的未读消息数
  virtual bool GetUserGroupCount(uint32 user_id, uint32 group_id, GroupCounterItem* item) = 0;

  // 清除用户对应的某个群组的计数
  virtual bool ClearUserGroupCounter(uint32 user_id, uint32 group_id) = 0;

};

#endif
