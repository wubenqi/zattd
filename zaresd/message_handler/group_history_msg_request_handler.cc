// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/group_history_msg_request_handler.h"

#include "base/logging.h"
#include "base2/base_types.h"

#include "proto/group_history_msg_request.h"
#include "proto/group_msg_list_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// 获得群历史消息
int GroupHistoryMsgRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(GroupHistoryMsgRequest, group_history_msg_request);

  CounterManager* counter_manager = ModelMainManager::GetInstance()->GetCounterManager();
  MessageManager* message_manager = ModelMainManager::GetInstance()->GetMessageManager();

  GroupMsgListResponse group_msg_list_response;
  group_msg_list_response.set_req_user_id(group_history_msg_request->req_user_id());
  group_msg_list_response.set_request_cmd_id(GetHighInt16ByInt32(message->message_type()));
  group_msg_list_response.set_request_cmd_id(group_history_msg_request->group_id());
  group_msg_list_response.MutableAttachData()->CopyFrom(group_history_msg_request->GetAttachData());

  message_manager->GetGroupMessages(
      group_history_msg_request->group_id(),
      group_history_msg_request->msg_offset(),
      group_history_msg_request->msg_count(),
      group_msg_list_response.mutable_msg_list());

  context->SendSessionData(session_id, group_msg_list_response);

  return 0;
}
