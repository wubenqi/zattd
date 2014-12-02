// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/group_unread_msg_count_request_handler.h"

#include "base/logging.h"

#include "proto/group_unread_msg_count_request.h"
#include "proto/group_unread_msg_count_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// 获取群未读消息
int GroupUnreadMsgCountRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(GroupUnreadMsgCountRequest, group_unread_msg_count_request);

  GroupManager* group_manger = ModelMainManager::GetInstance()->GetGroupManager();
  CounterManager* counter_manger = ModelMainManager::GetInstance()->GetCounterManager();

  GroupUnreadMsgCountResponse group_unread_msg_count_response;
  group_unread_msg_count_response.SetReserved(group_unread_msg_count_request->GetReserved());
  group_unread_msg_count_response.set_req_user_id(group_unread_msg_count_request->req_user_id());
  group_unread_msg_count_response.SetAttachData(*group_unread_msg_count_request->GetAttachData());

  std::vector<uint32> group_ids;
  std::map<uint32, uint32> unreads;

  group_manger->GetGroupIdsByUserId(group_unread_msg_count_request->req_user_id(),  false, &group_ids);
  counter_manger->GetUserGroupUnreadCount(group_unread_msg_count_request->req_user_id(), group_ids, &unreads);

  for (std::map<uint32, uint32>::iterator it=unreads.begin(); it!=unreads.end(); ++it) {
    GroupUnreadMsgCount* unread = group_unread_msg_count_response.add_group_unread_list();
    unread->group_id = it->first;
    unread->unread_msg_count = it->second;
  }
  
  context->SendSessionData(session_id, group_unread_msg_count_response);

  return 0;
}
