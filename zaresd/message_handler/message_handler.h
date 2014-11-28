// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请不要随意改动
//

#ifndef ZARESD_MESSAGE_HANDLER_MESSAGE_HANDLER_H_
#define ZARESD_MESSAGE_HANDLER_MESSAGE_HANDLER_H_

#include "message_pdu/message_pdu.h"

class ZAresHandlerThread;

void InitMessageHandlerTable();
int DispatchMessageHandler(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message);
bool CheckMessageHandler(uint32 message_type);

#endif

