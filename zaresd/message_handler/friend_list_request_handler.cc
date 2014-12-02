// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/friend_list_request_handler.h"

#include "base/logging.h"
#include "base/stringprintf.h"
#include "base/memory/scoped_ptr.h"

#include "proto/friend_list_request.h"
#include "proto/friend_list_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

int FriendListRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(FriendListRequest, friend_list_request);

  FriendListResponse friend_list_response;
  friend_list_response.SetReserved(friend_list_request->GetReserved());
  friend_list_response.set_from_user_id(friend_list_request->user_id());
  friend_list_response.SetAttachData(*friend_list_request->GetAttachData());

  if (friend_list_request->user_id() > 0) {
    RelationshipManager* relationship_manager = ModelMainManager::GetInstance()->GetRelationshipManager();
    relationship_manager->GetRecentContactByUserId(friend_list_request->user_id(), 100, friend_list_response.mutable_friend_lists());
  } else {
    LOG(ERROR) << "FriendListRequest: user_id is 0!!!!!!!!!!";
  }

  if (context) {
    context->SendSessionData(session_id, friend_list_response);
  }

  return 0;
}

