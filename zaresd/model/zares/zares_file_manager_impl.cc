// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//


#include "zaresd/model/zares/zares_file_manager_impl.h"

size_t ZAresFileManagerImpl::GetUserFiles(uint32 to_user_id, std::vector<OfflineFile*>* files) {
  return 0;
}

bool ZAresFileManagerImpl::SaveFileRecord(uint32 user_id, uint32 to_user_id, const std::string& task_id, const std::string& file_path, uint32 fileSize) {
  return true;
}

bool ZAresFileManagerImpl::DeleteFileRecord(const std::string& task_id) {
  return true;
}

const TransmitFile* ZAresFileManagerImpl::GetFileRecord(const std::string& task_id, TransmitFile* file) {
  return NULL;
}
