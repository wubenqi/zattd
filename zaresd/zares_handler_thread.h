// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_ZARES_HANDLER_THREAD_H_
#define ZARESD_ZARES_HANDLER_THREAD_H_

#include "base/threading/thread.h"
#include "base/timer/timer.h"

#include "net/codec/teamtalk/teamtalk_packet.h"
#include "message_pdu/message_pdu.h"
// #include "db/base_database.h"

class ZAresHandlerThread : public base::Thread {
public:
  ZAresHandlerThread(const std::string& name, int thread_index);
  virtual ~ZAresHandlerThread();

  bool Run();
  void Shutdown();

  // static db::BaseDatabase* current_dbconn();

  inline int thread_index() const {
    return thread_index_;
  }

  inline base::Timer* GetTimer() {
    return timer_;
  }

  // db::BaseDatabase* GetDatabaseConncetion() {
  //   return dbconn_;
  // }

  void DoMessageDataHandler(int io_handler_id, const TeamTalkPacketPtr& packet);
  void SendSessionData(int io_handler_id, const message::MessagePDU& message);

protected:
  // Process packet from client_comm_handler 
  void OnMessageDataHandler(int io_handler_id, const TeamTalkPacketPtr& packet);

  // Called just prior to starting the message loop
  virtual void Init();
  // Called just after the message loop ends
  virtual void CleanUp();

private:
  int thread_index_;
  base::Timer* timer_;
  // db::BaseDatabase* dbconn_;
};


#endif
