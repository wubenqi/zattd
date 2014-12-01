// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/model/zares/zares_department_manager_impl.h"

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "db/conn_pool_manager.h"

#include "proto/base_teamtalk_pdu.h"

// 获取所有部门信息
bool ZAresDepartmentManagerImpl::GetDepartmentInfos(std::vector<DepartmentInfo*>* department_infos) {
 
  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  scoped_ptr<db::QueryAnswer> answ(db_conn->Query("SELECT `id`,`title`,`leader`,`pid`,`status`,`desc` FROM IMDepartment WHERE status = 0"));

  if (answ.get() != NULL) {
   while (answ->FetchRow()) {
      DepartmentInfo* department = new DepartmentInfo();
      department->ParseFromDatabase(*answ);
      department_infos->push_back(department);
    }
  } else {
    return false;
  }
  return true;
}
