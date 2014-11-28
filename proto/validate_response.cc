// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/validate_response.h"

#include "db/database_util.h"

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
  if (result_!=0) {
    user_->SerializeToByteStream(os);
  }
  return !os->Fail();
}
