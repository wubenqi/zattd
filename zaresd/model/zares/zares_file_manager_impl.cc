// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//


#include "zaresd/model/zares/zares_file_manager_impl.h"

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/stringprintf.h"
#include "base2/time2.h"
#include "base/string_number_conversions.h"

#include "db/database_util.h"
#include "db/conn_pool_manager.h"

#include "zaresd/const_zaresd_defines.h"

size_t ZAresFileManagerImpl::GetUserFiles(uint32 to_user_id, std::vector<OfflineFile*>* files) {
  if (to_user_id == 0) {
    return 0;
  }

  uint32 t = base::NowMSTime()-7*24*3600;
  std::string sql = StringPrintf("SELECT id,userId,toUserId,taskId,filePath,status,created,updated,fsize FROM IMTransmitFile WHERE toUserId = %d AND created > %d AND status = 1 ORDER BY created DESC LIMIT 50",
        to_user_id,
        t);

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));
  if (answ.get() != NULL) {
    while (answ->FetchRow()) {
      OfflineFile* offline_file = new OfflineFile();
  
      CHECK(offline_file);
      answ->GetColumn(1, &offline_file->from_id);
      answ->GetColumn(3, &offline_file->task_id);
      answ->GetColumn(4, &offline_file->file_name);
      answ->GetColumn(8, &offline_file->file_size);

      files->push_back(offline_file);
    }
  } else {
    return 0;
  }
  return files->size();
}

uint32	from_id;
std::string task_id;
std::string file_name;
uint32	file_size;


bool ZAresFileManagerImpl::SaveFileRecord(uint32 user_id, uint32 to_user_id, const std::string& task_id, const std::string& file_path, uint32 file_size) {
  if (user_id == 0 || to_user_id == 0 || file_path.empty()) {
      return false;
  }

  uint32 now = base::NowMSTime();

  std::string sql;
  db::QueryParam p;
  p.AddParam(&user_id);
  p.AddParam(&to_user_id);
  p.AddParam(task_id.c_str());
  p.AddParam(file_path.c_str());
  p.AddParam(&now);
  p.AddParam(&now);
  p.AddParam(&file_size);
  db::MakeQueryString("INSERT INTO IMTransmitFile (userId, toUserId, taskId, filePath, created, updated,fsize) VALUES (:1,:2,:3,:4:5,:6,:7,:8)", &p, &sql);
  
  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  if (db_conn->Execute(sql) <=0 ) {
    LOG(ERROR) << "Error execute sql: " << sql;
  }

  return true;
}

bool ZAresFileManagerImpl::DeleteFileRecord(const std::string& task_id) {
  if (task_id.empty()) {
    return false;
  }

  std::string sql = StringPrintf("UPDATE IMTransmitFile SET status = 0, updated = %d WHERE taskId = '%s' LIMIT 1", base::NowMSTime(), task_id.c_str());
  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);
  if (db_conn->Execute(sql) <=0 ) {
    LOG(ERROR) << "Error execute sql: " << sql;
  }

  return true;
}

const TransmitFile* ZAresFileManagerImpl::GetFileRecord(const std::string& task_id, TransmitFile* file) {
  if (task_id.empty()) {
    return NULL;
  }

  std::string sql = StringPrintf("SELECT id,userId,toUserId,taskId,filePath,status,created,updated,fsize FROM IMTransmitFile WHERE taskId = '%s'", task_id.c_str());

  db::ScopedPtr_DatabaseConnection db_conn(db_conn_pool_);

  scoped_ptr<db::QueryAnswer> answ(db_conn->Query(sql));
  if (answ.get() != NULL) {
    if (answ->FetchRow()) {
      answ->GetColumn(0, &file->id);
      answ->GetColumn(1, &file->from_user_id);
      answ->GetColumn(2, &file->to_user_id);
      answ->GetColumn(3, &file->task_id);
      answ->GetColumn(4, &file->file_path);
      answ->GetColumn(5, &file->status);
      answ->GetColumn(6, &file->created);
      answ->GetColumn(7, &file->updated);
      answ->GetColumn(8, &file->file_size);
     return file;
    }
  }
 
  return NULL;
}
