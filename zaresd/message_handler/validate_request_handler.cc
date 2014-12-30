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
#include "base/strings/stringprintf.h"
#include "base/memory/scoped_ptr.h"

#include "proto/validate_request.h"
#include "proto/validate_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

int ValidateRequestHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(ValidateRequest, validate_request);

  // 2. 取出用户信息，返回给请求客户端
  ValidateResponse validate_response;
  validate_response.SetReserved(validate_request->GetReserved());
  validate_response.SetReserved(validate_request->GetReserved());
  validate_response.set_user_name(validate_request->user_name());
  validate_response.SetAttachData(*validate_request->GetAttachData());
  validate_response.set_result(1);

  if (validate_request->user_name().empty() 
    || validate_request->password().empty()) {
      LOG(ERROR) << "Check ValidateRequest: user_name or passwd is empty!!! user_name = " << validate_request->user_name();
  } else {
    // 1. Check validate_request invalid!!!!
    LoginManager* login_manager = ModelMainManager::GetInstance()->GetLoginManager();
    UserManager* user_manager = ModelMainManager::GetInstance()->GetUserManager();

    bool is_authed = login_manager->Auth(validate_request->user_name(), validate_request->password());

    if (is_authed) {
      validate_response.set_result(0);
      if (user_manager->GetUserInfo(validate_request->user_name(), validate_response.mutable_user())) {
        // 
      } else {
        LOG(ERROR) << "user_manager->GetUserInfo(" << validate_request->user_name() << ") error!!!!";
      }
    } else {
      LOG(ERROR) << "login_manager->Auth(" << validate_request->user_name() << ") error!!!!";
    }
  }

  if (context) context->SendSessionData(io_handler_id, validate_response);

  return 0;
}

