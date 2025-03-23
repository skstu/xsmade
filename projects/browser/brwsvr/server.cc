#include "server.h"

Server::Server() {
  Init();
}
Server::~Server() {
  UnInit();
}
void Server::Init() {
  do {
    uvpp_ = dynamic_cast<IUvpp *>(IUvpp::Create(
        Conv::u16_to_u8(Config::GetOrCreate()->GetPath().libuvpp_path)
            .c_str()));
    if (!uvpp_)
      break;
    uvpp_config_ = uvpp_->ConfigGet();
    if (!uvpp_config_)
      break;
    uvpp_config_->SetServiceType(
        static_cast<unsigned long>(uvpp::ServerType::ACCEPTOR) |
        static_cast<unsigned long>(uvpp::AddressType::IPC) |
        static_cast<unsigned long>(uvpp::SessionType::IPC));
    uvpp_config_->Address(
        Config::GetOrCreate()->GetSettings().server.pipe_addr.data(),
        Config::GetOrCreate()->GetSettings().server.pipe_addr.size());
    uvpp_config_->RegisterServerHelloCb(
        [](ISession *session, const IBuffer *buffer, IBuffer *) {
          do {
            const IBuffer *hello = session->GetHelloBuffer();
            if (!hello)
              break;
            if (hello->Empty())
              break;
            policy_id_t policy_id = 0;
            memcpy(&policy_id, hello->GetData(), hello->GetDataSize());
            session->Route(Brwmnr::GetOrCreate()->GetBrowser(policy_id));
          } while (0);
        });
    uvpp_config_->RegisterServerReadyCb([]() {
      LOG_INFO("module({}) ({})", "Server", "Service ready.");
      std::cout << "Server readyed." << std::endl;
    });
    uvpp_config_->RegisterServerSessionReadyCb([](ISession *session) {});
    uvpp_config_->RegisterServerSessionDestroyCb([](const ISession *session) {
      Server::GetOrCreate()->sessions_gpu_.pop(session->GetIdentify());
      Server::GetOrCreate()->sessions_main_.pop(session->GetIdentify());
    });
    uvpp_config_->RegisterServerMessageReceiveReplyCb(
        [](const ISession *session, const CommandType &cmd, const IBuffer *msg,
           CommandType &repCmd, IBuffer *repMsg) {
          const unsigned long long identify = session->GetIdentify();
          switch (LocalCommandType(cmd)) {
          case LocalCommandType::LCT_CHROMIUM_GPU_FRAMEBUFFERSTREAM: {
            policy_id_t policy_id = session->GetIdentify();
            Server::GetOrCreate()->OnFrameBufferStream(
                policy_id, msg->GetData(), msg->GetDataSize());
          } break;
          case LocalCommandType::LCT_CHROMIUM_GPU_REPNOTIFY: {
          } break;
          case LocalCommandType::LCT_CHROMIUM_MAIN_REPNOTIFY: {
            if (msg->Empty())
              break;
            std::string notify_body(msg->GetData(), msg->GetDataSize());
            std::cout << notify_body << std::endl;
            Server::GetOrCreate()->OnNotify(identify, notify_body);
          } break;
          case LocalCommandType::LCT_CHROMIUM_MAIN_PLEASEPREPARE: {
            Server::GetOrCreate()->sessions_main_.push(
                identify, const_cast<uvpp::ISession *>(session));
            repCmd = CommandType(LocalCommandType::LCT_SERVER_SERVERREADY);
            repMsg->SetData("Server ready", strlen("Server ready"));
            LOG_INFO("module({}) cmd({:x}) def({}) identify({}) desc({}) ",
                     "Server", static_cast<unsigned long>(cmd),
                     "LCT_CHROMIUM_MAIN_PLEASEPREPARE", identify,
                     "Reply to chromium 'main' process ready.");
          } break;
          case LocalCommandType::LCT_CHROMIUM_GPU_PLEASEPREPARE: {
            repCmd = CommandType(LocalCommandType::LCT_SERVER_SERVERREADY);
            repMsg->SetData("Server ready", strlen("Server ready"));
            Server::GetOrCreate()->sessions_gpu_.push(
                identify, const_cast<uvpp::ISession *>(session));
            LOG_INFO("module({}) cmd({:x}) def({}) identify({}) desc({}) ",
                     "Server", static_cast<unsigned long>(cmd),
                     "LCT_CHROMIUM_GPU_PLEASEPREPARE", identify,
                     "Reply to chromium 'gpu' process ready.");
          } break;
          default:
            break;
          }
        });

#if ENABLE_FFCODEC
    const std::string stream_path = R"(C:\Users\k34ub\Desktop\test.mp4)";
    stl::File::Remove(stream_path);
    ffcodec_ = new FFCodec(stream_path);
#if 0
    const char* filename = "C:\\Users\\k34ub\\Desktop\\ffTests\\test.mp4";//"c:\\temp\\1.avi";
    int width = 480;
    int height = 360;
    int fps = 60;
    int bit_rate = 200000; // 200 kbps


    ffcodec_->setUpEncoder(filename, width, height, fps, bit_rate);
    //ffcodec_->encodeTestVideo();
    ffcodec_->encodeFromFolder(R"(C:\Users\k34ub\source\skstu\xsmade\bin\tests\1742264407208686\)", "", 129);
    //encoder.encodeFromFolder("T:\\Bastian\\Bilder\\Photon Tracer\\Videos\\", "frame_", 11);

    ffcodec_->closeEncoder();
#endif
#endif
    ready_.store(true);
  } while (0);
}
bool Server::RequestInput(const browser_id_t &brwid,
                          const std::string &body) const {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (!uvpp_service_ || body.empty())
      break;
    if (sessions_main_.size() <= 0)
      break;
    auto f = sessions_main_.search(brwid);
    if (!f)
      break;
    uvpp::ISession *f_session = *f;
    result = f_session->Write(
        static_cast<unsigned long>(LocalCommandType::LCT_SERVER_REQINPUT),
        body.data(), body.size());
  } while (0);
  return result;
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
    uvpp_service_ = uvpp_->CreateSevice();
    if (!uvpp_service_)
      break;
    open_.store(true);
    uvpp_service_->Start();
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
