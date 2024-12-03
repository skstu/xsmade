#include "config.h"

Uvpp::Uvpp() {
}
Uvpp::~Uvpp() {
}
SHARED_API void *interface_init(void *data, unsigned long len) {
  if (!__gpService)
    __gpService = new Service();
  return dynamic_cast<IServiceManager *>(__gpService);
#if 0
	__gpConfig = new Config();
	void* result = nullptr;
	unsigned long type = 0;
	do {
		ServerType server_type = Protocol::GetServerType(type);
		SessionType session_type = Protocol::GetSessionType(type);
		AddressType address_type = Protocol::GetAddressType(type);
		if (server_type == ServerType::UNKNOWN || \
			session_type == SessionType::UNKNOWN || \
			address_type == AddressType::UNKNOWN)
			return result;

		switch (server_type) {
		case ServerType::ACCEPTOR: {
			result = reinterpret_cast<decltype(result)>(dynamic_cast<IService*>(new Server()));
		}break;
		case ServerType::INITIATOR: {
			result = reinterpret_cast<decltype(result)>(dynamic_cast<IService*>(new Client()));
		}break;
		default:
			break;
		}
	} while (0);
	return result;
#endif
}
SHARED_API void interface_uninit() {
  SK_DELETE_PTR(__gpService);
}
