#include "config.h"

Service::Service() {
  Init();
}

Service::~Service() {
  UnInit();
}

void Service::Init() {
  config_ = new Config();
}
void Service::UnInit() {
  SK_DELETE_PTR(config_);
}
IBuffer *Service::CreateBuffer(const char *data, size_t len) const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return dynamic_cast<IBuffer *>(new Buffer(data, len));
}
bool Service::Ready() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return ready_.load();
}
IConfig *Service::ConfigGet() const {
  std::lock_guard<std::mutex> lock{*mtx_};
  return dynamic_cast<IConfig *>(config_);
}
bool Service::Start() {
  return true;
}
void Service::Stop() {

  auto sksk = 0;
}
void Service::Release() const {
  delete this;
}

IService *Service::GetSevice() const {
  IService *result = nullptr;
  std::lock_guard<std::mutex> lock{*mtx_};
  const unsigned long service_type = config_->GetServiceType();
  do {
    ServerType server_type = Protocol::GetServerType(service_type);
    SessionType session_type = Protocol::GetSessionType(service_type);
    AddressType address_type = Protocol::GetAddressType(service_type);
    if (server_type == ServerType::UNKNOWN ||
        session_type == SessionType::UNKNOWN ||
        address_type == AddressType::UNKNOWN)
      break;

    switch (server_type) {
    case ServerType::ACCEPTOR: {
      if (!__gpServer)
        __gpServer = new Server();
      result = dynamic_cast<IService *>(__gpServer);
    } break;
    case ServerType::INITIATOR: {
      if (!__gpClient)
        __gpClient = new Client();
      result = dynamic_cast<IService *>(__gpClient);
    } break;
    default:
      break;
    }
  } while (0);
  return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
Client *__gpClient = nullptr;
Server *__gpServer = nullptr;
Service *__gpService = nullptr;
Service *ServiceGet() {
  return __gpService;
}