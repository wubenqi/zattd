// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_MODEL_MODULE_H_
#define ZARESD_MODEL_MODEL_MODULE_H_

#include "zaresd/model/login_manager.h"
#include "zaresd/model/department_manager.h"
#include "zaresd/model/user_manager.h"
#include "zaresd/model/group_manager.h"
#include "zaresd/model/relationship_manager.h"
#include "zaresd/model/message_manager.h"
#include "zaresd/model/file_manager.h"
#include "zaresd/model/counter_manager.h"
#include "zaresd/model/audio_manager.h"

class ModelModule {
public:
  virtual ~ModelModule() {}

  virtual bool Initialize(const std::string model_type) { return true; } 
  virtual void Destroy() {}

  //////////////////////////////////////////////////////////////////////////
  LoginManager* GetLoginManager() {
    return login_manager_;
  }
  DepartmentManager* GetDepartmentManager() {
    return department_manager_;
  }
  UserManager* GetUserManager() {
    return user_manager_;
  }
  GroupManager* GetGroupManager() {
    return group_manager_;
  }
  RelationshipManager* GetRelationshipManager() {
    return relationship_manager_;
  }
  MessageManager* GetMessageManager() {
    return message_manager_;
  }
  FileManager* GetFileManager() {
    return file_manager_;
  }
  CounterManager* GetCounterManager() {
    return counter_manager_;
  }
  AudioManager* GetAudioManager() {
    return audio_manager_;
  }

protected:
  ModelModule() {
    login_manager_ = NULL;
    department_manager_ = NULL;
    user_manager_ = NULL;
    group_manager_ = NULL;
    relationship_manager_ = NULL;
    message_manager_ = NULL;
    file_manager_ = NULL;
    counter_manager_ = NULL;
    audio_manager_ = NULL;
  }

  LoginManager* login_manager_;
  DepartmentManager* department_manager_;
  UserManager* user_manager_;
  GroupManager* group_manager_;
  RelationshipManager* relationship_manager_;
  MessageManager* message_manager_;
  FileManager* file_manager_;
  CounterManager* counter_manager_;
  AudioManager* audio_manager_;
};

#endif
