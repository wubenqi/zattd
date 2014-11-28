// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/user_action_log.h"

bool UserActionLog::ParseFromByteStream(const net::ByteStream& is) {
  is >> source_
    >> protocol_;
  is.ReadString(ip_);
  is >> user_id_
    >> action_type_;
  is.ReadString(os_type_);
  is.ReadString(user_agent_);
  is.ReadString(flash_ver_);
  is.ReadString(client_ver_);

  return !is.Fail();
}

bool UserActionLog::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << source_
    << protocol_;
  os->WriteString(ip_);
  (*os) << user_id_
    << action_type_;

  os->WriteString(os_type_);
  os->WriteString(user_agent_);
  os->WriteString(flash_ver_);
  os->WriteString(client_ver_);

  return !os->Fail();
}
