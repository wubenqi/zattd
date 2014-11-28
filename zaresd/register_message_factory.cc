// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "message_pdu/message_pdu_factory_manager.h"

#include "base/logging.h"

#include "proto/validate_request.h"
#include "proto/all_user_request.h"
#include "proto/all_user_response.h"
#include "proto/db_query_request.h"
#include "proto/db_query_response.h"
#include "proto/db_write_response.h"
#include "proto/department_request.h"
#include "proto/department_response.h"
#include "proto/file_add_offline_req.h"
#include "proto/file_del_offline_req.h"
#include "proto/file_has_offline_req.h"
#include "proto/file_has_offline_res.h"
#include "proto/friend_list_request.h"
#include "proto/friend_list_response.h"
#include "proto/group_change_member_notify.h"
#include "proto/group_change_member_request.h"
#include "proto/group_change_member_response.h"
#include "proto/group_create_normal_group_notify.h"
#include "proto/group_create_tmp_group_request.h"
#include "proto/group_create_tmp_group_response.h"
#include "proto/group_dialog_list_request.h"
#include "proto/group_dialog_list_response.h"
#include "proto/group_history_msg_request.h"
#include "proto/group_list_request.h"
#include "proto/group_list_response.h"
#include "proto/group_msg_list_response.h"
#include "proto/group_msg_read_ack.h"
#include "proto/group_unread_msg_count_request.h"
#include "proto/group_unread_msg_count_response.h"
#include "proto/group_unread_msg_request.h"
#include "proto/group_user_list_request.h"
#include "proto/group_user_list_response.h"
#include "proto/history_msg_request.h"
#include "proto/msg_data.h"
#include "proto/msg_list_response.h"
#include "proto/msg_read_ack.h"
#include "proto/remove_session_request.h"
#include "proto/remove_session_response.h"
#include "proto/stop_receive_packet.h"
#include "proto/unread_msg_count_request.h"
#include "proto/unread_msg_count_response.h"
#include "proto/unread_msg_request.h"
#include "proto/user_action_log.h"
#include "proto/users_info_request.h"
#include "proto/users_info_response.h"
#include "proto/validate_request.h"
#include "proto/validate_response.h"

//可以定义一些宏
bool RegisterPDUMessageFactory(message::MessagePDUFactoryManager* factory_manager) {
  CHECK(factory_manager);

  ADD_MESSAGEPDU_FACTORY(ValidateRequest, MESSAGE_VALIDATE_REQUEST);
  ADD_MESSAGEPDU_FACTORY(FriendListRequest, MESSAGE_FRIEND_LIST_REQUEST);
  ADD_MESSAGEPDU_FACTORY(RemoveSessionRequest, MESSAGE_REMOVE_SESSION_REQUEST);
  ADD_MESSAGEPDU_FACTORY(DeparmentRequest, MESSAGE_DEPARTMENT_REQUEST);
  ADD_MESSAGEPDU_FACTORY(UsersInfoRequest, MESSAGE_USERS_INFO_REQUEST);
  ADD_MESSAGEPDU_FACTORY(AllUserRequest, MESSAGE_ALL_USER_REQUEST);
  ADD_MESSAGEPDU_FACTORY(MsgData, MESSAGE_MSG_DATA);
  ADD_MESSAGEPDU_FACTORY(UnreadMsgCountRequest, MESSAGE_UNREAD_MSG_COUNT_REQUEST);
  ADD_MESSAGEPDU_FACTORY(UnreadMsgRequest, MESSAGE_UNREAD_MSG_REQUEST);
  ADD_MESSAGEPDU_FACTORY(MsgReadAck, MESSAGE_MSG_READ_ACK);

  ADD_MESSAGEPDU_FACTORY(GroupListRequest, MESSAGE_GROUP_LIST_REQUEST);
  ADD_MESSAGEPDU_FACTORY(GroupUserListRequest, MESSAGE_GROUP_USER_LIST_REQUEST);
  ADD_MESSAGEPDU_FACTORY(GroupUnreadMsgCountRequest, MESSAGE_GROUP_UNREAD_MSG_COUNT_REQUEST);
  ADD_MESSAGEPDU_FACTORY(GroupUnreadMsgRequest, MESSAGE_GROUP_UNREAD_MSG_REQUEST);
  ADD_MESSAGEPDU_FACTORY(GroupHistoryMsgRequest, MESSAGE_GROUP_HISTORY_MSG_REQUEST);
  ADD_MESSAGEPDU_FACTORY(GroupMsgReadAck, MESSAGE_GROUP_MSG_READ_ACK);
  ADD_MESSAGEPDU_FACTORY(GroupCreateTmpGroupRequest, MESSAGE_GROUP_CREATE_TMP_GROUP_REQUEST);
  ADD_MESSAGEPDU_FACTORY(GroupChangeMemberRequest, MESSAGE_GROUP_CHANGE_MEMBER_REQUEST);
  ADD_MESSAGEPDU_FACTORY(GroupDialogListRequest, MESSAGE_GROUP_DIALOG_LIST_REQUEST);


  ADD_MESSAGEPDU_FACTORY(FileHasOfflineReq, MESSAGE_FILE_HAS_OFFLINE_REQ);
  ADD_MESSAGEPDU_FACTORY(FileAddOfflineReq, MESSAGE_FILE_ADD_OFFLINE_REQ);
  ADD_MESSAGEPDU_FACTORY(FileDelOfflineReq, MESSAGE_FILE_DEL_OFFLINE_REQ);

  return true;
}
