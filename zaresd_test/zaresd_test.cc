// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd_test/zaresd_test.h"

#include "base/at_exit.h"
#include "base2/time2.h"

#include "zaresd/config_info.h"
#include "zaresd/const_zaresd_defines.h"
#include "zaresd/model/model_main_manager.h"

#include "message_pdu/message_pdu_factory_manager.h"

#include "proto/validate_request.h"
#include "zaresd/message_handler/validate_request_handler.h"

#include "proto/department_request.h"
#include "zaresd/message_handler/department_request_handler.h"

#include "proto/all_user_request.h"
#include "zaresd/message_handler/all_user_request_handler.h"

#include "proto/friend_list_request.h"
#include "zaresd/message_handler/friend_list_request_handler.h"

#include "proto/remove_session_request.h"
#include "zaresd/message_handler/remove_session_request_handler.h"

#include "proto/msg_data.h"
#include "zaresd/message_handler/msg_data_handler.h"

#include "proto/users_info_request.h"
#include "zaresd/message_handler/users_info_request_handler.h"

#include "proto/group_list_request.h"
#include "zaresd/message_handler/group_list_request_handler.h"

#include "proto/group_dialog_list_request.h"
#include "zaresd/message_handler/group_dialog_list_request_handler.h"

#include "proto/group_user_list_request.h"
#include "zaresd/message_handler/group_user_list_request_handler.h"

#include "proto/group_create_tmp_group_request.h"
#include "zaresd/message_handler/group_create_tmp_group_request_handler.h"

#include "proto/group_change_member_request.h"
#include "zaresd/message_handler/group_change_member_request_handler.h"

void ValidateRequestHandler_Test() {
  ValidateRequest validate_request;
  validate_request.set_user_name("A");
  validate_request.set_password("");
  ValidateRequestHandler::Execute(NULL, 0, &validate_request);

  validate_request.set_user_name("B");
  validate_request.set_password("123456");
  ValidateRequestHandler::Execute(NULL, 0, &validate_request);
}

void DepartmentRequestHandler_Test() {
  DepartmentRequest department_request;
  department_request.set_req_user_id(1);
  DepartmentRequestHandler::Execute(NULL, 0, &department_request);
}

void AllUserRequestHandler_Test() {
  AllUserRequest all_user_request;
  all_user_request.set_req_user_id(1);
  AllUserRequestHandler::Execute(NULL, 0, &all_user_request);
}

void FriendListRequestHandler_Test() {
  FriendListRequest friend_list_request;
  friend_list_request.set_user_id(10035);
  FriendListRequestHandler::Execute(NULL, 0, &friend_list_request);
}

void RemoveSessionRequestHandler_Test() {
  RemoveSessionRequest remove_session_request;
  remove_session_request.set_req_user_id(10035);
  remove_session_request.set_session_id(10036);
  remove_session_request.set_session_type(1);
  RemoveSessionRequestHandler::Execute(NULL, 0, &remove_session_request);
}

void MsgDataHandler_Test() {
  MsgData msg_data;

  msg_data.set_from_user_id(10035);
  msg_data.set_to_user_id(10036);
  msg_data.set_msg_type(MESSAGE_TYPE_IM);
  msg_data.set_msg_data(std::string("Hello zaresd"));
  msg_data.set_create_time(base::NowMSTime()/1000);
  MsgDataHandler::Execute(NULL, 0, &msg_data);
}

void UsersInfoRequestHandler_Test() {
  UsersInfoRequest user_info_request;
  user_info_request.set_from_user_id(10035);
  user_info_request.add_user_id_list(10036);
  user_info_request.add_user_id_list(10037);
  UsersInfoRequestHandler::Execute(NULL, 0, &user_info_request);
}

void GroupListRequestHandler_Test() {
  GroupListRequest group_list_request;
  group_list_request.set_user_id(10035);
  GroupListRequestHandler::Execute(NULL, 0, &group_list_request);
}

void GroupDialogListRequestHandler_Test() {
  GroupDialogListRequest group_dialog_list_request;
  group_dialog_list_request.set_user_id(10035);
  GroupDialogListRequestHandler::Execute(NULL, 0, &group_dialog_list_request);
}

void GroupUserListRequestHandler_Test() {
  GroupUserListRequest group_user_list_request;
  group_user_list_request.set_group_id(104240);
  group_user_list_request.set_req_user_id(10035);
  GroupUserListRequestHandler::Execute(NULL, 0, &group_user_list_request);
}

void GroupCreateTmpGroupRequestHandler_Test() {
  GroupCreateTmpGroupRequest group_create_tmp_group_request;
  group_create_tmp_group_request.set_req_user_id(10035);
  group_create_tmp_group_request.set_group_name("ZAresd");
  group_create_tmp_group_request.set_group_avatar("g0/000/000/1409816408883559_140719535912.jpg");
  group_create_tmp_group_request.add_user_list(10035);
  group_create_tmp_group_request.add_user_list(10036);
  group_create_tmp_group_request.add_user_list(10037);
  GroupCreateTmpGroupRequestHandler::Execute(NULL, 0, &group_create_tmp_group_request);
}

void GroupChangeMemberRequestHandler_Test() {
  GroupChangeMemberRequest group_change_member_request;
  group_change_member_request.set_req_user_id(10035);
  group_change_member_request.set_group_id(104250);
  group_change_member_request.add_user_list(10036);

  // QuitGroup
  group_change_member_request.set_change_type(1);
  GroupChangeMemberRequestHandler::Execute(NULL, 0, &group_change_member_request);

  // JoinGroup
  group_change_member_request.set_change_type(0);
  GroupChangeMemberRequestHandler::Execute(NULL, 0, &group_change_member_request);
}

int main(int argc, char* argv[]) {
  base::AtExitManager at_exit;

  ConfigInfo::GetInstance()->Initialize("./zaresd.xml");
  ModelMainManager::GetInstance()->Initialize("zares");

#if 0
  ValidateRequestHandler_Test();
  DepartmentRequestHandler_Test();
  AllUserRequestHandler_Test();
  FriendListRequestHandler_Test();
  RemoveSessionRequestHandler_Test();
  MsgDataHandler_Test();
  UsersInfoRequestHandler_Test();
  GroupListRequestHandler_Test();
  GroupDialogListRequestHandler_Test();
  GroupUserListRequestHandler_Test();
  GroupCreateTmpGroupRequestHandler_Test();
#endif

  GroupChangeMemberRequestHandler_Test();
  return 0;
}