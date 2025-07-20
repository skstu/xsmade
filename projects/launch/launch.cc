#include <launch.h>

Launch::Launch(const std::string &args) : args_(args) {
  Init();
}
Launch::~Launch() {
  UnInit();
}
void Launch::Init() {
}
void Launch::UnInit() {
}
void Launch::Perform() {
  do {
#if 0
  std::string module_path =
      System::GetCurrentProcessPath() + "/components/libuvpp.dll";
  uvpp::IUvpp *pUvpp =
      dynamic_cast<uvpp::IUvpp *>(IComponent::Create(module_path.c_str()));
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
  pUvppConfig->RegisterServerSessionReadyCb([](const uvpp::ISession *session) {
    std::cout << fmt::format("session create '{}'", session->Address())
              << std::endl;
  });
  pUvppConfig->RegisterServerSessionDestroyCb(
      [](const uvpp::ISession *session) {
        std::cout << fmt::format("session destroy '{}'", session->Address())
                  << std::endl;
      });
  pUvppConfig->RegisterServerMessageCb([](const uvpp::ISession *session,
                                          const uvpp::CommandType &cmd,
                                          const uvpp::IBuffer *buffer) {
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
  IComponent::Destroy((IComponent **)&pUvpp);
#endif
  } while (0);
}
