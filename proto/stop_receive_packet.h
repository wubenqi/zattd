// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_STOP_RECEIVE_PACKET_H_
#define PROTO_STOP_RECEIVE_PACKET_H_

#include "proto/base_teamtalk_pdu.h"

class StopReceivePacket : public BaseTeamTalkPDU {
public:
  StopReceivePacket() :
    BaseTeamTalkPDU(MESSAGE_STOP_RECEIVE_PACKET) {}

  virtual ~StopReceivePacket() {}

  PROPERTY_BASIC_TYPE_DECLARE(uint32, code);

  //////////////////////////////////////////////////////////////////////////
  virtual uint32 ByteSize() const {
    return BaseTeamTalkPDU::ByteSize() + sizeof(code_);
  }

protected:
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  uint32 code_;
};

#endif
