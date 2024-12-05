#include <system.h>
#include "sys.hpp"
#include <stl.hpp>
#include <fmt/format.h>
#include <base/uvpp/export.h>
using namespace uvpp;

int main(int argc, char **argv) {
  std::string module_path =
      System::GetCurrentProcessPath() + "/plugins/uvpp.dll";
  uvpp::IUvpp *pUvpp = uvpp::IUvpp::Create(module_path.c_str());
  uvpp::IConfig *pUvppConfig = pUvpp->ConfigGet();
  pUvppConfig->SetServiceType(
      static_cast<unsigned long>(uvpp::ServerType::ACCEPTOR) |
      static_cast<unsigned long>(uvpp::AddressType::IPC) |
      static_cast<unsigned long>(uvpp::SessionType::IPC));
  std::string addr(R"(\\.\pipe\test_uvpp_server)");
  pUvppConfig->Address(addr.data(), addr.size());
  uvpp::IService *pService = pUvpp->CreateSevice();
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
  pService->Start();
  std::string input;
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input == "q" || std::cin.eof()) {
      break;
    } else {
    }
  } while (1);
  uvpp::IUvpp::Destroy(&pUvpp);
  return 0;
}
