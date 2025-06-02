#include "brwcfg.h"
ChromiumGpu::ChromiumGpu(const std::string &server_addr)
    : IChromium(ChromiumProcessType::ChromiumGpuProcess, server_addr) {
  Init();
}
ChromiumGpu::~ChromiumGpu() {
  UnInit();
}
void ChromiumGpu::Init() {
#if ENABLE_UVPP
  uvpp_config_->RegisterClientMessageReceiveReplyCb(
      [](const ISession *session, const CommandType &cmd, const IBuffer *buffer,
         CommandType *cmd_reply, IBuffer *buffer_reply) {
        switch (static_cast<command_type_t>(cmd)) {
        case command_type_t::LCT_SERVER_SERVERREADY: {
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
    *cmd_reply = CommandType(command_type_t::LCT_CHROMIUM_GPU_PLEASEPREPARE);
    buffer_reply->SetData("Please prepare on gpu",
                          strlen("Please prepare on gpu"));
    LOG_INFO("module({}) reqBody({})", "ChromiumGpu",
             "Request server prepare.");
  });
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
#if ENABLE_UVPP
  do {
    if (!open_.load())
      break;
    if (!stream || stream_size <= 0)
      break;
    std::string pak(stream, stream_size);
    write_cache_.push(pak);
  } while (0);
#endif
}
void ChromiumGpu::Process() {
#if ENABLE_UVPP
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
                command_type_t::LCT_CHROMIUM_GPU_FRAMEBUFFERSTREAM),
            buf.data(), buf.size());
      }
    } while (0);

    if (!open_.load()) {
      LOG_INFO("module({}) ({})", "ChromiumGpu", "Process thread stopped.");
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  } while (1);
#endif
}
