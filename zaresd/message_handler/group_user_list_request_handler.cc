// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/group_user_list_request_handler.h"

#include "base/logging.h"

#include "proto/group_user_list_request.h"
#include "proto/group_user_list_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// 获取群详细信息
int GroupUserListRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(GroupUserListRequest, group_user_list_request);

  GroupManager* group_manager = ModelMainManager::GetInstance()->GetGroupManager();

  GroupUserListResponse group_user_list_response;
  group_user_list_response.SetReserved(group_user_list_request->GetReserved());
  group_user_list_response.set_req_user_id(group_user_list_request->req_user_id());
  group_user_list_response.set_group_id(group_user_list_request->group_id());
  group_user_list_response.SetAttachData(*group_user_list_request->GetAttachData());

  GroupInfo group;
  if (group_manager->GetGroupInfo(group_user_list_request->group_id(), &group)) {
    group_user_list_response.set_result(0);

    group_user_list_response.set_group_name(group.group_name);
    group_user_list_response.set_group_avatar(group.group_avatar);
    group_user_list_response.set_group_type(group.group_type);
    group_user_list_response.set_group_creator_id(group.group_creator_id);

    GroupRelationInfoList group_relations;
    group_manager->GetGroupMembers(group_user_list_request->group_id(), &group_relations);
    for (size_t i=0; i<group_relations.size(); ++i) {
      group_user_list_response.add_user_list(group_relations[i].user_id);
    }
  } else {
    group_user_list_response.set_result(1);
  }

  if (context) {
    context->SendSessionData(session_id, group_user_list_response);
  }

  return 0;
}
