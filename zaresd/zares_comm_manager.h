// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_ZARES_COMM_MANAGER_H_
#define ZARESD_ZARES_COMM_MANAGER_H_

#include "base/memory/singleton.h"
#include "base/memory/scoped_ptr.h"
#include "base/containers/hash_tables.h"

#include "net/codec/teamtalk/teamtalk_codec.h"
#include "net/engine/tcp_server.h"

class ZAresCommManager :
  public net::TeamTalkCodec::Delegate {
public:
  static ZAresCommManager* GetInstance() {
    return Singleton<ZAresCommManager>::get();
  }

  virtual ~ZAresCommManager() {}

  bool Start(const std::string& addr, const std::string& port);

  // unsafe
  void SendPacket(int io_handler_id, const TeamTalkPacketPtr packet);

protected:
  virtual int OnTTNewConnection(const net::IOHandlerPtr& ih);
  virtual int OnTTDataReceived(const net::IOHandlerPtr& ih, const TeamTalkPacketPtr& packet, base::Time receive_time);
  virtual int OnTTConnectionClosed(const net::IOHandlerPtr& ih);

private:
  void DoSendPacket(int io_handler_id, const TeamTalkPacketPtr packet);

  //////////////////////////////////////////////////////////////////////////
  friend class Singleton<ZAresCommManager>;
  friend struct DefaultSingletonTraits<ZAresCommManager>;

  ZAresCommManager() {}

  scoped_ptr<net::TeamTalkCodec> codec_;
  scoped_ptr<net::TCPServer> server_;

  typedef base::hash_map<int, net::IOHandlerPtr> IOHandlerMap;
  IOHandlerMap io_handlers_;

	DISALLOW_COPY_AND_ASSIGN(ZAresCommManager);
};

#endif

