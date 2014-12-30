// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/zaresd_server.h"

#include "base/at_exit.h"
#include "base/sys_info.h"
#include "base2/file_path_util.h"

#if defined(OS_WIN)
#include "net/base/winsock_init.h"
#endif

#include "net/message_loop/message_pump_libevent2.h"
#include "message_pdu/message_pdu_factory_manager.h"

#include "zaresd/config_info.h"

#include "zaresd/zares_comm_manager.h"
#include "zaresd/message_handler/message_handler.h"
#include "zaresd/zares_handler_thread_manager.h"
#include "zaresd/model/model_main_manager.h"

ZAresdServer::ZAresdServer() 
  : BaseDaemon() {
  message_loop_ = new base::MessageLoop(make_scoped_ptr(new base::MessagePumpLibevent2()));
}

ZAresdServer::~ZAresdServer() {
}

int ZAresdServer::LoadConfig( const base::FilePath& xml_ini_file ) {
  std::string config_file_path = file_path_util::ToStringHack(xml_ini_file);
  return ConfigInfo::GetInstance()->Initialize(config_file_path.c_str()) ? 0 : -1;
}

int	ZAresdServer::Initialize( int argc, char** argv ) {
  //uint64 t = MAKEINT64(1,1);
  //LOG(INFO) << t;

  // 客户端连接处理
  if (message_loop_ == NULL) {
  }
  
  ConfigInfo* config = ConfigInfo::GetInstance();

  ModelMainManager::GetInstance()->Initialize("zares");

  ZAresHandlerThreadManager* zares_handler_thread_manager = ZAresHandlerThreadManager::GetInstance();

  zares_handler_thread_manager->Initialize(config->db_addr());
  zares_handler_thread_manager->Run();

  // 网络消息初始化
  message::MessagePDUFactoryManager* factoty_manager = message::MessagePDUFactoryManager::GetInstance();
  RegisterPDUMessageFactory(factoty_manager);
  InitMessageHandlerTable();

  ZAresCommManager* zares_comm_manager = ZAresCommManager::GetInstance();
  if(!zares_comm_manager->Start(config->zaresd_addr_info().addr, config->zaresd_addr_info().port)) {

    LOG(ERROR) << "Start ZAresd server in port[" << config->zaresd_addr_info().port << "] error.";
    return -1;
  }
  LOG(INFO) << "ZAresd server in port["<< config->zaresd_addr_info().port << "]";

  return 0;
}

int ZAresdServer::Destroy() {
  ZAresHandlerThreadManager* zares_handler_thread_manager = ZAresHandlerThreadManager::GetInstance();
  zares_handler_thread_manager->Shutdown();
  return 0;
}

int main(int argc, char* argv[]) {


  base::AtExitManager at_exit_manager;

#if defined(OS_WIN)
  net::EnsureWinsockInit();
#endif

  ZAresdServer daemon;
  return daemon.DoMain(argc, argv);
}

