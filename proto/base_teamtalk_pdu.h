// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// TeamTalkPDU���˼·��
//   TT��PDU��Ƽ򵥣�ռ���ڴ��٣�Ч�ʸߣ���ʹ��Ҳ����̫���㡣
//   ��������protobuf����ƣ�PDU����һ����ͨ�����Լ��������е����ݣ�����PDU�ĳ�Ա�����Լ������ڴ���ͷ��ڴ�
//   ��Ȼ���ռ��һЩ�ռ䣬��ʹ�ü�

#ifndef PROTO_BASE_TEAMTALK_PDU_H_
#define PROTO_BASE_TEAMTALK_PDU_H_

#include <vector>

#include "base/stl_util.h"
#include "message_pdu/message_pdu.h"

#include "net/base/byte_stream.h"

#include "proto/const_message_pdu_types.h"
#include "proto/attach_data.h"

#define ZARESD_SERVER_LIB

#ifdef ZARESD_SERVER_LIB
namespace db {
class QueryAnswer;
}
#endif

//////////////////////////////////////////////////////////////////////////
// string���л�ռ�ó���
#define SIZEOF_STRING(s) (sizeof(uint32)+s.length())

//////////////////////////////////////////////////////////////////////////
struct UserInfo {
  uint32 ByteSize() const;
  bool ParseFromByteStream(const net::ByteStream& is);
  bool SerializeToByteStream(net::ByteStream* os) const;

#ifdef ZARESD_SERVER_LIB
  bool ParseFromDatabase(const db::QueryAnswer& answ);
#endif

  uint32 	user_id;
  std::string name;
  std::string nick_name;
  std::string avatar_url;
  std::string title;          // ְ��
  std::string position;       // ��ַ
  uint32 role_status;    // �û���ְ״̬ 0:��ְ 1:��ְ
  uint32 sex;            // 0:Ů 1:��
  uint32 depart_id;      // ����id
  uint32 job_num;        // ����
  std::string telphone;       // �绰
  std::string email;          // ����
  uint32 user_updated;   // ����ʱ��
};

struct FriendInfo {
  uint32 ByteSize() const {
    return sizeof(friend_user_id) + sizeof(updated);
  }

  bool ParseFromByteStream(const net::ByteStream& is) {
    is >> friend_user_id
      >> updated;

    return !is.Fail();
  }

  bool SerializeToByteStream(net::ByteStream* os) const {
    (*os) << friend_user_id
      << updated;

    return !os->Fail();
  }

#ifdef ZARESD_SERVER_LIB
  bool ParseFromDatabase(const db::QueryAnswer& answ);
#endif

  uint32 friend_user_id;
  uint32 updated;   // ����ʱ��
};

struct DepartmentInfo {
  uint32 ByteSize() const;
  bool ParseFromByteStream(const net::ByteStream& is);
  bool SerializeToByteStream(net::ByteStream* os) const;

#ifdef ZARESD_SERVER_LIB
  bool ParseFromDatabase(const db::QueryAnswer& answ);
#endif

  uint32    depart_id;          //����id
  std::string title;          // ��������
  std::string description;          // ��������
  uint32    parent_depart_id;   //�ϼ�����id
  uint32    leader;             //����leader id
  uint32    status;         //����״̬  0:���� 1:ɾ��
};

struct UserUnreadMsgCount {
  uint32 ByteSize() const {
    return sizeof(from_user_id) + sizeof(unread_msg_count);
  }

  bool ParseFromByteStream(const net::ByteStream& is) {
    is >> from_user_id
      >> unread_msg_count;

    return !is.Fail();
  }
  bool SerializeToByteStream(net::ByteStream* os) const {
    (*os) << from_user_id
      << unread_msg_count;

    return !os->Fail();
  }

#ifdef ZARESD_SERVER_LIB
  bool ParseFromDatabase(const db::QueryAnswer& answ) { return true; }
#endif

  uint32 from_user_id;
  uint32 unread_msg_count;
} ;

struct ServerMsg {
  uint32 ByteSize() const;
  bool ParseFromByteStream(const net::ByteStream& is);
  bool SerializeToByteStream(net::ByteStream* os) const;

#ifdef ZARESD_SERVER_LIB
  bool ParseFromDatabase(const db::QueryAnswer& answ) { return true; }
#endif

  uint32 	from_user_id;
  std::string	 	from_name;
  std::string		from_nick_name;
  std::string		from_avatar_url;
  uint32 	create_time;
  uint8	 	msg_type;
  std::string 	msg_data;
};

//////////////////////////////////////////////////////////////////////////
struct GroupInfo {
  uint32 ByteSize() const { return 0; }
  bool ParseFromByteStream(const net::ByteStream& is) { return true; }
  bool SerializeToByteStream(net::ByteStream* os) const { return true; }

#ifdef ZARESD_SERVER_LIB
  bool ParseFromDatabase(const db::QueryAnswer& answ) { return true; }
#endif

  uint32 	group_id;
  std::string	group_name;
  std::string	group_avatar;
  uint32	group_creator_id;
  uint32	group_type;		// 1--normal group, 2--temporary group
  uint32	group_updated;
  std::vector<uint32> group_memeber_list;
};

struct GroupUnreadMsgCount {
  uint32 ByteSize() const {
    return sizeof(group_id) + sizeof(unread_msg_count);
  }

  bool ParseFromByteStream(const net::ByteStream& is) {
    is >> group_id
      >> unread_msg_count;

    return !is.Fail();
  }
  bool SerializeToByteStream(net::ByteStream* os) const {
    (*os) << group_id
      << unread_msg_count;

    return !os->Fail();
  }

#ifdef ZARESD_SERVER_LIB
  bool ParseFromDatabase(const db::QueryAnswer& answ) { return true; }
#endif

  uint32 group_id;
  uint32 unread_msg_count;
};

struct GroupMsg {
  uint32 ByteSize() const { return 0; }
  bool ParseFromByteStream(const net::ByteStream& is) { return true; }
  bool SerializeToByteStream(net::ByteStream* os) const { return true; }

#ifdef ZARESD_SERVER_LIB
  bool ParseFromDatabase(const db::QueryAnswer& answ) { return true; }
#endif

  uint32 from_user_id;
  uint32 create_time;
  std::string msg_content;
};

//////////////////////////////////////////////////////////////////////////
struct OfflineFile {
  uint32 ByteSize() const { return 0; }
  bool ParseFromByteStream(const net::ByteStream& is) { return true; }
  bool SerializeToByteStream(net::ByteStream* os) const { return true; }

#ifdef ZARESD_SERVER_LIB
  bool ParseFromDatabase(const db::QueryAnswer& answ) { return true; }
#endif

  uint32	from_id;
  std::string task_id;
  std::string file_name;
  uint32	file_size;
};


//////////////////////////////////////////////////////////////////////////
// BaseTeamTalkPDU
class BaseTeamTalkPDU : public message::MessagePDU {
public:
  virtual ~BaseTeamTalkPDU() {
    if (attach_data_) {
      delete attach_data_;
      attach_data_ = NULL;
    }
  }

  // ע�⣬���ؿ���ΪNULL,��������ҪС��
  const BaseAttachData* GetAttachData() const;
  BaseAttachData* MutableAttachData();

  // From message::MessagePDU
  virtual uint32 ByteSize() const {
    return attach_data_ ? attach_data_->ByteSize() : 0;
  }

  virtual bool ParseFromArray(const void* data, uint32 data_len) {
    net::ByteStream is(data, data_len);
    bool result = ParseFromByteStream(is);
    if (result && attach_data_) {
      result = attach_data_->ParseFromByteStream(is);
    }
    return result;
  }

  virtual bool SerializeToArray(void* data, uint32 data_len) const {
    net::ByteStream os(data, data_len);
    bool result = SerializeToByteStream(&os);
    if (result && attach_data_) {
      result = attach_data_->SerializeToByteStream(&os);
    }
    return result;
  }

protected:
  BaseTeamTalkPDU(MessagePDUType message_type, BaseAttachData::AttachDataType attach_data_type=BaseAttachData::kAttachDataTypeNull) :
    message::MessagePDU(message_type),
    attach_data_type_(attach_data_type),
    attach_data_(NULL) {}

//   BaseTeamTalkPDU(MessagePDUType message_type) :
//     message::MessagePDU(message_type),
//     attach_data_type_(BaseAttachData::kAttachDataTypeNull),
//     attach_data_(NULL) {}
//   }
// 
//   BaseTeamTalkPDU() :
//     attach_data_type_(BaseAttachData::kAttachDataTypeNull),
//     attach_data_(NULL) {}

  inline void set_attach_data_type(BaseAttachData::AttachDataType attach_data_type) { attach_data_type_ = attach_data_type; }

  virtual bool ParseFromByteStream(const net::ByteStream& is);
  virtual bool SerializeToByteStream(net::ByteStream* os) const;

  // ÿ��PDUֻʹ��һ��AttachData
  // �������ɵ�ʱ����趨�Ƿ�Ҫʹ��attach_data�Լ�ʹ���������͵�AttachData
  BaseAttachData::AttachDataType attach_data_type_;
  BaseAttachData* attach_data_;
};

// �����Ա��
// ��ͨ��������string�Ȳ���Ҫ�Լ������ڴ�Ķ���
#define PROPERTY_OBJECT_DECLARE(class_name, proterty) \
  inline const class_name##& proterty() const { return proterty##_; } \
  inline void set_##proterty(const class_name##& val) { proterty##_ = val; } \
  inline class_name##* mutable_##proterty() { return &proterty##_; }

// �Զ�����󣬴洢���Ƕ���ָ�룬������ͷ���Ҫ�Լ�����
#define PROPERTY_OBJECTPTR_DECLARE(class_name, proterty) \
  inline const class_name##& proterty() const { return *proterty##_; } \
  inline void set_##proterty(const class_name##& val) { *(mutable_##proterty()) = val; } \
  inline class_name##* mutable_##proterty() { if (proterty##_ == NULL) proterty##_ = new class_name(); return proterty##_; }

// �������ͣ���int
#define PROPERTY_BASIC_TYPE_DECLARE(class_type, proterty) \
  inline class_type proterty() const { return proterty##_; } \
  inline void set_##proterty( class_type val ) { proterty##_ = val; }

//////////////////////////////////////////////////////////////////////////
// ��ͨ��������string�Ȳ���Ҫ�Լ������ڴ�Ķ���
#define PROPERTY_OBJECT_ARRAY_DECLARE(class_name, proterty) \
  inline int proterty_##size() const { return proterty##_.size(); } \
  inline const class_name##& proterty(int index) const { return proterty##_[index]; } \
  inline void add_##proterty( const class_name& val ) { proterty##_.push_back(val); } \
  inline std::vector<class_name##*>* mutable_##proterty() { return &proterty##_; }

  // inline void set_##proterty( int intdex, class_type val ) { proterty##_[index] = val; } \
  // inline const class_name##& proterty() const { return proterty##_; } \
  // inline void set_##proterty(const class_name##& val) { proterty##_ = val; } \
  // inline class_name##* mutable_##proterty() { return &proterty##_; }

// �Զ�����󣬴洢���Ƕ���ָ�룬������ͷ���Ҫ�Լ�����
#define PROPERTY_OBJECTPTR_ARRAY_DECLARE(class_name, proterty) \
  inline int proterty_##size() const { return proterty##_.size(); } \
  inline const std::vector<class_name##*>& proterty() const { return proterty##_; } \
  inline const class_name##& proterty(int index) const { return *proterty##_[index]; } \
  inline class_name##* add_##proterty() { class_name* val = new class_name(); proterty##_.push_back(val); return val; } \
  inline std::vector<class_name##*>* mutable_##proterty() { return &proterty##_; }

  // inline void set_##proterty(const class_name##& val) { *(mutable_##proterty()) = val; }

// �������ͣ���int
#define PROPERTY_BASIC_TYPE_ARRAY_DECLARE(class_type, proterty) \
  inline int proterty_##size() const { return proterty##_.size(); } \
  inline const std::vector<class_type>& proterty() const { return proterty##_; } \
  inline class_type proterty(int index) const { return proterty##_[index]; } \
  inline void add_##proterty( class_type val ) { proterty##_.push_back(val); } \
  inline std::vector<class_type>* mutable_##proterty() { return &proterty##_; }

// inline void set_##proterty( int intdex, class_type val ) { proterty##_[index] = val; } \

// inline ::google::protobuf::uint32 i_all(int index) const;
// inline void set_i_all(int index, ::google::protobuf::uint32 value);
// inline void add_i_all(::google::protobuf::uint32 value);
// inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
// i_all() const;
// inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
// mutable_i_all();


template <class T>
uint32 CalculateContainerByteSize(const T& container) {
  uint32 size = container.empty() ? 0 : sizeof(uint32);
  for (typename T::const_iterator i(container.begin()); i != container.end(); ++i)
    size += (*i)->ByteSize();

  return size;
}

template <>
uint32 CalculateContainerByteSize(const std::vector<uint32>& container);

//////////////////////////////////////////////////////////////////////////
#define PARSE_OBJECTPTR_ARRAY_IMPLICIT(class_name, arr) \
  do { \
    uint32 array_size =0; \
    is >> array_size; \
    for (uint32 i=0; i<array_size; ++i) { \
      class_name* obj = new class_name(); \
      obj->ParseFromByteStream(is); \
      arr.push_back(obj); \
    } \
  } while (0);

#define SERIALIZE_OBJECTPTR_ARRAY_IMPLICIT(arr) \
  do { \
    (*os) << static_cast<uint32>(arr.size()); \
    for (size_t i=0; i<arr.size(); ++i) { \
      arr[i]->SerializeToByteStream(os); \
    } \
  } while (0);


#define PARSE_BASICTYPE_ARRAY_IMPLICIT(class_type, arr) \
  do { \
    uint32 array_size =0; \
    is >> array_size; \
    for (uint32 i=0; i<array_size; ++i) { \
      class_type v; \
      is >> v; \
      arr.push_back(v); \
    } \
  } while (0);

#define SERIALIZE_BASICTYPE_ARRAY_IMPLICIT(arr) \
  do { \
    (*os) << static_cast<uint32>(arr.size()); \
    for (size_t i=0; i<arr.size(); ++i) { \
      (*os) << arr[i]; \
    } \
  } while (0);

#endif