// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_ZARES_MODEL_MODULE_H_
#define ZARESD_MODEL_ZARES_MODEL_MODULE_H_

#include "zaresd/model/model_module.h"

#include "db/conn_pool_manager.h"

// TT的数据库实现
class ZAresModelModule : public ModelModule {
public:
  ZAresModelModule() {}
  virtual ~ZAresModelModule() {}

  //////////////////////////////////////////////////////////////////////////
  virtual bool Initialize(const std::string model_type);
  virtual void Destroy();

private:
  db::CdbConnPoolManager db_conn_pool_;
};

#endif
