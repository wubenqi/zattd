// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#include "proto/attach_data.h"

#include "base/logging.h"

//////////////////////////////////////////////////////////////////////////
// Ìí¼ÓNullAttachData
class NullAttachData : public BaseAttachData {
public:
  NullAttachData() :
    BaseAttachData(kAttachDataTypeNull) {}

  virtual uint32 ByteSize() const {
    return 0;
  }
  virtual bool ParseFromByteStream(const base::ByteStream& is) {
    return true;
  }
  virtual bool SerializeToByteStream(base::ByteStream* os) const {
    return true;
  }
};

class DbAttachData : public BaseAttachData {
public:
  DbAttachData() :
    BaseAttachData(kAttachDataTypeDB) {}

  // implict BaseAttachData
  virtual const std::string& GetPduData() const;
  virtual std::string* MutablePduData();
  virtual void SetPduData(const std::string& val);
};

//////////////////////////////////////////////////////////////////////////
class PduAttachData : public BaseAttachData {
public:
  PduAttachData() :
    BaseAttachData(kAttachDataTypePDU) {}

  virtual uint32 ByteSize() const;
  virtual bool ParseFromByteStream(const base::ByteStream& is);
  virtual bool SerializeToByteStream(base::ByteStream* os) const;
};

//////////////////////////////////////////////////////////////////////////
BaseAttachData::~BaseAttachData() {
}

BaseAttachData* BaseAttachData::CreateAttachData(AttachDataType attach_data_type) {
  BaseAttachData* attach_data = NULL;
  if (attach_data_type == kAttachDataTypeDB) {
    attach_data = new DbAttachData();
  } else if (attach_data_type == kAttachDataTypePDU) {
    attach_data = new PduAttachData();
  } else if (attach_data_type == kAttachDataTypeNull) {
    attach_data = new NullAttachData();
  }
  return attach_data;
}

bool BaseAttachData::CopyFrom(const BaseAttachData& other) {
  // 1. CHECK
  if (attach_data_type_ != other.attach_data_type_) {
    LOG(ERROR) << "this->attach_data_type = " << attach_data_type_ << ", other.attach_data_type = " << other.attach_data_type_;
    return false;
  }
  type_ = other.type_;
  handle_ = other.handle_;
  service_type_ = other.service_type_;
  pdu_data_ = other.pdu_data_;
  
  return true;
}

bool BaseAttachData::CopyFrom(const BaseAttachData* other) {
  if (other == NULL) {
    return false;
  }

  return CopyFrom(*other);
}

uint32 BaseAttachData::ByteSize() const {
  return sizeof(attach_data_len_) + sizeof(type_) + sizeof(handle_) + sizeof(service_type_);
}

bool BaseAttachData::ParseFromByteStream(const base::ByteStream& is) {
  is >> attach_data_len_
     >> type_
     >> handle_
     >> service_type_;

  return !is.Fail();
}

bool BaseAttachData::SerializeToByteStream(base::ByteStream* os) const {
  //attach_data_len_ = ByteSize()-sizeof(attach_data_len_);
  (*os) << (static_cast<uint32>(ByteSize()-sizeof(attach_data_len_)))
        << type_
        << handle_
        << service_type_;
  return !os->Fail();
}

//////////////////////////////////////////////////////////////////////////
const std::string& DbAttachData::GetPduData() const {
  NOTREACHED() << "DbAttachData not use pdu_data!!!!";
  return pdu_data_;
}

std::string* DbAttachData::MutablePduData() {
  NOTREACHED() << "DbAttachData not use pdu_data!!!!";
  return &pdu_data_;
}

void DbAttachData::SetPduData(const std::string& val) {
  NOTREACHED() << "DbAttachData not use pdu_data!!!!";
  pdu_data_ = val;
}

//////////////////////////////////////////////////////////////////////////
uint32 PduAttachData::ByteSize() const {
#ifndef SIZEOF_STRING
#define SIZEOF_STRING(s) (sizeof(uint32)+s.length())
#endif
  return BaseAttachData::ByteSize() + SIZEOF_STRING(pdu_data_);
}

bool PduAttachData::ParseFromByteStream(const base::ByteStream& is) {
  bool result = BaseAttachData::ParseFromByteStream(is);
  if (result) {
    result = (0 == is.ReadString(pdu_data_));
  }
  return result;
}

bool PduAttachData::SerializeToByteStream(base::ByteStream* os) const {
  bool result = BaseAttachData::SerializeToByteStream(os);
  if (result) {
    result = (0 == os->WriteString(pdu_data_));
  }
  return result;
}
