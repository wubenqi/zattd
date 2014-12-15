// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请不要随意改动
//

#include "zaresd/message_handler/message_handler.h"

#include "base/lazy_instance.h"
#include "base/hash_tables.h"

#include "proto/const_message_pdu_types.h"

#include "zaresd/zares_handler_thread.h"

#include "zaresd/message_handler/validate_request_handler.h"
#include "zaresd/message_handler/all_user_request_handler.h"
#include "zaresd/message_handler/department_request_handler.h"
#include "zaresd/message_handler/friend_list_request_handler.h"
#include "zaresd/message_handler/history_msg_request_handler.h"
#include "zaresd/message_handler/msg_data_handler.h"
#include "zaresd/message_handler/msg_read_ack_handler.h"
#include "zaresd/message_handler/remove_session_request_handler.h"
#include "zaresd/message_handler/unread_msg_count_request_handler.h"
#include "zaresd/message_handler/unread_msg_request_handler.h"
#include "zaresd/message_handler/users_info_request_handler.h"
#include "zaresd/message_handler/validate_request_handler.h"

#include "zaresd/message_handler/group_change_member_request_handler.h"
#include "zaresd/message_handler/group_create_tmp_group_request_handler.h"
#include "zaresd/message_handler/group_dialog_list_request_handler.h"
#include "zaresd/message_handler/group_history_msg_request_handler.h"
#include "zaresd/message_handler/group_list_request_handler.h"
#include "zaresd/message_handler/group_msg_read_ack_handler.h"
#include "zaresd/message_handler/group_unread_msg_count_request_handler.h"
#include "zaresd/message_handler/group_unread_msg_request_handler.h"
#include "zaresd/message_handler/group_user_list_request_handler.h"

#include "zaresd/message_handler/file_add_offline_req_handler.h"
#include "zaresd/message_handler/file_del_offline_req_handler.h"
#include "zaresd/message_handler/file_has_offline_req_handler.h"

typedef int (*ExecuteHandlerFunc)(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message);
// int (*execute_handler)(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message);

struct MessageHandler {
  MessageHandler() :
    status(0),
    execute_handler(NULL) {}

  MessageHandler(ExecuteHandlerFunc func) :
    status(0),
    execute_handler(func) {}

  uint16 status;
  ExecuteHandlerFunc execute_handler;
  //int (*execute_handler)(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message);
};

typedef base::hash_map<uint32, MessageHandler> MessageHandlerMap;

static base::LazyInstance<MessageHandlerMap>::Leaky g_message_handlers = LAZY_INSTANCE_INITIALIZER;

void  InitMessageHandlerTable() {
  // DB storage server related
  g_message_handlers.Get()[MESSAGE_VALIDATE_REQUEST] = MessageHandler(&ValidateRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_FRIEND_LIST_REQUEST] = MessageHandler(&FriendListRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_REMOVE_SESSION_REQUEST] = MessageHandler(&RemoveSessionRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_DEPARTMENT_REQUEST] = MessageHandler(&DepartmentRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_USERS_INFO_REQUEST] = MessageHandler(&UsersInfoRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_ALL_USER_REQUEST] = MessageHandler(&AllUserRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_MSG_DATA] = MessageHandler(&MsgDataHandler::Execute);
  g_message_handlers.Get()[MESSAGE_UNREAD_MSG_COUNT_REQUEST] = MessageHandler(&UnreadMsgCountRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_UNREAD_MSG_REQUEST] = MessageHandler(&UnreadMsgRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_MSG_READ_ACK] = MessageHandler(&MsgReadAckHandler::Execute);
  // MESSAGE_DB_QUERY_REQUEST

  // pdu with business server
  g_message_handlers.Get()[MESSAGE_GROUP_LIST_REQUEST] = MessageHandler(&GroupListRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_GROUP_USER_LIST_REQUEST] = MessageHandler(&GroupUserListRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_GROUP_UNREAD_MSG_COUNT_REQUEST] = MessageHandler(&GroupUnreadMsgCountRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_GROUP_UNREAD_MSG_REQUEST] = MessageHandler(&GroupUnreadMsgRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_GROUP_HISTORY_MSG_REQUEST] = MessageHandler(&GroupHistoryMsgRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_GROUP_MSG_READ_ACK] = MessageHandler(&GroupMsgReadAckHandler::Execute);
  g_message_handlers.Get()[MESSAGE_GROUP_CREATE_TMP_GROUP_REQUEST] = MessageHandler(&GroupCreateTmpGroupRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_GROUP_CHANGE_MEMBER_REQUEST] = MessageHandler(&GroupChangeMemberRequestHandler::Execute);
  g_message_handlers.Get()[MESSAGE_GROUP_DIALOG_LIST_REQUEST] = MessageHandler(&GroupDialogListRequestHandler::Execute);

  // to storage server
  g_message_handlers.Get()[MESSAGE_FILE_HAS_OFFLINE_REQ] = MessageHandler(&FileHasOfflineReqHandler::Execute);
  g_message_handlers.Get()[MESSAGE_FILE_ADD_OFFLINE_REQ] = MessageHandler(&FileAddOfflineReqHandler::Execute);
  g_message_handlers.Get()[MESSAGE_FILE_DEL_OFFLINE_REQ] = MessageHandler(&FileDelOfflineReqHandler::Execute);
}

int DispatchMessageHandler(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  MessageHandlerMap::iterator it = g_message_handlers.Get().find(message->message_type());
  if (it == g_message_handlers.Get().end()) {
    LOG(ERROR) << "Not impl handler: " << message->message_type();
  } else {
    (it->second.execute_handler)(context, session_id, message);
  }
  return 0;
}

bool CheckMessageHandler(uint32 message_type) {
  return g_message_handlers.Get().find(message_type) != g_message_handlers.Get().end();
}
