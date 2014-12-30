// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/msg_read_ack_handler.h"

#include "base/logging.h"
#include "base/strings/stringprintf.h"
#include "base/memory/scoped_ptr.h"
#include "base2/base_types.h"

#include "proto/msg_read_ack.h"
#include "proto/db_write_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// 未读消息清零
// 清理消息计数，已读
int MsgReadAckHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  // <int>requestId</int>
  // <int>userId</int> --> from_user_id
  // <int>friendUserId</int> --> to_user_id

  CAST_PROTO_MESSAGE(MsgReadAck, msg_read_ack);

  LOG(INFO) << "Clear counter, msg_read_ack: ";

  CounterManager* counter_manager = ModelMainManager::GetInstance()->GetCounterManager();
  DBWriteResponse db_write_response;
  db_write_response.SetReserved(msg_read_ack->GetReserved());
  db_write_response.set_request_id(msg_read_ack->request_id());
  db_write_response.set_result(0);
  db_write_response.set_request_pdu_type(GetHighInt16ByInt32(message->message_type()));
  db_write_response.set_from_id(msg_read_ack->from_user_id());
  db_write_response.set_to_id(msg_read_ack->to_user_id());

  if (!counter_manager->ClearUserUnreadItemCount(msg_read_ack->from_user_id(), msg_read_ack->to_user_id(), msg_read_ack->client_type())) {
    // todo:
    //  LOG(ERROR) << "";
    db_write_response.set_result(1);
  }
  counter_manager->DeleteUserReadedDialogMessages(msg_read_ack->from_user_id(), msg_read_ack->to_user_id(), msg_read_ack->client_type());

  context->SendSessionData(io_handler_id, db_write_response);

  return 0;
}

