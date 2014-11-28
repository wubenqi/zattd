// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_MESSAGE_MANAGER_H_
#define ZARESD_MODEL_MESSAGE_MANAGER_H_

#include "proto/base_teamtalk_pdu.h"

class MessageManager {
public:
  virtual ~MessageManager() {}

  //////////////////////////////////////////////////////////////////////////
  // 获取单向数据，取未读消息用的,这里只取单向的，所以不用relateId
  virtual size_t GetMessages(uint32 from_user_id, uint32 to_user_id, uint32 offset, int count, std::vector<ServerMsg*>* messages) = 0;

  // 根据发送者和接收者的用户Id获取对话消息,双向数据
  virtual size_t GetDialogMessages(uint32 from_user_id, uint32 to_user_id, uint32 offset, int count, std::vector<ServerMsg*>* messages) = 0;

  //////////////////////////////////////////////////////////////////////////
  // 获取群消息
  virtual size_t GetGroupMessages(uint32 group_id, uint32 offset, int count, std::vector<GroupMsg*>* messages) = 0;

  // 获取群消息,离线消息用
  virtual size_t GetGroupMessagesFromId(uint32 user_id, uint32 last_msg_id, int count, std::vector<GroupMsg*>* group_msgs) = 0;

  //////////////////////////////////////////////////////////////////////////
  // 发送一段语音消息
  virtual bool SendAudioMessage(uint32 from_user_id, uint32 to_user_id, const std::string& content, uint32 time) = 0;

  // 发送一条IM消息,目前只有聊天记录，暂时不考虑原有业务中的私信，at消息等
  virtual bool SendIMGroupMessage(uint32 userId, uint32 to_group_id, const std::string& content, uint32 time) = 0;

  // 发送一条IM消息,目前只有聊天记录，暂时不考虑原有业务中的私信，at消息等
  virtual bool SendIMMessage(uint32 from_user_id, uint32 to_user_id, uint32 type, const std::string& content, uint32 time) = 0;

};

#endif
