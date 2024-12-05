#include <system.h>
#include "sys.hpp"
#include <stl.hpp>
#include <fmt/format.h>
#include <base/uvpp/export.h>

int main(int argc, char **argv) {
  std::string module_path =
      System::GetCurrentProcessPath() + "/plugins/uvpp.dll";
  uvpp::IUvpp *pUvpp = uvpp::IUvpp::Create(module_path.c_str());
  uvpp::IConfig *pUvppConfig = pUvpp->ConfigGet();
  pUvppConfig->SetServiceType(
      static_cast<unsigned long>(uvpp::ServerType::INITIATOR) |
      static_cast<unsigned long>(uvpp::AddressType::IPC) |
      static_cast<unsigned long>(uvpp::SessionType::IPC));
  std::string addr(R"(\\.\pipe\test_uvpp_server)");
  pUvppConfig->Address(addr.data(), addr.size());
  uvpp::IService *pClient = pUvpp->CreateSevice();
  pUvppConfig->RegisterClientConnection([](const uvpp::ISession *session) {
    std::cout << "Client ready." << std::endl;
  });
  pClient->Start();
  std::string input;
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input == "q" || std::cin.eof()) {
      break;
    } else if (input.find("test") != std::string::npos) {
      pClient->Write((unsigned long)uvpp::CommandType::TESTMSG, "Hello!", 6);
    } else {
    }
  } while (1);
  uvpp::IUvpp::Destroy(&pUvpp);
  return 0;
}
