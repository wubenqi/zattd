// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/validate_request_handler.h"

#include "base/logging.h"
#include "base/stringprintf.h"
#include "base/memory/scoped_ptr.h"

#include "proto/validate_request.h"
#include "proto/validate_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

int ValidateRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(ValidateRequest, validate_request);

  // 1. Check validate_request invalid!!!!
  LoginManager* login_manager = ModelMainManager::GetInstance()->GetLoginManager();
  UserManager* user_manager = ModelMainManager::GetInstance()->GetUserManager();

  // 2. 取出用户信息，返回给请求客户端
  ValidateResponse validate_response;
  validate_response.set_user_name(validate_request->user_name());
  validate_response.MutableAttachData()->CopyFrom(validate_request->GetAttachData());
  validate_response.set_result(1);

  bool is_authed = login_manager->Auth(validate_request->user_name(), validate_request->password());

  if (is_authed) {
    UserInfo user_info;
    if (user_manager->GetUserInfo(validate_request->user_name(), &user_info)) {
      validate_response.set_result(0);
      *(validate_response.mutable_user()) = user_info;
    } else {
      // 
    }
  }

  context->SendSessionData(session_id, validate_response);

  return 0;
}

