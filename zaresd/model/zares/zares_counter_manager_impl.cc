// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/zares/zares_counter_manager_impl.h"

#include "zaresd/const_zaresd_defines.h"

// 17 -> "IOS"
// 18 -> "ANDROID"
// other -> ""

// public enum CachePoolName {
//   counter, // 所有计数器
//   unread, // 未读计数器
//   //		cinfo,	//用户信息(消息通知用的).
//   //		cinfo_push, // 推送cinfo
//   group_counter
// }

// STRICT 

// CacheManager cache_manager_;


void ZAresCounterManagerImpl::IncrUserMsgCount(uint32 from_user_id, uint32 to_user_id) {

}

const Counter* ZAresCounterManagerImpl::GetUnreadMsgCount(uint32 user_id, uint32 client_type, Counter* unread_msg_count) {
  if (user_id == 0) {
    return NULL;
  }

  std::map<uint32, uint32>* unread_count = cache_.FindUnreadCount(user_id, client_type);
  if (unread_count == NULL) {
    return NULL;
  }

  unread_msg_count->set_user_id(user_id);
  int limit = 0;
  for (std::map<uint32, uint32>::iterator it=unread_count->begin(); it!=unread_count->end() && limit<300; ++it, ++limit) {
    unread_msg_count->mutable_unread_count()->insert(std::make_pair(it->first, it->second));
  }

  return unread_msg_count;
}

bool ZAresCounterManagerImpl::ClearUserUnreadItemCount(uint32 user_id, uint32 friend_user_id, uint32 client_type) {

  if (user_id == 0 || friend_user_id == 0) {
    return false;
  }

  std::map<uint32, uint32>* unread_count = cache_.FindUnreadCount(user_id, client_type);
  if (unread_count == NULL) {
    return false;
  }

  std::map<uint32, uint32>::iterator it = unread_count->find(friend_user_id);
  if (it!=unread_count->end()) {
    unread_count->erase(it);
  }

  return true;
}

size_t ZAresCounterManagerImpl::GetUserFriendUnreadCount(uint32 user_id, uint32 friend_user_id, uint32 client_type) {
  size_t unread_count = 0;
  if (user_id != 0 && friend_user_id != 0) {
    std::map<uint32, uint32>* unread_counts = cache_.FindUnreadCount(user_id, client_type);
    if (unread_count == NULL) {
      return false;
    }

    std::map<uint32, uint32>::iterator it = unread_counts->find(friend_user_id);
    if (it!=unread_counts->end()) {
      unread_count = it->second;
    }
  }
  return unread_count;
}

size_t ZAresCounterManagerImpl::GetUserGroupUnreadCount(uint32 userId, const std::vector<uint32>& group_ids, uint32 client_type, std::map<uint32, uint32>* unreads) {

  if (userId == 0 || group_ids.empty() || unreads == NULL) {
    return 0;
  }

  for (size_t i=0; i<group_ids.size(); ++i) {
    GroupCounterItem counter_item;
    GetUserGroupCount(userId, group_ids[i], client_type, &counter_item);
    unreads->insert(std::make_pair(group_ids[i], counter_item.user_unread_count));
  }

  return unreads->size();
}

bool ZAresCounterManagerImpl::DeleteUserReadedDialogMessages(uint32 user_id, uint32 friend_user_id, uint32 client_type) {
  return true;
}

const GroupCounterItem* ZAresCounterManagerImpl::GetUserGroupCount(uint32 user_id, uint32 client_type, uint32 group_id, GroupCounterItem* item) {
  item->user_id = user_id;
  item->group_id = group_id;
  item->group_total_count = 0;
  item->user_unread_count = 0;
  item->last_message_id = 0;

  if (user_id == 0 || group_id == 0) {
    return item;
  }

  uint32 total_count = cache_.GetGroupTotalCount(group_id);
  if (total_count == 0) {
    return item;
  }
  item->group_total_count = total_count;

  ReadCountAndLastID* counter_and_last_id = cache_.FindCounterAndLastIDs(user_id, group_id, client_type);
  if (counter_and_last_id) {
    // item->user_unread_count = counter_and_last_id->counter;
    item->last_message_id = counter_and_last_id->last_id;

    uint32 unread_count = total_count - counter_and_last_id->read_count;
    unread_count = unread_count > GROUP_UNREAD_MAX_COUNTER ? GROUP_UNREAD_MAX_COUNTER : unread_count;
    item->user_unread_count = unread_count;
  }

  return item;
}

bool ZAresCounterManagerImpl::ClearUserGroupCounter(uint32 user_id, uint32 group_id, uint32 client_type) {
  ReadCountAndLastID* counter_and_last_id = cache_.FindCounterAndLastIDs(user_id, group_id, client_type);
  if (counter_and_last_id) {
    counter_and_last_id->last_id = 0;
    counter_and_last_id->read_count = 0;
  }
  return true;
}
