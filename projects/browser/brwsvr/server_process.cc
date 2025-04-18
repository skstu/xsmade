#include "server.h"
//!@ Private
void Server::OnChromiumMainMessage(const ISession *session,
                                   const CommandType &inCmd, const IBuffer *msg,
                                   CommandType &repCmd, IBuffer *repMsg) {
}
void Server::OnChromiumGpuMessage(const ISession *session,
                                  const CommandType &inCmd, const IBuffer *msg,
                                  CommandType &repCmd, IBuffer *repMsg) {
}
void Server::OnChromiumRendererMessage(const ISession *session,
                                       const CommandType &inCmd,
                                       const IBuffer *msg, CommandType &repCmd,
                                       IBuffer *repMsg) {
}

void Server::Process(void) {
  const Config *config = Config::GetOrCreate();
  do {
    do { //!@ process request queue.
      if (request_queue_.empty())
        break;
      mp_errno_t ret = mp_errno_t::MP_EUNKN;
      std::string resBody("{}");
      IRequest *req = *request_queue_.pop();
      const policy_id_t policy_id = req->GetCfg().policy.id;
      const request_id_t reqid = req->GetCfg().reqid;
      do {
        if (!req->Ready())
          break;
        LOG_INFO("module({}) cfgType({:x}) cfgBody({})", "ServerProcess",
                 static_cast<unsigned long>(req->GetCfg().GetType()),
                 req->GetCfg().Serialization());
        switch (req->GetCfg().GetType()) {
        case brwcfg::IConfigure::Type::BrwCreate: {
          IChromiumHost *pChromium =
              CreateBrowser(req->GetCfg().Serialization(), ret);
          if (!pChromium)
            break;
        } break;
        case brwcfg::IConfigure::Type::BrwDestory: {
          DestroyBrowser(req->GetCfg().GetBrwId(), ret);
        } break;
        case brwcfg::IConfigure::Type::BrwCommandEvent:
          //[[fallthrough]];
          // {
          //   IChromium *pChromium = GetBrowser(policy_id, ret);
          //   if (!pChromium)
          //     break;
          //   if (!pChromium->Request(command_type_t::LCT_SERVER_REQCOMMAND,
          //                           req->GetCfg().Serialization(), ret))
          //     break;
          //   ret = MP_DONE;
          // }
          break;
        case brwcfg::IConfigure::Type::BrwInputEvent: {
          // IChromium *pChromium = GetBrowser(policy_id, ret);
          // if (!pChromium)
          //   break;
          // if (!pChromium->Request(command_type_t::LCT_SERVER_REQINPUT,
          //                         req->GetCfg().Serialization(), ret))
          //   break;
          // ret = MP_DONE;
        } break;
        default:
          break;
        }
      } while (0);
      if (ret != MP_DONE && ret != MP_OK) {
        req->SetErrno(ret);
        resBody = req->GetRes();
        OnNotify(policy_id, resBody);
      } else {
        LOG_INFO("Web request done({})", static_cast<int>(ret));
      }
    } while (0);
    if (!open_.load()) {
      LOG_INFO("module({}) ({})", "ServerProcess", "Process thread stopped.");
      std::cout << "Process thread stopped." << std::endl;
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  } while (1);
}