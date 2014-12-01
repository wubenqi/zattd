// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/group_change_member_request_handler.h"

#include "base/logging.h"

#include "proto/group_change_member_request.h"
#include "proto/group_change_member_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// 加入或退出群
int GroupChangeMemberRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(GroupChangeMemberRequest, group_change_member_request);

  GroupManager* group_manager = ModelMainManager::GetInstance()->GetGroupManager();

  GroupChangeMemberResponse group_change_member_response;
  group_change_member_response.set_req_user_id(group_change_member_request->req_user_id());
  *(group_change_member_response.mutable_user_list()) = group_change_member_request->user_list();
  group_change_member_response.MutableAttachData()->CopyFrom(group_change_member_request->GetAttachData());

  uint32 result = 0;
  uint32 change_type = 0;
  GroupInfo group;

  if (group_change_member_request->change_type() == 0) {
    if (group_manager->GetGroupInfo(group_change_member_request->group_id(), &group)) {
      group_manager->JoinGroup(
          group_change_member_request->user_list(),
          group_change_member_request->group_id(),
          group);
    }
    change_type = 0;
  } else {
    if (group_manager->GetGroupInfo(group_change_member_request->group_id(), &group)) {
      group_manager->QuitGroup(
          group_change_member_request->req_user_id(),
          group_change_member_request->user_list(),
          group_change_member_request->group_id(),
          group);
      *(group_change_member_response.mutable_user_list()) = group_change_member_request->user_list();
    }
    change_type = 1;
  }

  group_change_member_response.set_result(result);
  //change_type);
  group_change_member_response.set_group_id(group_change_member_request->group_id());
  group_change_member_response.set_change_type(change_type);

  if (context) {
    context->SendSessionData(session_id, group_change_member_response);
  }
 
  return 0;
}

