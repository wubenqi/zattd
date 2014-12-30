// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/zares_handler_thread.h"

#include "base/memory/scoped_ptr.h"
// #include "base/lazy_instance.h"
// #include "base/threading/thread_local.h"

#include "message_pdu/message_pdu_util.h"

#include "zaresd/message_handler/message_handler.h"
#include "zaresd/zares_comm_manager.h"

// A lazily created thread local storage for quick access to a thread's message
// loop, if one exists.  This should be safe and free of static constructors.
// base::LazyInstance<base::ThreadLocalPointer<db::BaseDatabase> > lazy_tls_dbconn_ptr = LAZY_INSTANCE_INITIALIZER;

ZAresHandlerThread::ZAresHandlerThread(const std::string& name, int thread_index/*, db::BaseDatabase* dbconn*/) :
  base::Thread(name.c_str()),
    thread_index_(thread_index),
    timer_(NULL) {
//    dbconn_(dbconn) {

}

ZAresHandlerThread::~ZAresHandlerThread() {

}

// db::BaseDatabase* ZAresHandlerThread::current_dbconn() {
//   // TODO(darin): sadly, we cannot enable this yet since people call us even
//   // when they have no intention of using us.
//   return lazy_tls_dbconn_ptr.Pointer()->Get();
// }

bool ZAresHandlerThread::Run() {
  base::Thread::Options options(base::MessageLoop::TYPE_DEFAULT, 0);
  return StartWithOptions(options);
}

void ZAresHandlerThread::Shutdown() {
  Stop();
}

void ZAresHandlerThread::Init() {
  timer_ = new base::Timer(false, false);
//  lazy_tls_dbconn_ptr.Pointer()->Set(dbconn_);
}

void ZAresHandlerThread::CleanUp() {
  // lazy_tls_dbconn_ptr.Pointer()->Set(NULL);

  if (timer_) {
    delete timer_;
    timer_ = NULL;
  }
}

void ZAresHandlerThread::DoMessageDataHandler(int io_handler_id, const TeamTalkPacketPtr& packet) {
  message_loop()->PostTask(FROM_HERE, base::Bind(&ZAresHandlerThread::OnMessageDataHandler, base::Unretained(this), io_handler_id, packet));
}

void ZAresHandlerThread::OnMessageDataHandler(int io_handler_id, const TeamTalkPacketPtr& packet) {
  scoped_ptr<message::MessagePDU> message(message::ParseMessagePDUFromNetPacker(packet));
  if (message.get() != NULL) {
    DispatchMessageHandler(this, io_handler_id, message.get());
  } else {
    // LOG(ERROR) << "";
  }
}

void ZAresHandlerThread::SendSessionData(int io_handler_id, const message::MessagePDU& message) {
  TeamTalkPacketPtr packet = message::MessageToPacket(message);
  // net::IOBufferPtr io_buffer = message::MessageToIOBuffer(message);
  ZAresCommManager::GetInstance()->SendPacket(io_handler_id, packet);
}
