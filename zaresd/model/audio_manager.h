// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_AUDIO_MANAGER_H_
#define ZARESD_MODEL_AUDIO_MANAGER_H_

#include "base/basictypes.h"

class AudioManager {
public:
  virtual ~AudioManager() {}

  // 登陆的验证接口
  // uname:
  // passwd已加密密码
  // virtual bool Auth(const std::string& uname, const std::string& passwd) = 0;
};

#endif
