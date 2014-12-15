CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT (zaresd)

IF(CMAKE_SYSTEM MATCHES Linux)
  ADD_DEFINITIONS(-D__LINUX__)
  ADD_DEFINITIONS(-D__linux)
  ADD_DEFINITIONS(-D_REENTRANT)
ELSE(CMAKE_SYSTEM MATCHES Linux)
  ADD_DEFINITIONS(-D__WINDOWS__)
ENDIF(CMAKE_SYSTEM MATCHES Linux)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${TF_CURRENT_BINARY_PATH_BIN})

#INCLUDE_DIRECTORIES(..)
#INCLUDE_DIRECTORIES(../proto/cc/common ../proto/cc/editor ../proto/cc/server)
LINK_DIRECTORIES(${TF_CURRENT_BINARY_PATH_LIB})
LINK_DIRECTORIES(/usr/lib64/mysql)

SET (SERVER_LIST 
		./client_comm_handler.cc
		./client_comm_handler.h
		./client_comm_manager.cc
		./client_comm_manager.h
		./config_info.cc
		./config_info.h
		./const_zaresd_defines.h
		./register_message_factory.cc
		./zaresd_server.cc
		./zaresd_server.h
		./zares_handler_thread.cc
		./zares_handler_thread.h
		./zares_handler_thread_manager.cc
		./zares_handler_thread_manager.h
		./model/audio_manager.h
		./model/counter_manager.h
		./model/department_manager.h
		./model/file_manager.h
		./model/group_manager.h
		./model/login_manager.h
		./model/message_manager.h
		./model/model_main_manager.cc
		./model/model_main_manager.h
		./model/model_module.h
		./model/relationship_manager.h
		./model/user_manager.h
		./model/zares/zares_audio_manager_impl.cc
		./model/zares/zares_audio_manager_impl.h
		./model/zares/zares_counter_manager_impl.cc
		./model/zares/zares_counter_manager_impl.h
		./model/zares/zares_department_manager_impl.cc
		./model/zares/zares_department_manager_impl.h
		./model/zares/zares_file_manager_impl.cc
		./model/zares/zares_file_manager_impl.h
		./model/zares/zares_group_manager_impl.cc
		./model/zares/zares_group_manager_impl.h
		./model/zares/zares_login_manager_impl.cc
		./model/zares/zares_login_manager_impl.h
		./model/zares/zares_message_manager_impl.cc
		./model/zares/zares_message_manager_impl.h
		./model/zares/zares_model_module.cc
		./model/zares/zares_model_module.h
		./model/zares/zares_relationship_manager_impl.cc
		./model/zares/zares_relationship_manager_impl.h
		./model/zares/zares_user_manager_impl.cc
		./model/zares/zares_user_manager_impl.h
		./message_handler/all_user_request_handler.cc
		./message_handler/all_user_request_handler.h
		./message_handler/department_request_handler.cc
		./message_handler/department_request_handler.h
		./message_handler/file_add_offline_req_handler.cc
		./message_handler/file_add_offline_req_handler.h
		./message_handler/file_del_offline_req_handler.cc
		./message_handler/file_del_offline_req_handler.h
		./message_handler/file_has_offline_req_handler.cc
		./message_handler/file_has_offline_req_handler.h
		./message_handler/friend_list_request_handler.cc
		./message_handler/friend_list_request_handler.h
		./message_handler/group_change_member_request_handler.cc
		./message_handler/group_change_member_request_handler.h
		./message_handler/group_create_tmp_group_request_handler.cc
		./message_handler/group_create_tmp_group_request_handler.h
		./message_handler/group_dialog_list_request_handler.cc
		./message_handler/group_dialog_list_request_handler.h
		./message_handler/group_history_msg_request_handler.cc
		./message_handler/group_history_msg_request_handler.h
		./message_handler/group_list_request_handler.cc
		./message_handler/group_list_request_handler.h
		./message_handler/group_msg_read_ack_handler.cc
		./message_handler/group_msg_read_ack_handler.h
		./message_handler/group_unread_msg_count_request_handler.cc
		./message_handler/group_unread_msg_count_request_handler.h
		./message_handler/group_unread_msg_request_handler.cc
		./message_handler/group_unread_msg_request_handler.h
		./message_handler/group_user_list_request_handler.cc
		./message_handler/group_user_list_request_handler.h
		./message_handler/history_msg_request_handler.cc
		./message_handler/history_msg_request_handler.h
		./message_handler/message_handler.cc
		./message_handler/message_handler.h
		./message_handler/msg_data_handler.cc
		./message_handler/msg_data_handler.h
		./message_handler/msg_read_ack_handler.cc
		./message_handler/msg_read_ack_handler.h
		./message_handler/remove_session_request_handler.cc
		./message_handler/remove_session_request_handler.h
		./message_handler/unread_msg_count_request_handler.cc
		./message_handler/unread_msg_count_request_handler.h
		./message_handler/unread_msg_request_handler.cc
		./message_handler/unread_msg_request_handler.h
		./message_handler/users_info_request_handler.cc
		./message_handler/users_info_request_handler.h
		./message_handler/validate_request_handler.cc
		./message_handler/validate_request_handler.h
	)

ADD_EXECUTABLE(zaresd ${SERVER_LIST}
)

##update_end
TARGET_LINK_LIBRARIES(zaresd proto net db3 message_pdu base2 base dynamic_annotations libevent mysqlclient pthread rt)

