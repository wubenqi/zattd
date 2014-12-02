// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/all_user_request_handler.h"

#include "base/logging.h"

#include "proto/all_user_request.h"
#include "proto/all_user_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

int AllUserRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(AllUserRequest, all_user_request);

  AllUserResponse all_user_response;
  all_user_response.SetReserved(all_user_request->GetReserved());
  all_user_response.set_from_user_id(all_user_request->req_user_id());
  all_user_response.SetAttachData(*all_user_request->GetAttachData());

  if (all_user_request->req_user_id()>0) {
    UserManager* user_manager = ModelMainManager::GetInstance()->GetUserManager();
    user_manager->GetAllUserInfo(all_user_response.mutable_user_info_list());
  } else {
    LOG(ERROR) << "all_user_request.req_user_id ivalid, val=0!!!!";
  }

  if (context) {
    context->SendSessionData(session_id, all_user_response);
  }

  return 0;
}

