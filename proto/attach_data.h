// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef PROTO_ATACH_DATA_H_
#define PROTO_ATACH_DATA_H_

#include "base/basictypes.h"

#include "net/base/byte_stream.h"
// #include "message_pdu/message_pdu.h"

enum {
  ATTACH_TYPE_HANDLE	= 1,
  ATTACH_TYPE_SHOP_ID	= 2,
  ATTACH_TYPE_HANDLE_AND_PDU = 3,
};

class BaseAttachData {
public:
  enum AttachDataType {
    kAttachDataTypeNull = 0,
    kAttachDataTypeDB = 1,
    kAttachDataTypePDU = 2,
  };

  virtual ~BaseAttachData();

  //////////////////////////////////////////////////////////////////////////
  static BaseAttachData* CreateAttachData(AttachDataType attach_data_type);

  static inline void AttachDataInitialize(BaseAttachData* attach_data, uint32 type, uint32 handle, uint32 service_type) {
    attach_data->set_type(type);
    attach_data->set_handle(handle);
    attach_data->set_service_type(service_type);
  }

  //////////////////////////////////////////////////////////////////////////
  inline AttachDataType GetAttachDataType() const { return attach_data_type_; }

  //////////////////////////////////////////////////////////////////////////
  bool CopyFrom(const BaseAttachData& other);
  bool CopyFrom(const BaseAttachData* other);

  //////////////////////////////////////////////////////////////////////////
  inline uint32 type() const { return type_; }
  inline void set_type(uint32 val) { type_ = val; }

  inline uint32 handle() const { return handle_; }
  inline void set_handle(uint32 val) { handle_ = val; }

  inline uint32 service_type() const { return service_type_; }
  inline void set_service_type(uint32 val) { service_type_ = val; }

  //////////////////////////////////////////////////////////////////////////
  virtual const std::string& GetPduData() const { return pdu_data_; } 
  virtual std::string* MutablePduData() { return &pdu_data_; }
  virtual void SetPduData(const std::string& val) { pdu_data_ = val; }

  virtual uint32 ByteSize() const;
  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

protected:
  explicit BaseAttachData(AttachDataType attach_data_type) :
    attach_data_type_(attach_data_type) {}

  AttachDataType attach_data_type_;
  uint32 		type_;
  uint32		handle_;
  uint32    service_type_;

  std::string pdu_data_;
  // message::MessagePDU* message_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(BaseAttachData);
};

#endif // PROTO_ATACH_DATA_H_
