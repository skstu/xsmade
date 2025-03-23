#include "brwcfg.h"
ChromiumMain::ChromiumMain(const std::string &server_addr)
    : IChromium(ChromiumProcessType::ChromiumProcess, server_addr) {
  Init();
}
ChromiumMain::~ChromiumMain() {
  UnInit();
}
void ChromiumMain::Init() {
  uvpp_config_->RegisterClientMessageReceiveReplyCb(
      [](const ISession *session, const CommandType &cmd, const IBuffer *buffer,
         CommandType *cmd_reply, IBuffer *buffer_reply) {
        switch (LocalCommandType(cmd)) {
        case LocalCommandType::LCT_SERVER_REQINPUT: {
          if (buffer->Empty())
            break;
          IRequest req(std::string(buffer->GetData(), buffer->GetDataSize()));
          req.SetErrno(mp_errno_t::MP_EINVALIDREQ);
          *cmd_reply =
              CommandType(LocalCommandType::LCT_CHROMIUM_MAIN_REPNOTIFY);
          do {
            if (req.GetCfg().type != brwcfg::IConfigure::Type::BrwInputEvent) {
              req.SetErrno(mp_errno_t::MP_EINVEVENT);
              break;
            }
            Brwcfg::IBrowser *brwObj =
                Brwcfg::GetOrCreate()->GetChromiumBrowserObj();

            if (!brwObj) {
              req.SetErrno(mp_errno_t::MP_ESYSNOTFOUND);
              break;
            }
            if (brwObj->IForwardInputEvent(buffer->GetData(),
                                           buffer->GetDataSize())) {
              req.SetErrno(mp_errno_t::MP_ESYSTEMEXC);
              break;
            }
            req.SetErrno(mp_errno_t::MP_OK);
          } while (0);
          std::string resBody = req.GetRes();
          buffer_reply->SetData(resBody.data(), resBody.size());
        } break;
        case LocalCommandType::LCT_SERVER_SERVERREADY: {
          Brwcfg::GetOrCreate()->ServerStatus(true);
        } break;
        default:
          break;
        }
        LOG_INFO("module({}) reqCmd({:x}) reqBody({})", "ChromiumMain",
                 static_cast<unsigned long>(cmd),
                 (buffer && buffer->GetDataSize() > 0)
                     ? std::string(buffer->GetData(), buffer->GetDataSize())
                     : "");
      });
  uvpp_config_->RegisterClientConnection([](const ISession *session,
                                            CommandType *cmd_reply,
                                            IBuffer *buffer_reply) {
    *cmd_reply = CommandType(LocalCommandType::LCT_CHROMIUM_MAIN_PLEASEPREPARE);
    buffer_reply->SetData("Please prepare on main",
                          strlen("Please prepare on main"));
    LOG_INFO("module({}) ({})", "ChromiumMain", "Request server prepare.");
  });
#if 0
  do {
    policy_id_ = Config::GetOrCreate()->GetConfigure().policy.id;
    uvpp_ = dynamic_cast<IUvpp *>(IUvpp::Create(
        Conv::u16_to_u8(Config::GetOrCreate()->GetPath().libuvpp_path)
            .c_str()));
    uvpp_config_ = uvpp_->ConfigGet();
    uvpp_config_->SetIdentify(policy_id_);
    uvpp_config_->SetServiceType(
        static_cast<unsigned long>(uvpp::ServerType::INITIATOR) |
        static_cast<unsigned long>(uvpp::AddressType::IPC) |
        static_cast<unsigned long>(uvpp::SessionType::IPC));
    std::string addr(Config::GetOrCreate()->GetSettings().server.pipe_addr);
    uvpp_config_->Address(addr.data(), addr.size());
    uvpp_client_ = uvpp_->CreateSevice();
    uvpp_config_->RegisterClientMessageReceiveReplyCb(
        [](const ISession *session, const CommandType &cmd,
           const IBuffer *buffer, CommandType *cmd_reply,
           IBuffer *buffer_reply) {
          switch (LocalCommandType(cmd)) {
          case LocalCommandType::LCT_SERVER_REQINPUT: {
            if (buffer->Empty())
              break;
            IRequest req(std::string(buffer->GetData(), buffer->GetDataSize()));
            req.SetErrno(mp_errno_t::MP_EINVALIDREQ);
            *cmd_reply =
                CommandType(LocalCommandType::LCT_CHROMIUM_MAIN_REPNOTIFY);
            do {
              if (req.GetCfg().type !=
                  brwcfg::IConfigure::Type::BrwInputEvent) {
                req.SetErrno(mp_errno_t::MP_EINVEVENT);
                break;
              }
              Brwcfg::IBrowser *brwObj =
                  Brwcfg::GetOrCreate()->GetChromiumBrowserObj();

              if (!brwObj) {
                req.SetErrno(mp_errno_t::MP_ESYSNOTFOUND);
                break;
              }
              if (brwObj->IForwardInputEvent(buffer->GetData(),
                                             buffer->GetDataSize())) {
                req.SetErrno(mp_errno_t::MP_ESYSTEMEXC);
                break;
              }
              req.SetErrno(mp_errno_t::MP_OK);
            } while (0);
            std::string resBody = req.GetRes();
            buffer_reply->SetData(resBody.data(), resBody.size());
          } break;
          case LocalCommandType::LCT_SERVER_SERVERREADY: {
            std::unique_lock<std::mutex> lck(gs_server_ready_mtx_,
                                             std::defer_lock);
            lck.lock();
            gs_server_ready_ = true;
            lck.unlock();
          } break;
          default:
            break;
          }
          LOG_INFO("module({}) reqCmd({:x}) reqBody({})", "ChromiumMain",
                   static_cast<unsigned long>(cmd),
                   (buffer && buffer->GetDataSize() > 0)
                       ? std::string(buffer->GetData(), buffer->GetDataSize())
                       : "");
        });
    uvpp_config_->RegisterClientConnection([](const ISession *session,
                                              CommandType *cmd_reply,
                                              IBuffer *buffer_reply) {
      *cmd_reply =
          CommandType(LocalCommandType::LCT_CHROMIUM_MAIN_PLEASEPREPARE);
      buffer_reply->SetData("Please prepare on main",
                            strlen("Please prepare on main"));
      LOG_INFO("module({}) ({})", "ChromiumMain", "Request server prepare.");
    });
    ready_.store(true);
  } while (0);
#endif
}
void ChromiumMain::UnInit() {
}
void ChromiumMain::Release() const {
  delete this;
}
#if 0
bool ChromiumMain::Start() {
  
  do {
    if (!ready_.load())
      break;
    if (!uvpp_client_->Start())
      break;
    open_.store(true);
  } while (0);
  return open_.load();
}
void ChromiumMain::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    uvpp_client_->Stop();
  } while (0);
}
#endif