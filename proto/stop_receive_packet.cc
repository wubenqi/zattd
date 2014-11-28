// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/stop_receive_packet.h"

bool StopReceivePacket::ParseFromByteStream(const net::ByteStream& is) {
  is >> code_;

  return !is.Fail();
}

bool StopReceivePacket::SerializeToByteStream(net::ByteStream* os) const {
  (*os) << code_;

  return !os->Fail();
}
