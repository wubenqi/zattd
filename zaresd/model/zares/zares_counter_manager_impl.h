// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_ZARES_COUNTER_MANAGER_IMPL_H_
#define ZARESD_MODEL_ZARES_COUNTER_MANAGER_IMPL_H_

#include "zaresd/model/counter_manager.h"

class ZAresCounterManagerImpl : public CounterManager {
public:
  ZAresCounterManagerImpl() {}
  virtual ~ZAresCounterManagerImpl() {}

  // 获得用户所有的未读消息
  virtual bool GetUnreadMsgCount(uint32 user_id, Counter* unread_msg_count);

  // 清除用户来自某好友的未读消息计数
  virtual bool ClearUserUnreadItemCount(uint32 user_id, uint32 friend_user_id);

  // 获得用户来自他的某好友的未读消息
  virtual size_t GetUserFriendUnreadCount(uint32 user_id, uint32 friend_user_id);

  // 返回某用户在某个群里的未读消息计数
  virtual size_t GetUserGroupUnreadCount(uint32 user_id, const std::vector<uint32>& group_ids, std::map<uint32, uint32>* unreads);

  virtual bool DeleteUserReadedDialogMessages(uint32 user_id, uint32 friend_user_id);

  //////////////////////////////////////////////////////////////////////////
  // 返回某用户在某群里的未读消息数
  virtual bool GetUserGroupCount(uint32 user_id, uint32 group_id, GroupCounterItem* item);

  // 清除用户对应的某个群组的计数
  virtual bool ClearUserGroupCounter(uint32 user_id, uint32 group_id);
};

#endif
