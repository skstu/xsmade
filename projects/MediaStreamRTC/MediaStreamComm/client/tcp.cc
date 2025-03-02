#include "MediaStreamComm.h"
using namespace uvpp;

ClientTcp::ClientTcp() {
  Init();
}
ClientTcp::~ClientTcp() {
  UnInit();
}
void ClientTcp::Release() const {
  delete this;
}
void ClientTcp::Init() {
  do {
    uvpp_ = IUvpp::Create(
        (System::GetCurrentProcessPath() + "/plugins/uvpp.dll").c_str());
    if (!uvpp_)
      break;

    IConfig *pUvppConfig = uvpp_->ConfigGet();
    pUvppConfig->SetServiceType(
        static_cast<unsigned long>(ServerType::INITIATOR) |
        static_cast<unsigned long>(AddressType::IPV4) |
        static_cast<unsigned long>(SessionType::TCP));
    std::string addr(R"(192.168.30.11:10100)");
    pUvppConfig->Address(addr.data(), addr.size());
    client_ = uvpp_->CreateSevice();
    if (!client_)
      break;
    pUvppConfig->RegisterClientConnection([](const ISession *session) {
      std::cout << fmt::format("connect to server({})", session->Address())
                << std::endl;
    });
    pUvppConfig->RegisterClientDisconnection([](const ISession *session) {
      std::cout << fmt::format("disconnect to server({})", session->Address())
                << std::endl;
    });
    ready_.store(true);
  } while (0);
}
void ClientTcp::UnInit() {
  do {
    if (!uvpp_)
      break;
    IUvpp::Destroy(&uvpp_);
  } while (0);
  ready_.store(false);
}
bool ClientTcp::Start() {
  do {
    if (open_.load() || !ready_.load())
      break;
    if (!client_->Start())
      break;
    open_.store(true);
  } while (0);
  return open_.load();
}
void ClientTcp::Stop() {
  do {
    if (!open_.load())
      break;
    client_->Stop();
  } while (0);
  open_.store(false);
}
