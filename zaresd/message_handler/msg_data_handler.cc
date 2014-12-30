// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/msg_data_handler.h"

#include "base/logging.h"
#include "base2/base_types.h"

#include "proto/msg_data.h"
#include "proto/db_write_response.h"

#include "zaresd/const_zaresd_defines.h"
#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// 发送消息(点对点、群)
int MsgDataHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(MsgData, msg_data);

  MessageManager* message_manager = ModelMainManager::GetInstance()->GetMessageManager();

  DBWriteResponse db_write_response;
  db_write_response.SetReserved(msg_data->GetReserved());
  db_write_response.set_request_id(msg_data->request_id());
  db_write_response.set_result(0);
  db_write_response.set_request_pdu_type(GetHighInt16ByInt32(message->message_type()));
  db_write_response.set_from_id(msg_data->from_user_id());
  db_write_response.set_to_id(msg_data->to_user_id());

  const int MESSAGE_TYPE_IM = 1; // 普通用户+系统消息
  const int MESSAGE_TYPE_IM_AUDIO = 2;
  const int MESSAGE_TYPE_IM_GROUP = 17;
  const int MESSAGE_TYPE_IM_GROUP_AUDIO = 18;

  // 1. check request msg_data
  bool is_sucess = false;
  bool is_group_message = false;

  if (msg_data->from_user_id() == 0 ||
      msg_data->to_user_id() == 0 || 
      msg_data->msg_type() == 0 || 
      msg_data->msg_data().empty() ||
      ( (msg_data->msg_type() == MESSAGE_TYPE_IM || msg_data->msg_type() == MESSAGE_TYPE_IM_GROUP) && msg_data->msg_data().length() > 1536) || // 一般的文本消息
      ( (msg_data->msg_type() == MESSAGE_TYPE_IM_AUDIO || msg_data->msg_type() == MESSAGE_TYPE_IM_GROUP_AUDIO) && msg_data->msg_data().length() > 102400)) {
    LOG(ERROR) << "Check data is invalid!!!!";
    is_sucess = false;
  } else {
    // 内容为空的校验在MessageServer就做掉，直接发送失败
    int msg_type = msg_data->msg_type();
    if (msg_type == MESSAGE_TYPE_IM ) {
      is_sucess = message_manager->SendIMMessage(
          msg_data->from_user_id(),
          msg_data->to_user_id(),
          msg_data->msg_type(),
          msg_data->msg_data(),
          msg_data->create_time());
    } else if (msg_type == MESSAGE_TYPE_IM_AUDIO){
      is_sucess = message_manager->SendAudioMessage(
          msg_data->from_user_id(),
          msg_data->to_user_id(),
          msg_data->msg_data(),
          msg_data->create_time());
    } else if (msg_type == MESSAGE_TYPE_IM_GROUP || msg_type == MESSAGE_TYPE_IM_GROUP_AUDIO) {
      is_group_message = true;
      is_sucess = message_manager->SendIMGroupMessage(
          msg_data->from_user_id(),
          msg_data->to_user_id(),
          msg_data->msg_data(),
          msg_data->create_time());
    }

    if (!is_sucess) { 
      // 发送失败，记一把日志
      // LOG(ERROR) << "";
    } else {
      if(!is_group_message) {
        // DelayUpdateMonitor.getInstance().AddPersonalUpdate(fromUserId, toId, created);
      } else {
        // DelayUpdateMonitor.getInstance().AddGroupUpdate(toId, created);
      }
      // logger.info("发送消息成功 - from:" + fromUserId + ", to: " + toId
      //  + ", messageType: " + messageType + ", content: *");
    }
  }
  db_write_response.set_result(is_sucess ? 0 : 1);

  if (context) {
    context->SendSessionData(io_handler_id, db_write_response);
  }

  return 0;
}
