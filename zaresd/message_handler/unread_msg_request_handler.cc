// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// �˴���Ϊ�Զ����ɣ����ں�������ʵ�������߼�
//

#include "zaresd/message_handler/unread_msg_request_handler.h"

#include "base/logging.h"
#include "base2/base_types.h"

#include "proto/unread_msg_request.h"
#include "proto/msg_list_response.h"

#include "zaresd/const_zaresd_defines.h"
#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// ��ȡδ����Ϣ, һ�ζ�ȡ���50��
int UnreadMsgRequestHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(UnreadMsgRequest, unread_msg_request);

  CounterManager* counter_mananger = ModelMainManager::GetInstance()->GetCounterManager();
  MessageManager* message_mananger = ModelMainManager::GetInstance()->GetMessageManager();

  MsgListResponse msg_list_response;
  msg_list_response.SetReserved(unread_msg_request->GetReserved());
  msg_list_response.set_request_cmd_id(GetHighInt16ByInt32(message->message_type()));
  msg_list_response.set_from_user_id(unread_msg_request->from_user_id());
  msg_list_response.set_to_user_id(unread_msg_request->to_user_id());
  msg_list_response.SetAttachData(*unread_msg_request->GetAttachData());

  uint32 count = counter_mananger->GetUserFriendUnreadCount(unread_msg_request->from_user_id(), unread_msg_request->to_user_id(), unread_msg_request->client_type());
  count = count > UNREAD_MAX_COUNTER ? UNREAD_MAX_COUNTER : count;
  if (count > 0) {
    message_mananger->GetMessages(
        unread_msg_request->from_user_id(),
        unread_msg_request->to_user_id(),
        0,
        count,
        msg_list_response.mutable_msg_list());

    // TODO:
    //  LOG(INFO) << "";
  } else {
    // TODO:
    //  LOG(ERROR) << "";
  }

  context->SendSessionData(io_handler_id, msg_list_response);

  return 0;
}
