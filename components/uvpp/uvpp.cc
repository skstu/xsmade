#include "config.h"

Uvpp::Uvpp() {
}
Uvpp::~Uvpp() {
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
