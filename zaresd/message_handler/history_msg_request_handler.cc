// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/history_msg_request_handler.h"

#include "base/logging.h"
#include "base2/base_types.h"

#include "proto/history_msg_request.h"
#include "proto/msg_list_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

#define  MAX_HISTORY_MESSAGE_COUNT 50

// 读取历史消息,一次读取最多20条
int HistoryMsgRequestHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(HistoryMsgRequest, history_msg_request);

  MessageManager* message_manager = ModelMainManager::GetInstance()->GetMessageManager();

  MsgListResponse msg_list_response;
  msg_list_response.SetReserved(history_msg_request->GetReserved());
  msg_list_response.set_request_cmd_id(GetHighInt16ByInt32(message->message_type()));
  msg_list_response.set_from_user_id(history_msg_request->from_user_id());
  msg_list_response.set_to_user_id(history_msg_request->to_user_id());
  msg_list_response.SetAttachData(*history_msg_request->GetAttachData());


  uint32 count = history_msg_request->msg_count() > MAX_HISTORY_MESSAGE_COUNT ? MAX_HISTORY_MESSAGE_COUNT : history_msg_request->msg_count();

  // 
  message_manager->GetDialogMessages(
      history_msg_request->from_user_id(),
      history_msg_request->to_user_id(),
      history_msg_request->msg_offset(),
      count,
      msg_list_response.mutable_msg_list());

  context->SendSessionData(io_handler_id, msg_list_response);

  return 0;
}
