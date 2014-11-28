// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_CLIENT_COMM_HANDLER_H_
#define ZARESD_CLIENT_COMM_HANDLER_H_
#pragma once

#include "base/memory/singleton.h"
#include "base/timer.h"
#include "net/engine/tcp_acceptor.h"
#include "net/teamtalk/teamtalk_io_handler.h"

// class ServerCommHandler;
class ClientCommHandler :
  public net::TeamTalkIOHandler {
public:
  ClientCommHandler(SOCKET socket, net::Reactor* reactor);
  virtual ~ClientCommHandler();
  void Destroy();

  //////////////////////////////////////////////////////////////////////////
  virtual int OnNewConnection();
  virtual int OnDataReceived(const TeamTalkPacketPtr& packet);
  virtual int OnConnectionClosed();

  //////////////////////////////////////////////////////////////////////////
private:
  std::string log_prefix_;
};

const scoped_refptr<ClientCommHandler>& GetEmptyClientCommHandler();

class ClientCommHandlerFactory :
  public net::IOHandlerFactory {
public:
  static ClientCommHandlerFactory* GetInstance() {
    return Singleton<ClientCommHandlerFactory>::get();
  }

  virtual net::IOHandler* CreateIOHandler(SOCKET socket, net::Reactor* reactor) {
    return new ClientCommHandler(socket, reactor);
  }

private:
  friend class Singleton<ClientCommHandlerFactory>;
  friend struct DefaultSingletonTraits<ClientCommHandlerFactory>;

  ClientCommHandlerFactory() {}
  virtual ~ClientCommHandlerFactory() {}

  DISALLOW_COPY_AND_ASSIGN(ClientCommHandlerFactory);
};

#endif

