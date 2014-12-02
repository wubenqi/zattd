// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/group_create_tmp_group_request_handler.h"

#include "base/logging.h"

#include "proto/group_create_tmp_group_request.h"
#include "proto/group_create_tmp_group_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// 创建群
int GroupCreateTmpGroupRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(GroupCreateTmpGroupRequest, group_create_tmp_group_request);

  GroupManager* group_manager = ModelMainManager::GetInstance()->GetGroupManager();

  GroupCreateTmpGroupResponse group_create_tmp_group_response;
  group_create_tmp_group_response.SetReserved(group_create_tmp_group_request->GetReserved());
  group_create_tmp_group_response.set_req_user_id(group_create_tmp_group_request->req_user_id());
  group_create_tmp_group_response.SetAttachData(*group_create_tmp_group_request->GetAttachData());

  uint32 result = 1;
  uint32 group_id = 0;
  GroupInfo group;

  // Todo:
  //  Check 
  if (group_manager->CreateGroup(
      group_create_tmp_group_request->req_user_id(),
      group_create_tmp_group_request->group_name(),
      2,
      group_create_tmp_group_request->group_avatar(),
      "",
      group_create_tmp_group_request->user_list(),
      &group)) {
    result = 0;
    group_id = group.group_id;
  } else {
    LOG(ERROR) << "";
  }

  group_create_tmp_group_response.set_result(result);
  group_create_tmp_group_response.set_group_id(group_id);

  if (context) {
    context->SendSessionData(session_id, group_create_tmp_group_response);
  }

  return 0;
}
