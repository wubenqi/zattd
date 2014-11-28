// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_CONFIG_INFO_H_
#define ZARESD_CONFIG_INFO_H_

#include <vector>
#include <string>

#include "base/basictypes.h"
#include "base/memory/singleton.h"

#include "base2/config_file_util.h"

class ConfigInfo {
public:
  ~ConfigInfo() {
  }

  static ConfigInfo* GetInstance() {
    return Singleton<ConfigInfo>::get();
  }

  bool Initialize(const char* ini_file);
  void Destroy();

  inline const base::IpAddrInfo2& zaresd_addr_info() const {
    return zaresd_addr_info_;
  }
  
  inline const base::DBAddrInfo& db_addr() const {
    return db_addr_;
  }
  
protected:
  friend class Singleton<ConfigInfo>;
  friend struct DefaultSingletonTraits<ConfigInfo>;

  // void GetDBAddrInfo(const base::ConfigFile& xml_ini, const char* section_name, base::DBAddrInfo* db_addr);
  ConfigInfo() {
  }

  DISALLOW_COPY_AND_ASSIGN(ConfigInfo);

  base::DBAddrInfo db_addr_;
  base::IpAddrInfo2 zaresd_addr_info_;
};

#endif

