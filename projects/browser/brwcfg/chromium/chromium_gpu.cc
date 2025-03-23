#include "brwcfg.h"
ChromiumGpu::ChromiumGpu(const std::string &server_addr)
    : IChromium(ChromiumProcessType::ChromiumGpuProcess, server_addr) {
  Init();
}
ChromiumGpu::~ChromiumGpu() {
  UnInit();
}
void ChromiumGpu::Init() {
  uvpp_config_->RegisterClientMessageReceiveReplyCb(
      [](const ISession *session, const CommandType &cmd, const IBuffer *buffer,
         CommandType *cmd_reply, IBuffer *buffer_reply) {
        switch (LocalCommandType(cmd)) {
        case LocalCommandType::LCT_SERVER_SERVERREADY: {
          Brwcfg::GetOrCreate()->ServerStatus(true);
          LOG_INFO("module({}) ({})", "ChromiumGpu", "Received server ready.");
        } break;
        default:
          break;
        }
        LOG_INFO("module({}) reqCmd({:x}) reqBody({})", "ChromiumGpu",
                 static_cast<unsigned long>(cmd),
                 (buffer && buffer->GetDataSize() > 0)
                     ? std::string(buffer->GetData(), buffer->GetDataSize())
                     : "");
      });
  uvpp_config_->RegisterClientConnection([](const ISession *session,
                                            CommandType *cmd_reply,
                                            IBuffer *buffer_reply) {
    *cmd_reply = CommandType(LocalCommandType::LCT_CHROMIUM_GPU_PLEASEPREPARE);
    buffer_reply->SetData("Please prepare on gpu",
                          strlen("Please prepare on gpu"));
    LOG_INFO("module({}) reqBody({})", "ChromiumGpu",
             "Request server prepare.");
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
          case LocalCommandType::LCT_SERVER_SERVERREADY: {
            std::unique_lock<std::mutex> lck(gs_server_ready_mtx_,
                                             std::defer_lock);
            lck.lock();
            gs_server_ready_ = true;
            LOG_INFO("module({}) ({})", "ChromiumGpu",
                     "Received server ready.");
            lck.unlock();
          } break;
          default:
            break;
          }
          LOG_INFO("module({}) reqCmd({:x}) reqBody({})", "ChromiumGpu",
                   static_cast<unsigned long>(cmd),
                   (buffer && buffer->GetDataSize() > 0)
                       ? std::string(buffer->GetData(), buffer->GetDataSize())
                       : "");
        });
    uvpp_config_->RegisterClientConnection([](const ISession *session,
                                              CommandType *cmd_reply,
                                              IBuffer *buffer_reply) {
      *cmd_reply =
          CommandType(LocalCommandType::LCT_CHROMIUM_GPU_PLEASEPREPARE);
      buffer_reply->SetData("Please prepare on gpu",
                            strlen("Please prepare on gpu"));
      LOG_INFO("module({}) reqBody({})", "ChromiumGpu",
               "Request server prepare.");
    });
    ready_.store(true);
    threads_.emplace_back([this]() { Process(); });
  } while (0);
  LOG_INFO("module({}) identify({})", "ChromiumGpu", policy_id_);
#endif
}
void ChromiumGpu::UnInit() {
  do {

  } while (0);
}
void ChromiumGpu::Release() const {
  delete this;
}
void ChromiumGpu::OnGpuScreenshotImageStream(const char *stream,
                                             const size_t &stream_size) {
  do {
    if (!open_.load())
      break;
    if (!stream || stream_size <= 0)
      break;
    std::string pak(stream, stream_size);
    write_cache_.push(pak);
  } while (0);
}
void ChromiumGpu::Process() {
  do {
    do {
      if (write_cache_.empty())
        break;
      if (!Brwcfg::GetOrCreate()->ServerStatus())
        break;
      auto frame_buffer = write_cache_.pops();
      for (auto &buf : frame_buffer) {
        uvpp_client_->Write(
            static_cast<unsigned long>(
                LocalCommandType::LCT_CHROMIUM_GPU_FRAMEBUFFERSTREAM),
            buf.data(), buf.size());
      }
    } while (0);

    if (!open_.load()) {
      LOG_INFO("module({}) ({})", "ChromiumGpu", "Process thread stopped.");
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  } while (1);
}
#if 0
bool ChromiumGpu::Start() {
  do {
    if (!ready_.load())
      break;
    if (!uvpp_client_->Start())
      break;
    open_.store(true);
  } while (0);
  return open_.load();
}
void ChromiumGpu::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &t : threads_) {
      t.join();
    }
    threads_.clear();
    uvpp_client_->Stop();
  } while (0);
  LOG_INFO("module({}) ({})", "ChromiumGpu", "Process server stopped.");
}
void ChromiumGpu::Process() {
  do {
    do {
      if (frame_buffer_queue_.empty())
        break;
      std::unique_lock<std::mutex> lck(gs_server_ready_mtx_, std::defer_lock);
      lck.lock();
      if (!gs_server_ready_)
        break;
      lck.unlock();
      auto frame_buffer = frame_buffer_queue_.pops();
      for (auto &buf : frame_buffer) {
        uvpp_client_->Write(
            static_cast<unsigned long>(
                LocalCommandType::LCT_CHROMIUM_GPU_FRAMEBUFFERSTREAM),
            buf.data(), buf.size());
      }
    } while (0);

    if (!open_.load()) {
      LOG_INFO("module({}) ({})", "ChromiumGpu", "Process thread stopped.");
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  } while (1);
}
void ChromiumGpu::OnGpuScreenshotImageStream(const char *stream,
                                             const size_t &stream_size) {
  do {
    if (!open_.load())
      break;
    if (!stream || stream_size <= 0)
      break;
    std::string pak(stream, stream_size);
    frame_buffer_queue_.push(pak);
  } while (0);
}

#endif
