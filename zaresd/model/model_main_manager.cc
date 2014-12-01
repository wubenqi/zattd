// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/model_main_manager.h"

#include "base/logging.h"

#include "zaresd/model/zares/zares_model_module.h"

bool ModelMainManager::Initialize(const std::string model_type) {
  if (model_type == "zares") {
    module_ = new ZAresModelModule();
    module_->Initialize(model_type);
  } else {
    NOTREACHED() << "Invalid model_type " << model_type;
  }
  return true;
}

void ModelMainManager::Destroy() {
  if (module_) {
    delete module_;
    module_ = NULL;
  }
}

LoginManager* ModelMainManager::GetLoginManager() {
  DCHECK(module_);
  return module_->GetLoginManager();
}
DepartmentManager* ModelMainManager::GetDepartmentManager() {
  DCHECK(module_);
  return module_->GetDepartmentManager();
}
UserManager* ModelMainManager::GetUserManager() {
  DCHECK(module_);
  return module_->GetUserManager();
}
GroupManager* ModelMainManager::GetGroupManager() {
  DCHECK(module_);
  return module_->GetGroupManager();
}
RelationshipManager* ModelMainManager::GetRelationshipManager() {
  DCHECK(module_);
  return module_->GetRelationshipManager();
}
MessageManager* ModelMainManager::GetMessageManager() {
  DCHECK(module_);
  return module_->GetMessageManager();
}
FileManager* ModelMainManager::GetFileManager() {
  DCHECK(module_);
  return module_->GetFileManager();
}
CounterManager* ModelMainManager::GetCounterManager() {
  DCHECK(module_);
  return module_->GetCounterManager();
}
AudioManager* ModelMainManager::GetAudioManager() {
  DCHECK(module_);
  return module_->GetAudioManager();
}

