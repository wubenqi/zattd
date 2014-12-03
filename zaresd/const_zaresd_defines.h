// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_CONST_ZARESD_DEFINES_H_
#define ZARESD_CONST_ZARESD_DEFINES_H_

#include "base/basictypes.h"

// ------------ IM消息的type ------------
const int MESSAGE_TYPE_IM = 1; // 普通用户+系统消息
const int MESSAGE_TYPE_IM_AUDIO = 2;
const int MESSAGE_TYPE_IM_GROUP = 17;
const int MESSAGE_TYPE_IM_GROUP_AUDIO = 18;

const uint32 UNREAD_MAX_COUNTER = 100; // 用户一次读取未读消息不能超过100
const uint32 GROUP_UNREAD_MAX_COUNTER = 150; // 用户一次读取未读群消息不能超过200

// ------------- 服务号小T ---------------
// public static final int SYS_SERVER_USER_ID = 10000;
// public static final String SYS_SERVER_USER_NAME = "小T";

const uint32 SYS_SERVER_USER_ID = 10000;

const uint32 kInvalidID = 0xFFFFFFFF;

#endif
