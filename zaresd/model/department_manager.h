// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_DEPARTMENT_MANAGER_H_
#define ZARESD_MODEL_DEPARTMENT_MANAGER_H_

#include <vector>
#include "proto/base_teamtalk_pdu.h"

class DepartmentManager {
public:
  virtual ~DepartmentManager() {}

  // 获取所有部门信息
  virtual bool GetDepartmentInfos(std::vector<DepartmentInfo*>* department_infos) = 0;
};

#endif
