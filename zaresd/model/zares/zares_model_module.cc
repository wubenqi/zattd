// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/zares/zares_model_module.h"

#include "base/logging.h"

#include "zaresd/config_info.h"

#include "zaresd/model/zares/zares_login_manager_impl.h"
#include "zaresd/model/zares/zares_department_manager_impl.h"
#include "zaresd/model/zares/zares_user_manager_impl.h"
#include "zaresd/model/zares/zares_group_manager_impl.h"
#include "zaresd/model/zares/zares_relationship_manager_impl.h"
#include "zaresd/model/zares/zares_message_manager_impl.h"
#include "zaresd/model/zares/zares_file_manager_impl.h"
#include "zaresd/model/zares/zares_counter_manager_impl.h"
#include "zaresd/model/zares/zares_audio_manager_impl.h"

bool ZAresModelModule::Initialize(const std::string model_type) {
  ConfigInfo* config = ConfigInfo::GetInstance();

  // TODO
  //  Check max_count;

  ZAresRelationshipManagerImpl* relationship_manager = NULL;
  ZAresMessageManagerImpl* message_manager = NULL;

  base::DBAddrInfo db_addr = config->db_addr();
  db_conn_pool_.Initialize(db_addr);

  if (NULL == audio_manager_) {
    audio_manager_ = new ZAresAudioManagerImpl();
  }

  if (NULL == counter_manager_) {
    counter_manager_ = new ZAresCounterManagerImpl();
  }

  if (NULL == department_manager_) {
    department_manager_ = new ZAresDepartmentManagerImpl(&db_conn_pool_);
  }

  if (NULL == file_manager_) {
    file_manager_ = new ZAresFileManagerImpl(&db_conn_pool_);
  }

  if (NULL == group_manager_) {
    group_manager_ = new ZAresGroupManagerImpl(&db_conn_pool_);
  }

  if (NULL == login_manager_) {
    login_manager_ = new ZAresLoginManagerImpl(&db_conn_pool_);
  }

  if (NULL == message_manager_) {
    message_manager_ = message_manager = new ZAresMessageManagerImpl(&db_conn_pool_);
  }

  if (NULL == relationship_manager_) {
    relationship_manager = new ZAresRelationshipManagerImpl(&db_conn_pool_);
    relationship_manager_ = relationship_manager;
  }

  if (NULL == user_manager_) {
    user_manager_ = new ZAresUserManagerImpl(&db_conn_pool_);
  }

  // Setup manager's relation
  message_manager->SetRelationshipManager(relationship_manager);
  return true;
}

void ZAresModelModule::Destroy() {
  if (audio_manager_) {
    delete audio_manager_;
    audio_manager_ = NULL;
  }
  if (counter_manager_) {
    delete counter_manager_;
    counter_manager_ = NULL;
  }
  if (department_manager_) {
    delete department_manager_;
    department_manager_ = NULL;
  }
  if (file_manager_) {
    delete file_manager_;
    file_manager_ = NULL;
  }
  if (group_manager_) {
    delete group_manager_;
    group_manager_ = NULL;
  }
  if (login_manager_) {
    delete login_manager_;
    login_manager_ = NULL;
  }
  if (message_manager_) {
    delete message_manager_;
    message_manager_ = NULL;
  }
  if (relationship_manager_) {
    delete relationship_manager_;
    relationship_manager_ = NULL;
  }
  if (user_manager_) {
    delete user_manager_;
    user_manager_ = NULL;
  }
}
