// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/file_has_offline_res.h"

namespace {

uint32 ByteSize(const OfflineFile& offline_file) {
  return sizeof(offline_file.from_id) +
    SIZEOF_STRING(offline_file.task_id) +
    SIZEOF_STRING(offline_file.file_name) +
    sizeof(offline_file.file_size);
}

bool ParseFromByteStream(OfflineFile* offline_file, const base::ByteStream& is) {
  is >> offline_file->from_id;
  is.ReadString(offline_file->task_id);
  is.ReadString(offline_file->file_name);
  is >> offline_file->file_size;

  return !is.Fail();
}

bool SerializeToByteStream(const OfflineFile& offline_file, base::ByteStream* os) {
  (*os) << offline_file.from_id;
  os->WriteString(offline_file.task_id);
  os->WriteString(offline_file.file_name);
  (*os) << offline_file.file_size;

  return !os->Fail();
}

}

uint32 FileHasOfflineRes::ByteSize() const {
  uint32 size = BaseTeamTalkPDU::ByteSize();
  size += sizeof(req_user_id_);
  CalculateContainerByteSize2(size, file_list_);
  return size;
}


bool FileHasOfflineRes::ParseFromByteStream(const base::ByteStream& is) {
  is >> req_user_id_;

  PARSE_OBJECTPTR_ARRAY_IMPLICIT(OfflineFile, file_list_);

  return !is.Fail();
}

bool FileHasOfflineRes::SerializeToByteStream(base::ByteStream* os) const {
  (*os) << req_user_id_;

  SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(file_list_);

  return !os->Fail();
}
