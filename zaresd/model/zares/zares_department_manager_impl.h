// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_ZARES_DEPARTMENT_MANAGER_IMPL_H_
#define ZARESD_MODEL_ZARES_DEPARTMENT_MANAGER_IMPL_H_

#include "zaresd/model/department_manager.h"

namespace db {
class CdbConnPoolManager;
}

class ZAresDepartmentManagerImpl : public DepartmentManager {
public:
  ZAresDepartmentManagerImpl(db::CdbConnPoolManager* db_conn_pool) :
    db_conn_pool_(db_conn_pool) {}
  virtual ~ZAresDepartmentManagerImpl() {}

  // 获取所有部门信息
  virtual bool GetDepartmentInfos(std::vector<DepartmentInfo*>* department_infos);

private:
  db::CdbConnPoolManager* db_conn_pool_;
};

#endif
