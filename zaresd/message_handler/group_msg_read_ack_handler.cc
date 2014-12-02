// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/group_msg_read_ack_handler.h"

#include "base/logging.h"
#include "base2/base_types.h"

#include "proto/group_msg_read_ack.h"
#include "proto/db_write_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// 清除用户在这个群的未读消息计数，全部置为已读
int GroupMsgReadAckHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(GroupMsgReadAck, group_msg_read_ack);

  LOG(INFO) << "Clear counter, msg_read_ack: ";

  CounterManager* counter_manager = ModelMainManager::GetInstance()->GetCounterManager();

  uint32 result = 0;
  if (!counter_manager->ClearUserGroupCounter(group_msg_read_ack->req_user_id(), group_msg_read_ack->group_id())) {
    result = 1;
  }

  DBWriteResponse db_write_response;
  db_write_response.SetReserved(group_msg_read_ack->GetReserved());
  db_write_response.set_request_id(0);
  db_write_response.set_result(result);
  db_write_response.set_request_pdu_type(GetHighInt16ByInt32(group_msg_read_ack->message_type()));
  db_write_response.set_from_id(group_msg_read_ack->req_user_id());
  db_write_response.set_to_id(group_msg_read_ack->group_id());

  context->SendSessionData(session_id, db_write_response);

  return 0;
}

