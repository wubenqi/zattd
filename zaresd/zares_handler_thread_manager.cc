// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/zares_handler_thread_manager.h"

#include "base/strings/stringprintf.h"
// #include "db/conn_pool_manager.h"

#include "zaresd/zares_handler_thread.h"

ZAresHandlerThreadManager::~ZAresHandlerThreadManager() {
  Shutdown();
}

void ZAresHandlerThreadManager::Initialize(const base::DBAddrInfo& db_adr) {
  thread_pool_size_ = db_adr.max_conn_count;
  // db_conn_pool_.Initialize(db_adr);

  std::string thread_name;
  for (size_t i=0; i<thread_pool_size_; ++i) {
    thread_name = base::StringPrintf("zares_handler_thread_%d", i);
    ZAresHandlerThread* thread = new ZAresHandlerThread(thread_name, i/*, db_conn_pool_.GetFreeConnection()*/);
    thread_pool_.push_back(thread);
  }
}

bool ZAresHandlerThreadManager::Run() {
  bool b_rt = true;
  size_t i = 0;
  for (i=0; i<thread_pool_size_; ++i) {
    if(!thread_pool_[i]->Run()) {
      b_rt = false;
      break;
    }
  }

  if (!b_rt) { // 启动Reactor出问题了
    Shutdown();
  }
  return b_rt;
}

void ZAresHandlerThreadManager::Shutdown() {
  if (thread_pool_size_>0) {
    for (size_t i=0; i<thread_pool_size_; ++i) {
      // db_conn_pool_.SetFreeConnection(thread_pool_[i]->GetDatabaseConncetion());
      thread_pool_[i]->Stop();
      delete thread_pool_[i];
    }
    thread_pool_.clear();
    thread_pool_size_ = 0;
  }
}

void ZAresHandlerThreadManager::PostDataToDbHandler(int io_handler_id, const TeamTalkPacketPtr& packet) {
  ZAresHandlerThread* thread = GetNextThread();
  thread->DoMessageDataHandler(io_handler_id, packet);
}
