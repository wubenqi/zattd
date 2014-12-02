// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/validate_response.h"

#include "db/database_util.h"

uint32 ValidateResponse::ByteSize() const {
  uint32 s1 = BaseTeamTalkPDU::ByteSize();
  uint32 s2 = SIZEOF_STRING(user_name_) + sizeof(result_);
  uint32 s3 = user_ ? user_->ByteSize() : 0;

  return s1+s2+s3;

  //return BaseTeamTalkPDU::ByteSize() + 
  //  SIZEOF_STRING(user_name_) +
  //  sizeof(result_) + 
  //  user_ ? user_->ByteSize() : 0;
}

bool ValidateResponse::ParseFromByteStream(const net::ByteStream& is) {
  is.ReadString(user_name_);
  is >> result_;
  if (result_) {
    mutable_user()->ParseFromByteStream(is);
  }

  return !is.Fail();
}

bool ValidateResponse::SerializeToByteStream(net::ByteStream* os) const {
  os->WriteString(user_name_);
  (*os) << result_;
  if (result_==0) {
    user_->SerializeToByteStream(os);
  }
  return !os->Fail();
}
