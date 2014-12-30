// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请不要随意改动
//

#ifndef ZARESD_MESSAGE_HANDLER_FILE_HAS_OFFLINE_ERQ_HANDLER_H_
#define ZARESD_MESSAGE_HANDLER_FILE_HAS_OFFLINE_ERQ_HANDLER_H_

#include "message_pdu/message_pdu.h"
#include "db/base_database.h"

class ZAresHandlerThread;
class FileHasOfflineReqHandler {
public:
  static int Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message);

private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(FileHasOfflineReqHandler);
};

#endif
