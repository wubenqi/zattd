// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/validate_request.h"

bool ValidateRequest::ParseFromByteStream(const base::ByteStream& is) {
  is.ReadString(user_name_);
  is.ReadString(password_);

  return !is.Fail();
}

bool ValidateRequest::SerializeToByteStream(base::ByteStream* os) const {
  os->WriteString(user_name_);
  os->WriteString(password_);

  return !os->Fail();
}
