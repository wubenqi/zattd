// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_USER_MANAGER_H_
#define ZARESD_MODEL_USER_MANAGER_H_

#include "proto/base_teamtalk_pdu.h"

class UserManager {
public:
  virtual ~UserManager() {}

  // 获取一个用户的信息
  // 输入：
  //  user_id: 用户ID
  //  user_info: 用户的具体信息，每个元素包括用户id，用户名，头像链接
  // 返回值：
  //  如果用户存在，返回设置user_info值，并返回user_info
  //  如果用户不存在或内部错误，返回NULL
  virtual const UserInfo* GetUserInfo(const uint32 user_id, UserInfo* user_info) = 0;

  // 获取一组用户的信息
  virtual bool GetUserInfo(const std::vector<uint32> user_ids, std::vector<UserInfo*>* user_infos) = 0;

  // 获取一个用户的信息
  // 输入：
  //  user_name: 用户名
  //  user_info: 用户的具体信息，每个元素包括用户id，用户名，头像链接
  // 返回值：
  //  如果用户存在，返回设置user_info值，并返回user_info
  //  如果用户不存在或内部错误，返回NULL
  virtual const UserInfo* GetUserInfo(const std::string& user_name, UserInfo* user_info) = 0;

  // 获取一组用户的信息
  virtual bool GetUserInfo(const std::vector<std::string>& user_names, std::vector<UserInfo*>* user_infos) = 0;

  // 获取所有用户的信息;默认聊天用户上限5000人
  virtual bool GetAllUserInfo(std::vector<UserInfo*>* user_infos) = 0;

};

#endif
