// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// �˴���Ϊ�Զ����ɣ����ں�������ʵ�������߼�
//
/**
    public DataBuffer deleteUserRecentContact(int userId, int friendUserId,
            int friendUserType, DataBuffer attachment, int version) {
        DataBuffer buffer = null;

        if (userId <= 0 || friendUserId <= 0 || friendUserType <= 0
                || BizConstants.SYS_SERVER_USER_ID == friendUserId) {
            buffer = new DataBuffer();
            buffer.writeInt(userId);
            buffer.writeInt(0);
            buffer.writeInt(friendUserId);
            buffer.writeInt(friendUserType);
            return MoguUtil.writeAttachments(buffer, attachment);
        }

        boolean isSuccess = false;
        try {
            if (1 == friendUserType) {
                isSuccess = RelationshipModel.getInstance()
                        .deleteRecentContactByUserId(userId, friendUserId);
            } else {
                Group group = GroupModel.getInstance().getGroupInfo(
                        friendUserId);
                // ���Ⱥ��������ɾ��ʧ�ܣ�Ⱥ��Ҳ�ܽ��Լ�����Ⱥ�������ϵȺ��ɾ��
                if (group == null || friendUserId != group.getGroupId()) {
                    isSuccess = false;
                } else {
                    isSuccess = GroupModel.getInstance()
                            .deleteRecentContactByGroupId(userId, friendUserId,
                                    group);
                }
            }
        } catch (SQLException e) {
            logger.error("delete recent contact error: userId = " + userId
                    + ", friendUserId = " + friendUserId + ", friendUserType ="
                    + friendUserType, e);
        }

        buffer = new DataBuffer();
        buffer.writeInt(userId); // �û�Id
        if (isSuccess) { // �ɹ�
            logger.info("delete recent contact success: result=" + isSuccess
                    + ", userId=" + userId + ", friendUserId = " + friendUserId
                    + ", friendUserType = " + friendUserType);
            buffer.writeInt(0); // ���
            buffer.writeInt(friendUserId);
            buffer.writeInt(friendUserType);
        } else { // ʧ��
            logger.info("delete recent contact error: result=" + isSuccess
                    + ", userId=" + userId + ", friendUserId = " + friendUserId
                    + ", friendUserType = " + friendUserType);
            buffer.writeInt(1); // ���
            buffer.writeInt(friendUserId);
            buffer.writeInt(friendUserType);
        }

        return MoguUtil.writeAttachments(buffer, attachment);
    }
 */


#include "zaresd/message_handler/remove_session_request_handler.h"

#include "base/logging.h"
#include "base/strings/stringprintf.h"
#include "base/memory/scoped_ptr.h"

#include "proto/remove_session_request.h"
#include "proto/remove_session_response.h"

#include "zaresd/const_zaresd_defines.h"
#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

int RemoveSessionRequestHandler::Execute(ZAresHandlerThread* context, int io_handler_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(RemoveSessionRequest, remove_session_request);

  RelationshipManager* relationship_manager = ModelMainManager::GetInstance()->GetRelationshipManager();
  GroupManager* group_manager = ModelMainManager::GetInstance()->GetGroupManager();

  RemoveSessionResponse remove_session_response;
  remove_session_response.SetReserved(remove_session_request->GetReserved());
  remove_session_response.set_req_user_id(remove_session_request->req_user_id());
  remove_session_response.set_result(0);
  remove_session_response.set_session_id(remove_session_request->session_id());
  remove_session_response.set_session_type(remove_session_request->session_type());
  remove_session_response.SetAttachData(*remove_session_request->GetAttachData());
  
  bool result = true;
  if (remove_session_request->req_user_id() == 0 ||
      remove_session_request->session_id() == 0 ||
      remove_session_request->session_type() == 0 ||
      remove_session_request->session_id() == SYS_SERVER_USER_ID
    ) {
      remove_session_response.set_result(0);
      LOG(ERROR) << "Invalid data!!";
  } else {
    if (1 == remove_session_request->session_type()) {
      result = relationship_manager->DeleteRecentContactByUserId(remove_session_request->req_user_id(), remove_session_request->session_id());
    } else {
      GroupInfo group;
      if (!group_manager->GetGroupInfo(remove_session_request->session_id(), &group) ||
            remove_session_request->session_id() != group.group_id) {
        // remove_session_response.set_result(1);
        result = false;
      } else {
        // result = group_manager->
      }
/*
      Group group = GroupModel.getInstance().getGroupInfo(
        friendUserId);
      // ���Ⱥ��������ɾ��ʧ�ܣ�Ⱥ��Ҳ�ܽ��Լ�����Ⱥ�������ϵȺ��ɾ��
      if (group == null || friendUserId != group.getGroupId()) {
        isSuccess = false;
      } else {
        isSuccess = GroupModel.getInstance()
          .deleteRecentContactByGroupId(userId, friendUserId,
          group);
      }
 */
    }
  }
  remove_session_response.set_result(result ? 0 : 1);

  if (context) {
    context->SendSessionData(io_handler_id, remove_session_response);
  }

  return 0;
}
