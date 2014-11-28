// Copyright (C) 2012 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//
// 此代码为自动生成，请在函数体里实现您的逻辑
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
                // 如果群不存在则删除失败，群主也能将自己建的群从最近联系群中删除
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
        buffer.writeInt(userId); // 用户Id
        if (isSuccess) { // 成功
            logger.info("delete recent contact success: result=" + isSuccess
                    + ", userId=" + userId + ", friendUserId = " + friendUserId
                    + ", friendUserType = " + friendUserType);
            buffer.writeInt(0); // 结果
            buffer.writeInt(friendUserId);
            buffer.writeInt(friendUserType);
        } else { // 失败
            logger.info("delete recent contact error: result=" + isSuccess
                    + ", userId=" + userId + ", friendUserId = " + friendUserId
                    + ", friendUserType = " + friendUserType);
            buffer.writeInt(1); // 结果
            buffer.writeInt(friendUserId);
            buffer.writeInt(friendUserType);
        }

        return MoguUtil.writeAttachments(buffer, attachment);
    }
 */


#include "zaresd/message_handler/remove_session_request_handler.h"

#include "base/logging.h"
#include "base/stringprintf.h"
#include "base/memory/scoped_ptr.h"

#include "proto/remove_session_request.h"
#include "proto/remove_session_response.h"

#include "zaresd/const_zaresd_defines.h"
#include "zaresd/model/model_main_manager.h"
#include "zaresd/zares_handler_thread.h"

int RemoveSessionRequestHandler::Execute(ZAresHandlerThread* context, uint64 session_id, const message::MessagePDU* message) {
  CAST_PROTO_MESSAGE(RemoveSessionRequest, remove_session_request);

  RelationshipManager* relationship_manager = ModelMainManager::GetInstance()->GetRelationshipManager();
  GroupManager* group_manager = ModelMainManager::GetInstance()->GetGroupManager();

  RemoveSessionResponse remove_session_response;
  remove_session_response.set_req_user_id(remove_session_request->req_user_id());
  remove_session_response.set_result(0);
  remove_session_response.set_session_id(remove_session_request->session_id());
  remove_session_response.set_session_type(remove_session_request->session_type());
  remove_session_response.MutableAttachData()->CopyFrom(remove_session_request->GetAttachData());
  
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
      // 如果群不存在则删除失败，群主也能将自己建的群从最近联系群中删除
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

  context->SendSessionData(session_id, remove_session_response);

  return 0;
}
