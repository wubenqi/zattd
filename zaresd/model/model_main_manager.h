// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_MODEL_MAIN_MANAGER_H_
#define ZARESD_MODEL_MODEL_MAIN_MANAGER_H_

#include "base/memory/singleton.h"

#include "zaresd/model/model_module.h"

// 数据存储有可能不仅仅直接访问mysql，比如有人提出来使用Atlas(360)，甚至可以采用其它的数据库(MogoDB等)，
// 故model提供一些接口，
// 可以以插件方式实现不同的数据访问
class ModelMainManager {
public:
  ~ModelMainManager() {
    Destroy();
  }

  static ModelMainManager* GetInstance() {
    return Singleton<ModelMainManager>::get();
  }

  bool Initialize(const std::string model_type);
  void Destroy();

  LoginManager* GetLoginManager();
  DepartmentManager* GetDepartmentManager();
  UserManager* GetUserManager();
  GroupManager* GetGroupManager();
  RelationshipManager* GetRelationshipManager();
  MessageManager* GetMessageManager();
  FileManager* GetFileManager();
  CounterManager* GetCounterManager();
  AudioManager* GetAudioManager();

private:
  friend struct DefaultSingletonTraits<ModelMainManager>;

  ModelMainManager() {
    module_ = NULL;
  }

protected:
  ModelModule* module_;
};

#endif

