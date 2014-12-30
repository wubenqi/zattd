// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
//

#include "zaresd/message_handler/file_add_offline_req_handler.h"

#include "base/logging.h"
#include "base2/base_types.h"

#include "proto/file_add_offline_req.h"
#include "proto/db_write_response.h"

#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

int FileAddOfflineReqHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(FileAddOfflineReq, file_add_offline_req);

  FileManager* file_manager = ModelMainManager::GetInstance()->GetFileManager();

  // TODO
  /// check data
  // result 0,1,2

  DBWriteResponse db_write_response;
  db_write_response.SetReserved(file_add_offline_req->GetReserved());
  db_write_response.set_request_id(file_add_offline_req->req_user_id());
  db_write_response.set_result(0);
  db_write_response.set_request_pdu_type(GetHighInt16ByInt32(message->message_type()));
  db_write_response.set_from_id(file_add_offline_req->from_id());
  db_write_response.set_to_id(file_add_offline_req->to_id());

  bool is_sucess = file_manager->SaveFileRecord(
      file_add_offline_req->from_id(),
      file_add_offline_req->to_id(),
      file_add_offline_req->task_id(),
      file_add_offline_req->file_name(),
      file_add_offline_req->file_size()
    );

  db_write_response.set_result(is_sucess ? 0 : 2);

  context->SendSessionData(io_handler_id, db_write_response);

  return 0;
}
