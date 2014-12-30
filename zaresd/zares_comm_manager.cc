// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/zares_comm_manager.h"

#include "base2/base_types.h"
#include "base/message_loop/message_loop.h"
#include "base/bind.h"

#include "proto/const_message_pdu_types.h"
#include "zaresd/message_handler/message_handler.h"
#include "zaresd/zares_handler_thread_manager.h"

bool ZAresCommManager::Start(const std::string& addr, const std::string& port) {
  codec_.reset(new net::TeamTalkCodec(this));
  server_.reset(new net::TCPServer(base::MessageLoop::current(), codec_.get()));
  return server_->Create(addr, port, true);
}

int ZAresCommManager::OnTTNewConnection(const net::IOHandlerPtr& ih) {
  LOG(INFO) << "OnTTNewConnection: id=" << ih->io_handler_id() << " from " << ih->GetAddressString() << "connected";
  io_handlers_.insert(std::make_pair(ih->io_handler_id(), ih));
  return 0;
}

int ZAresCommManager::OnTTDataReceived(const net::IOHandlerPtr& ih, const TeamTalkPacketPtr& packet, base::Time receive_time) {
  LOG(INFO) << "OnTTDataReceived: id=" << ih->io_handler_id() << ", data_len=" << packet->GetBodyLength() << " from " << ih->GetAddressString();

  uint16 module_id = GetLowInt16ByInt32(packet->GetMessageType());
  uint16 command_id = GetHighInt16ByInt32(packet->GetMessageType());

  LOG(INFO) << "OnTTDataReceived: recv a packet, module_id = " << module_id
    << ", command_id = " << command_id
    << ", data_len = " << packet->GetBodyLength()
    << ", from " << ih->GetAddressString();
  int result = 0;

  if (packet->GetMessageType() == MESSAGE_HEARTBEAT) {
    codec_->SendPacket(ih, packet);
  } else {
    if(CheckMessageHandler(packet->GetMessageType())) {
      ZAresHandlerThreadManager::GetInstance()->PostDataToDbHandler(ih->io_handler_id(), packet);
    } else {
      LOG(ERROR) << "Not impl message_handler in message_type = " << packet->GetMessageType();
    }
  }
  return result;
}

int ZAresCommManager::OnTTConnectionClosed(const net::IOHandlerPtr& ih) {
  IOHandlerMap::iterator it = io_handlers_.find(ih->io_handler_id());
  if (it!=io_handlers_.end()) {
    io_handlers_.erase(it);
  }
  LOG(INFO) << "OnTTConnectionClosed: id=" << ih->io_handler_id() << ", from " << ih->GetAddressString() << " closed";
  return 0;
}

void ZAresCommManager::SendPacket(int io_handler_id, const TeamTalkPacketPtr packet) {
  server_->message_loop()->PostTask(FROM_HERE, base::Bind(&ZAresCommManager::DoSendPacket, base::Unretained(this), io_handler_id, packet));
  // 
}

void ZAresCommManager::DoSendPacket(int io_handler_id, const TeamTalkPacketPtr packet) {
  IOHandlerMap::iterator it = io_handlers_.find(io_handler_id);
  if (it!=io_handlers_.end()) {
    codec_->SendPacket(it->second, packet);
  }
}
