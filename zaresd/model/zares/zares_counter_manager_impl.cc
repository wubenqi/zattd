// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/zares/zares_counter_manager_impl.h"

bool ZAresCounterManagerImpl::GetUnreadMsgCount(uint32 user_id, Counter* unread_msg_count) {
  return true;
}

bool ZAresCounterManagerImpl::ClearUserUnreadItemCount(uint32 user_id, uint32 friend_user_id) {
  return true;
}

size_t ZAresCounterManagerImpl::GetUserFriendUnreadCount(uint32 user_id, uint32 friend_user_id) {
  return 0;
}

size_t ZAresCounterManagerImpl::GetUserGroupUnreadCount(uint32 userId, const std::vector<uint32>& group_ids, std::map<uint32, uint32>* unreads) {
  return 0;
}

bool ZAresCounterManagerImpl::DeleteUserReadedDialogMessages(uint32 user_id, uint32 friend_user_id) {
  return true;
}

bool ZAresCounterManagerImpl::GetUserGroupCount(uint32 user_id, uint32 group_id, GroupCounterItem* item) {
  return true;
}

bool ZAresCounterManagerImpl::ClearUserGroupCounter(uint32 user_id, uint32 group_id) {
  return true;
}
