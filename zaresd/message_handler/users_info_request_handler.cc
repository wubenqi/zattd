// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/users_info_request_handler.h"

#include "base/logging.h"

#include "proto/users_info_request.h"
#include "proto/users_info_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

// 获取用户信息
int UsersInfoRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(UsersInfoRequest, users_info_request);

  UserManager* user_manager = ModelMainManager::GetInstance()->GetUserManager();

  UsersInfoResponse users_info_response;
  users_info_response.set_from_user_id(users_info_request->from_user_id());
  if (!user_manager->GetUserInfo(users_info_request->user_id_list(), users_info_response.mutable_user_info_list())) {
    // TODO: 
    //  LOG(ERROR) << "";
  }

  context->SendSessionData(session_id, users_info_response);

  return 0;
}
