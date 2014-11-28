// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_ALL_USER_RESPONSE_H_
#define PROTO_ALL_USER_RESPONSE_H_

#include "proto/users_info_response.h"

class AllUserResponse : public UsersInfoResponse {
public:
  AllUserResponse() :
    UsersInfoResponse(MESSAGE_ALL_USER_RESPONSE) {}

  virtual ~AllUserResponse() {}
};

#endif // PROTO_ALL_USER_REQUEST_H_
