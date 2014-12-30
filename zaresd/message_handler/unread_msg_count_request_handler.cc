// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// �˴���Ϊ�Զ����ɣ����ں�������ʵ�������߼�
//

#include "zaresd/message_handler/unread_msg_count_request_handler.h"

#include "base/logging.h"
#include "base/strings/stringprintf.h"
#include "base/memory/scoped_ptr.h"

#include "proto/unread_msg_count_request.h"
#include "proto/unread_msg_count_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// ���δ����Ϣ����
int UnreadMsgCountRequestHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(UnreadMsgCountRequest, unread_msg_count_request);

  CounterManager* counter_manager = ModelMainManager::GetInstance()->GetCounterManager();

  UnreadMsgCountResponse unread_msg_count_response;
  unread_msg_count_response.SetReserved(unread_msg_count_request->GetReserved());
  unread_msg_count_response.set_to_user_id(unread_msg_count_request->user_id());
  unread_msg_count_response.SetAttachData(*unread_msg_count_request->GetAttachData());

  Counter user_unread_count;
  counter_manager->GetUnreadMsgCount(unread_msg_count_request->user_id(), unread_msg_count_request->client_type(), &user_unread_count);

  const std::map<uint32, uint32>& unread_count = user_unread_count.unread_count();

  for (std::map<uint32, uint32>::const_iterator it=unread_count.begin(); it!=unread_count.end(); ++it) {
    UserUnreadMsgCount* unread = unread_msg_count_response.add_user_unread_list();
    unread->from_user_id = it->first;
    unread->unread_msg_count = it->second;
  }

  context->SendSessionData(io_handler_id, unread_msg_count_response);

  return 0;
}
