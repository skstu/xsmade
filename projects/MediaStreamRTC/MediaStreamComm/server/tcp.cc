#include "MediaStreamComm.h"

using namespace uvpp;

ServerTcp::ServerTcp() {
  Init();
}
ServerTcp::~ServerTcp() {
  UnInit();
}
void ServerTcp::Release() const {
  delete this;
}
void ServerTcp::Init() {
  do {
    uvpp_ = IUvpp::Create(
        (System::GetCurrentProcessPath() + "/plugins/uvpp.dll").c_str());
    if (!uvpp_)
      break;

    IConfig *pUvppConfig = uvpp_->ConfigGet();
    pUvppConfig->SetServiceType(
        static_cast<unsigned long>(ServerType::ACCEPTOR) |
        static_cast<unsigned long>(AddressType::IPV4) |
        static_cast<unsigned long>(SessionType::TCP));
    std::string addr(R"(0.0.0.0:10100)");
    pUvppConfig->Address(addr.data(), addr.size());
    server_ = uvpp_->CreateSevice();
    if (!server_)
      break;
    pUvppConfig->RegisterServerReadyCb(
        []() { std::cout << "Server ready." << std::endl; });
    pUvppConfig->RegisterServerSessionReadyCb([](const ISession *session) {
      std::cout << fmt::format("session create '{}'", session->Address())
                << std::endl;
    });
    pUvppConfig->RegisterServerSessionDestroyCb([](const ISession *session) {
      std::cout << fmt::format("session destroy '{}'", session->Address())
                << std::endl;
    });
    pUvppConfig->RegisterServerMessageCb([](const ISession *session,
                                            const CommandType &cmd,
                                            const IBuffer *buffer) {
      std::cout << buffer->GetData() << std::endl;
    });

    ready_.store(true);
  } while (0);
}
void ServerTcp::UnInit() {
  do {
    if (!uvpp_)
      break;
    IUvpp::Destroy(&uvpp_);
  } while (0);
  ready_.store(false);
}
bool ServerTcp::Start() {
  do {
    if (open_.load() || !ready_.load())
      break;
    if (!server_->Start())
      break;
    open_.store(true);
  } while (0);
  return open_.load();
}
void ServerTcp::Stop() {
  do {
    if (!open_.load())
      break;
    server_->Stop();

  } while (0);
  open_.store(false);
}