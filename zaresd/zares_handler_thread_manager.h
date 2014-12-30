// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//


#ifndef ZARESD_ZARES_HANDLER_THREAD_MANAGER_H_
#define ZARESD_ZARES_HANDLER_THREAD_MANAGER_H_
#pragma once

#include <vector>

#include "base/memory/singleton.h"
#include "base/atomic_sequence_num.h"
#include "base2/config_file_util.h"

#include "net/codec/teamtalk/teamtalk_packet.h"

#include "db/conn_pool_manager.h"

class ZAresHandlerThread;
class ZAresHandlerThreadManager {
public:
  static ZAresHandlerThreadManager* GetInstance() {
    return Singleton<ZAresHandlerThreadManager>::get();
  }

  void Initialize(const base::DBAddrInfo& db_adr);

  bool Run();
  void Shutdown();

  ZAresHandlerThread* GetNextThread() {
    if (thread_pool_size_ == 1) {
      return thread_pool_[0];
    } else {
      uint32 next_thread = static_cast<uint32>(next_thread_.GetNext());
      return thread_pool_[next_thread%thread_pool_size_];
    }
  }
  
  void PostDataToDbHandler(int io_handler_id, const TeamTalkPacketPtr& packet);

private:
  friend struct DefaultSingletonTraits<ZAresHandlerThreadManager>;

  ZAresHandlerThreadManager() {
    thread_pool_size_ = 0;
  }

  ~ZAresHandlerThreadManager();

  std::vector<ZAresHandlerThread*> thread_pool_;
  size_t thread_pool_size_;
  base::AtomicSequenceNumber next_thread_;

  DISALLOW_COPY_AND_ASSIGN(ZAresHandlerThreadManager);
};


#endif
