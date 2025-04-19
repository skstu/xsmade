#include "server.h"

Server::Server() {
  Init();
}
Server::~Server() {
  UnInit();
}
void Server::Init() {
  do {
#if ENABLE_UVPP
    uvpp_ = static_cast<IUvpp *>(IUvpp::Create(
        Conv::u16_to_u8(Config::GetOrCreate()->GetPath().libuvpp_path)
            .c_str()));
    if (!uvpp_) {
      LOG_INFO("{} is empty pointer.", "uvpp_");
      std::cout << "uvpp_ is empty pointer." << std::endl;
      break;
    }
    uvpp_config_ = uvpp_->ConfigGet();
    if (!uvpp_config_) {
      LOG_INFO("{} is empty pointer.", "uvpp_config_");
      std::cout << "uvpp_config_ is empty pointer." << std::endl;
      break;
    }
    uvpp_config_->SetServiceType(
        static_cast<unsigned long>(uvpp::ServerType::ACCEPTOR) |
        static_cast<unsigned long>(uvpp::AddressType::IPC) |
        static_cast<unsigned long>(uvpp::SessionType::IPC));
    const std::string address =
        Config::GetOrCreate()->GetSettings().server.pipe_addr;
    uvpp_config_->Address(address.data(), address.size());
    std::cout << address << std::endl;
    std::cout << "XS® Pipe Server (" << address << ")" << std::endl;
    uvpp_config_->RegisterServerHelloCb(
        [](ISession *session, const IBuffer *buffer, IBuffer *) {});
    uvpp_config_->RegisterServerReadyCb([]() {
      LOG_INFO("module({}) ({})", "Server", "Service ready.");
      std::cout << "XS® Pipe Server readyed." << std::endl;
    });
    uvpp_config_->RegisterServerSessionReadyCb([](ISession *session) {
      session->Route(Server::GetOrCreate());
      const std::string log =
          fmt::format("Server session({})({}) readyed.", session->GetIdentify(),
                      session->Address());
      LOG_INFO("module({}) ({})", "Server", log);
    });
    uvpp_config_->RegisterServerSessionDestroyCb([](const ISession *session) {
      const unsigned long long identify = session->GetIdentify();
      const browser_id_t brwid = stl::HighLowStorage(identify).Low();
      const xs_process_id_t pid = stl::HighLowStorage(identify).High();
      mp_errno_t ret = mp_errno_t::MP_EUNKN;
      Server::GetOrCreate()->DestroyBrowser(brwid, ret);
    });
    uvpp_config_->RegisterServerMessageReceiveReplyCb(
        [](const ISession *session, const CommandType &inCmd,
           const IBuffer *msg, CommandType &repCmd, IBuffer *repMsg) {
          mp_errno_t ret = mp_errno_t::MP_EUNKN;
          Server *__this = reinterpret_cast<Server *>(session->Route());
          if (!__this)
            return;
          const unsigned long long identify = session->GetIdentify();
          const browser_id_t brwid = stl::HighLowStorage(identify).Low();
          const xs_process_id_t pid = stl::HighLowStorage(identify).High();
          command_type_t cmd =
              GetCommandType(static_cast<command_type_t>(inCmd));
          chromium_process_type_t chromium_process_type =
              GetChromiumProcessType(static_cast<command_type_t>(inCmd));

          IChromiumHost *pChromiumHost =
              Server::GetOrCreate()->GetBrowser(brwid, ret);
          if (!pChromiumHost)
            return;
          pChromiumHost->ProcessReady(chromium_process_type, pid, session);
#if 0
          switch (chromium_process_type) {
          case chromium_process_type_t::CHROMIUM_PROCESS_TYPE_MAIN: {
            __this->OnChromiumMainMessage(session, inCmd, msg, repCmd, repMsg);
          } break;
          case chromium_process_type_t::CHROMIUM_PROCESS_TYPE_GPU: {
            __this->OnChromiumGpuMessage(session, inCmd, msg, repCmd, repMsg);
          } break;
          case chromium_process_type_t::CHROMIUM_PROCESS_TYPE_RENDERER: {
            __this->OnChromiumRendererMessage(session, inCmd, msg, repCmd,
                                              repMsg);
          } break;
          default:
            break;
          }
#endif
        });
#endif ///#if ENABLE_UVPP
    ready_.store(true);
  } while (0);
}
void Server::UnInit() {
#if ENABLE_FFCODEC
  SK_DELETE_PTR(ffcodec_);
#endif
}
bool Server::Start(void) {
  do {
    if (!ready_.load() || open_.load())
      break;
#if ENABLE_UVPP
    if (!uvpp_) {
      LOG_INFO("{} is empty pointer.", "uvpp_");
      std::cout << "uvpp_ is empty pointer." << std::endl;
      break;
    }
    uvpp_service_ = uvpp_->CreateSevice();
    if (!uvpp_service_) {
      LOG_INFO("{} is empty pointer.", "uvpp_service_");
      std::cout << "uvpp_service_ is empty pointer." << std::endl;
      break;
    }
    uvpp_service_->Start();
#endif
    open_.store(true);

    threads_.emplace_back([this]() { Process(); });
  } while (0);
  return open_.load();
}
void Server::Stop(void) {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &t : threads_) {
      t.join();
    }
    threads_.clear();
    uvpp_service_->Stop();
  } while (0);
}
IChromiumHost *Server::GetBrowser(const policy_id_t &brwid,
                                  mp_errno_t &ret) const {
  IChromiumHost *result = nullptr;
  ret = mp_errno_t::MP_EUNKN;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    auto fExists = chromium_host_.find(brwid);
    if (fExists == chromium_host_.end())
      break;
    result = fExists->second;
    ret = MP_OK;
  } while (0);
  return result;
}
IChromiumHost *Server::CreateBrowser(const brwcfg::IConfigure &cfg,
                                     mp_errno_t &ret) {
  IChromiumHost *result = nullptr;
  std::lock_guard<std::mutex> lck(*mtx_);
  const auto config = Config::GetOrCreate();
  do {
    if (cfg.GetBrwId() <= 0) {
      ret = mp_errno_t::MP_EINVBRWID;
      break;
    }
    auto fExists = chromium_host_.find(cfg.GetBrwId());
    if (fExists != chromium_host_.end()) {
      ret = mp_errno_t::MP_EALREADY;
      result = fExists->second;
      break;
    }
    if (!config->CreateBrowserEnv(cfg.GetBrwId(), cfg)) {
      ret = mp_errno_t::MP_EBRWENVCFG;
      break;
    }
    result = new IChromiumHost(cfg.Serialization());
    if (!result->Open()) {
      ret = mp_errno_t::MP_EBRWOPEN;
      result->Release();
      break;
    }
    chromium_host_.emplace(cfg.GetPolicyId(), result);
    ret = mp_errno_t::MP_OK;
  } while (0);
  return result;
}
bool Server::DestroyBrowser(const browser_id_t &brwid, mp_errno_t &ret) {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    auto f = chromium_host_.find(brwid);
    if (f == chromium_host_.end()) {
      ret = mp_errno_t::MP_ENOTFOUND;
      break;
    }
    f->second->Close();
    f->second->Release();
    chromium_host_.erase(brwid);
    ret = mp_errno_t::MP_OK;
    result = true;
  } while (0);
  return result;
}
void Server::OnNotify(const browser_id_t &brwid, const std::string &res) const {
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (!notify_cb_)
      break;
    if (res.empty())
      break;
    brwcfg::IConfigure resObj(res);
    unsigned long reslen = static_cast<unsigned long>(res.size());
    char *p = (char *)malloc(reslen);
    memcpy(p, res.data(), reslen);
    notify_cb_(brwid, resObj.reqid, mp_errno_t::MP_ESEEDETAILS, p, reslen);
  } while (0);
  LOG_INFO("module({}) ({})", "ServerNotify", res);
}
void Server::OnFrameBufferStream(const browser_id_t &brwid, const char *stream,
                                 const size_t &stream_len) const {
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (!frame_buffer_stream_cb_)
      break;
    if (!stream || stream_len <= 0)
      break;
    char *p = (char *)malloc(stream_len);
    memcpy(p, stream, stream_len);
    frame_buffer_stream_cb_(brwid, p, static_cast<unsigned long>(stream_len));
  } while (0);
}
void Server::RegisterCbs(tf_frame_buffer_stream_cb frame_buffer_stream_cb,
                         tf_notify_cb notify_cb) {
  std::lock_guard<std::mutex> lck(*mtx_);
  frame_buffer_stream_cb_ = frame_buffer_stream_cb;
  notify_cb_ = notify_cb;
}
void Server::Request(IRequest *req) {
  std::lock_guard<std::mutex> lck(*mtx_);
  request_queue_.push(req);
}

////////////////////////////////////////////////////////////////////
static Server *__gpsServer = nullptr;
Server *Server::GetOrCreate() {
  if (!__gpsServer)
    __gpsServer = new Server();
  return __gpsServer;
}
void Server::Destroy() {
  if (__gpsServer) {
    __gpsServer->Stop();
  }
  SK_DELETE_PTR(__gpsServer);
}

#if 0 //!@ code backup
if (cmd == CommandType::TESTMSG) {
  std::cout << "Server recved test msg." << std::endl;
  repCmd = CommandType::TESTMSG;
  repMsg->SetData("Server test msg", strlen("Server test msg"));
  return;
}
const unsigned long long identify = session->GetIdentify();
const browser_id_t brwid = stl::HighLowStorage(identify).High();
const xs_process_id_t pid = stl::HighLowStorage(identify).Low();
if (brwid <= 0) {
  LOG_ERROR("module({}) cmd({:x}) brwid({}) desc({})", "Server",
            static_cast<unsigned long>(cmd), brwid,
            "Invalid session brwid.");
  return;
}

mp_errno_t ret = mp_errno_t::MP_EUNKN;
IChromium *chromium = Server::GetOrCreate()->GetBrowser(brwid, ret);

switch (static_cast<command_type_t>(cmd)) {
case command_type_t::LCT_CHROMIUM_GPU_FRAMEBUFFERSTREAM: {
  Server::GetOrCreate()->OnFrameBufferStream(brwid, msg->GetData(),
                                             msg->GetDataSize());
} break;
case command_type_t::LCT_CHROMIUM_GPU_REPNOTIFY: {
} break;
case command_type_t::LCT_CHROMIUM_MAIN_REPNOTIFY: {
  if (msg->Empty()) {
    LOG_WARN("Web notify msg is empty({})",
             "LCT_CHROMIUM_MAIN_REPNOTIFY");
    std::cout << fmt::format("Web notify msg is empty({})",
                             "LCT_CHROMIUM_MAIN_REPNOTIFY")
              << std::endl;
    break;
  }
  std::string notify_body(msg->GetData(), msg->GetDataSize());
  std::cout << notify_body << std::endl;
  Server::GetOrCreate()->OnNotify(brwid, notify_body);
  LOG_INFO("Recved web notify msg is ({})", notify_body.c_str());
} break;
case command_type_t::LCT_CHROMIUM_MAIN_PLEASEPREPARE: {
  if (!chromium)
    break;
  chromium->ProcessReady(ChromiumProcessType::ChromiumProcess, pid,
                         session);
  repCmd = static_cast<CommandType>(
      command_type_t::LCT_SERVER_SERVERREADY);
  repMsg->SetData("Server ready", strlen("Server ready"));
  LOG_INFO("module({}) cmd({:x}) def({}) brwid({}) desc({}) ",
           "Server", static_cast<unsigned long>(cmd),
           "LCT_CHROMIUM_MAIN_PLEASEPREPARE", brwid,
           "Reply to chromium 'main' process ready.");
} break;
case command_type_t::LCT_CHROMIUM_GPU_PLEASEPREPARE: {
  if (!chromium)
    break;
  chromium->ProcessReady(ChromiumProcessType::ChromiumGpuProcess, pid,
                         session);
  repCmd = static_cast<CommandType>(
      command_type_t::LCT_SERVER_SERVERREADY);
  repMsg->SetData("Server ready", strlen("Server ready"));
  LOG_INFO("module({}) cmd({:x}) def({}) brwid({}) desc({}) ",
           "Server", static_cast<unsigned long>(cmd),
           "LCT_CHROMIUM_GPU_PLEASEPREPARE", brwid,
           "Reply to chromium 'gpu' process ready.");
} break;
default:
  break;
}

#endif