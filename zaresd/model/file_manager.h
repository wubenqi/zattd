// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_MODEL_FILE_MANAGER_H_
#define ZARESD_MODEL_FILE_MANAGER_H_

#include "proto/base_teamtalk_pdu.h"

// #include <string>
// #include <vector>
// #include "base/basictypes.h"
// 
struct TransmitFile {
  uint32 id; 
  uint32 from_user_id; // 发送人
  uint32 to_user_id; // 接收人
  std::string task_id; //任务编号
  std::string file_path; // 文件路径
  uint32 file_size;		//文件大小.
  uint32 status; // 状态，是否已经被接收
  uint32 created; // 创建时间
  uint32 updated; // 更新时间
};

class FileManager {
public:
  virtual ~FileManager() {}

  // 获取一个用户未接收的所有文件列表
  virtual size_t GetUserFiles(uint32 to_user_id, std::vector<OfflineFile*>* files) = 0;

  // 保存一个未接收的离线文件
  virtual bool SaveFileRecord(uint32 user_id, uint32 to_user_id, const std::string& task_id, const std::string& file_path, uint32 fileSize) = 0;
 
  // 设置一个文件已经被对方接收
  virtual bool DeleteFileRecord(const std::string& task_id) = 0;
  
  // 获取一个发送的文件的记录
  virtual const TransmitFile* GetFileRecord(const std::string& task_id, TransmitFile* file) = 0;

};

#endif
