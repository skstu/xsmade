#include "config.h"

Uvpp::Uvpp() {
  Init();
}
Uvpp::~Uvpp() {
  UnInit();
}
void Uvpp::Init() {
}
void Uvpp::UnInit() {
}
bool Uvpp::Start() {
  do {
    if (open_.load())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { MainProcess(); });
  } while (0);
  return open_.load();
}
void Uvpp::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &t : threads_) {
      t.join();
    }
    threads_.clear();
  } while (0);
}
bool Uvpp::Ready() const {
  return true;
}

void Uvpp::WorkProcess(uv_handle_t *handle, void *arg) {
  do {

  } while (0);
}
void Uvpp::MainProcess() {
  uv_loop_t *loop = nullptr;
  do {
    loop = (uv_loop_t *)malloc(sizeof(uv_loop_t));
    if (0 != uv_loop_init(loop))
      break;

    do {
      uv_walk(loop, WorkProcess, nullptr);

      uv_run(loop, uv_run_mode::UV_RUN_NOWAIT);

      if (!open_.load()) {
        uv_walk(loop, Protocol::walk_close_handle_cb, this);
        uv_run(loop, uv_run_mode::UV_RUN_DEFAULT);
        uv_loop_close(loop);
        break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    } while (1);
  } while (0);
  if (loop) {
    free(loop);
    loop = nullptr;
  }
}
IConfig *Uvpp::ConfigGet() const {
  return dynamic_cast<IConfig *>(Config::Get());
}
IBuffer *Uvpp::CreateBuffer(const char *data, size_t len) const {
  return dynamic_cast<IBuffer *>(new Buffer(data, len));
}
IService *Uvpp::CreateSevice() const {
  IService *result = nullptr;
  const unsigned long service_type = Config::Get()->GetServiceType();
  do {
    ServerType server_type = Protocol::GetServerType(service_type);
    SessionType session_type = Protocol::GetSessionType(service_type);
    AddressType address_type = Protocol::GetAddressType(service_type);
    if (server_type == ServerType::UNKNOWN ||
        session_type == SessionType::UNKNOWN ||
        address_type == AddressType::UNKNOWN)
      break;
    switch (server_type) {
    case ServerType::UTILITY: {

    } break;
    case ServerType::ACCEPTOR: {
      result = dynamic_cast<IService *>(Server::Create());
    } break;
    case ServerType::INITIATOR: {
      result = dynamic_cast<IService *>(Client::Create());
    } break;
    default:
      break;
    }
  } while (0);
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////////
static Uvpp *__gpUvpp = nullptr;
Uvpp *Uvpp::Create() {
  if (!__gpUvpp)
    __gpUvpp = new Uvpp();
  return __gpUvpp;
}
void Uvpp::Destroy() {
  SK_DELETE_PTR(__gpUvpp);
}

#ifdef __cplusplus
extern "C" {
#endif

SHARED_API void *interface_init(void *data, unsigned long len) {
  auto config = Config::Create();
  auto uvpp = Uvpp::Create();

  return reinterpret_cast<void *>(uvpp);
}
SHARED_API void interface_uninit() {
  Server::Destroy();
  Client::Destroy();
  Config::Destroy();
  Uvpp::Destroy();
}

#ifdef __cplusplus
}
#endif
