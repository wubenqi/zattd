// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/group_list_request_handler.h"

#include "base/logging.h"

#include "proto/group_list_request.h"
#include "proto/group_list_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"


// 返回用户加入的群信息
int GroupListRequestHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(GroupListRequest, group_list_request);

  GroupManager* group_manager = ModelMainManager::GetInstance()->GetGroupManager();

  GroupListResponse group_list_response;
  group_list_response.SetReserved(group_list_request->GetReserved());
  group_list_response.set_req_user_id(group_list_request->user_id());
  group_list_response.SetAttachData(*group_list_request->GetAttachData());

  std::vector<GroupInfo*>* groups = group_list_response.mutable_group_list();
  if (group_manager->GetGroupsByUserId(group_list_request->user_id(), true, groups) > 0) {
    std::vector<uint32> group_ids;
    for (size_t i=0; i<groups->size(); ++i) {
      group_ids.push_back((*groups)[i]->group_id);
    }

    GroupRelationInfoListMap group_relations_map;
    group_manager->GetGroupMembers(group_ids, &group_relations_map);

    for (size_t i=0; i<groups->size(); ++i) {
      GroupRelationInfoListMap::iterator it = group_relations_map.find((*groups)[i]->group_id);
      if (it != group_relations_map.end()) {
        for (size_t j=0; j<it->second.size(); ++j) {
          (*groups)[i]->group_memeber_list.push_back((it->second)[j].user_id);
        }
      }
    }
  }

  if (context) {
    context->SendSessionData(io_handler_id, group_list_response);
  }

  return 0;
}
