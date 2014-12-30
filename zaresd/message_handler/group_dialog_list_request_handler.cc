// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/group_dialog_list_request_handler.h"

#include "base/logging.h"

#include "proto/group_dialog_list_request.h"
#include "proto/group_dialog_list_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// 返回用户加入的群信息
int GroupDialogListRequestHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(GroupDialogListRequest, group_dialog_list_request);

  GroupManager* group_manager = ModelMainManager::GetInstance()->GetGroupManager();

  GroupDialogListResponse group_dialog_list_response;
  group_dialog_list_response.SetReserved(group_dialog_list_request->GetReserved());
  group_dialog_list_response.set_req_user_id(group_dialog_list_request->user_id());
  group_dialog_list_response.SetAttachData(*group_dialog_list_request->GetAttachData());
  
  if (group_dialog_list_request->user_id() > 0) {

    std::vector<GroupInfo*>* groups = group_dialog_list_response.mutable_group_list();
    if (group_manager->GetRecentGroupsByUserId(group_dialog_list_request->user_id(), groups) > 0) {
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
  } else {
    LOG(ERROR) << "group_dialog_list_request->user_id() = 0 is valid!!!!";
  }

  if (context) {
    context->SendSessionData(io_handler_id, group_dialog_list_response);
  }

  return 0;
}

