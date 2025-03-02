#include <xs.h>
#include <system.hpp>
#include <fmt/format.h>
#include <components/wxui/export.h>

int main(int argc, char **argv) {
#if defined(__OSWIN__)
  wxui::IWxui *pWxui = wxui::IWxui::Create(
      (System::GetCurrentProcessPath() + "/wxui.dll").c_str());
#if DEBUG
  pWxui->ConfigGet()->SetResourceDir(
      R"(C:\Users\k34ub\AppData\Local\MarsProjects\resources\ffxui)");
#else
  pWxui->ConfigGet()->SetResourceDir(
      (System::GetCurrentProcessPath() + R"(\resources\ffxui\)").c_str());
#endif
  pWxui->ConfigGet()->SetFrameType(wxui::FrameType::SHAPEFRAME);
  pWxui->Start();
#elif defined(__OSMAC__)
  wxui::IWxui *pWxui = wxui::IWxui::Create(
      (System::GetCurrentProcessPath() + "/plugins/wxui.dylib").c_str());
#endif

  std::string input;
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input == "q" || std::cin.eof()) {
      pWxui->Stop();
      break;
    } else if (input.find("test") != std::string::npos) {
      std::vector<std::string> parser =
          stl::String::StringSpilt(input.data() + strlen("test "), " ");
      for (const auto &i : parser)
        std::cout << i << std::endl;
      auto frame = pWxui->GetFrame();
      frame->SetRegion(atoi(parser[0].c_str()), atoi(parser[1].c_str()),
                       atoi(parser[2].c_str()), atoi(parser[3].c_str()));
    }
  } while (1);
  wxui::IWxui::Destroy(&pWxui);
  return 0;
}