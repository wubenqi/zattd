// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/department_request_handler.h"

#include "base/logging.h"
#include "base/stringprintf.h"
#include "base/memory/scoped_ptr.h"

#include "proto/department_request.h"
#include "proto/department_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

int DepartmentRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(DeparmentRequest, department_request);

  LOG(INFO) << "DepartmentRequestHandler::Execute(): req_user_id = " << department_request->req_user_id();
  DepartmentResponse department_response;
  department_response.set_req_user_id(department_request->req_user_id());
  department_response.MutableAttachData()->CopyFrom(department_request->GetAttachData());

  DepartmentManager* depart_manager = ModelMainManager::GetInstance()->GetDepartmentManager();
  if(!depart_manager->GetDepartmentInfos(department_response.mutable_depart_list())) {
    LOG(ERROR) << "depart_list is empty!!!!";
  }

  context->SendSessionData(session_id, department_response);

  return 0;
}

