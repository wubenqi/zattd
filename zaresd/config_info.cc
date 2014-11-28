// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "zaresd/config_info.h"

#include "base/logging.h"
#include "base2/config_file.h"

bool ConfigInfo::Initialize(const char* ini_file) {
  bool result = false;
  if (ini_file==NULL) {
    LOG(ERROR) << "ini_file is empty()";
    return result;
  }

  base::ConfigFile xml_ini;
  if (!xml_ini.Initialize(ini_file)) {
    LOG(ERROR) << "parser config_file " << ini_file << " error.";
    return result;
  }
  
  result = zaresd_addr_info_.ParseFromConfigFile(xml_ini, "ZAresdServer");
  if (!result) {
    return false;
  }

  result = db_addr_.ParseFromConfigFile(xml_ini, "DatabaseServer");
  return result;
}

void ConfigInfo::Destroy() {
  db_addr_.Destroy();
  zaresd_addr_info_.Destroy();
}
