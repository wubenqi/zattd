// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// �˴���Ϊ�Զ����ɣ����ں�������ʵ�������߼�
//

#include "zaresd/message_handler/group_history_msg_request_handler.h"

#include "base/logging.h"
#include "base2/base_types.h"

#include "proto/group_history_msg_request.h"
#include "proto/group_msg_list_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// ���Ⱥ��ʷ��Ϣ
int GroupHistoryMsgRequestHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(GroupHistoryMsgRequest, group_history_msg_request);

  CounterManager* counter_manager = ModelMainManager::GetInstance()->GetCounterManager();
  MessageManager* message_manager = ModelMainManager::GetInstance()->GetMessageManager();

  GroupMsgListResponse group_msg_list_response;
  group_msg_list_response.SetReserved(group_history_msg_request->GetReserved());
  group_msg_list_response.set_req_user_id(group_history_msg_request->req_user_id());
  group_msg_list_response.set_request_cmd_id(GetHighInt16ByInt32(message->message_type()));
  group_msg_list_response.set_request_cmd_id(group_history_msg_request->group_id());
  group_msg_list_response.SetAttachData(*group_history_msg_request->GetAttachData());

  message_manager->GetGroupMessages(
      group_history_msg_request->group_id(),
      group_history_msg_request->msg_offset(),
      group_history_msg_request->msg_count(),
      group_msg_list_response.mutable_msg_list());

  context->SendSessionData(io_handler_id, group_msg_list_response);

  return 0;
}
