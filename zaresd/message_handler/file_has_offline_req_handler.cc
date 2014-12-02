// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/file_has_offline_req_handler.h"

#include "base/logging.h"

#include "proto/file_has_offline_req.h"
#include "proto/file_has_offline_res.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

int FileHasOfflineReqHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(FileHasOfflineReq, file_has_offline_req);

  FileManager* file_manager = ModelMainManager::GetInstance()->GetFileManager();

  FileHasOfflineRes file_has_offline_res;
  file_has_offline_res.SetReserved(file_has_offline_req->GetReserved());
  file_has_offline_res.set_req_user_id(file_has_offline_req->user_id());
  file_has_offline_res.SetAttachData(*file_has_offline_req->GetAttachData());
 
  file_manager->GetUserFiles(file_has_offline_req->user_id(), file_has_offline_res.mutable_file_list());

  context->SendSessionData(session_id, file_has_offline_res);

  return 0;
}

