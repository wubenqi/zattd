// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/client_comm_handler.h"

#include "base/file_util.h"
#include "base/bind.h"
#include "base/md5.h"
#include "base/stringprintf.h"
#include "base2/scoped_lock.h"
#include "base2/base_types.h"

#include "net/engine/reactor.h"

#include "proto/const_message_pdu_types.h"
#include "zaresd/message_handler/message_handler.h"
#include "zaresd/zares_handler_thread_manager.h"

const scoped_refptr<ClientCommHandler>& GetEmptyClientCommHandler() {
  static scoped_refptr<ClientCommHandler> kEmptyClientHandler;
  return kEmptyClientHandler;
}

ClientCommHandler::ClientCommHandler(SOCKET socket, net::Reactor* reactor) 
  : net::TeamTalkIOHandler(socket, reactor) {

}
ClientCommHandler::~ClientCommHandler() {
}

void ClientCommHandler::Destroy() {
}

int ClientCommHandler::OnNewConnection() {
  log_prefix_ = base::StringPrintf("[%u@%u]>> ", GetLowInt32ByInt64(GetSessionID()), GetReactorID());

  LOG(INFO) << log_prefix_ << "client_comm_handler from " << GetAddressString() << " connected";
  return 0;
}

int ClientCommHandler::OnDataReceived(const TeamTalkPacketPtr& packet) {
  uint16 module_id = GetLowInt16ByInt32(packet->GetMessageType());
  uint16 command_id = GetHighInt16ByInt32(packet->GetMessageType());

  LOG(INFO) << log_prefix_ << "recv a packet, module_id = " << module_id
          << ", command_id = " << command_id
          << ", data_len = " << packet->GetBodyLength()
          << ", from " << GetAddressString();
  int result = 0;

  if (packet->GetMessageType() == MESSAGE_HEARTBEAT) {
    SendSyncData(packet);
  } else {
    if(CheckMessageHandler(packet->GetMessageType())) {
      ZAresHandlerThreadManager::GetInstance()->PostDataToDbHandler(GetSessionID(), packet);
    } else {
      LOG(ERROR) << "Not impl message_handler in message_type = " << packet->GetMessageType();
    }
  }
  return result;
}

int ClientCommHandler::OnConnectionClosed() {
  LOG(INFO) << log_prefix_ << "client_comm_handler from " << GetAddressString() << " closed";
  return 0;
}
