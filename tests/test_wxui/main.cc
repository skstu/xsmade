#include <system.h>
#include "sys.hpp"
#include <stl.hpp>
#include <fmt/format.h>
#include <base/wxui/export.h>

int main(int argc, char **argv) {
  wxui::IWxui *pWxui = wxui::IWxui::Create(
      (System::GetCurrentProcessPath() + "/plugins/wxui.dll").c_str());
  pWxui->ConfigGet()->SetResourceDir(
      R"(C:\Users\k34ub\AppData\Roaming\MarsProjects\resources\ffxui)");
  pWxui->ConfigGet()->SetFrameType(wxui::FrameType::SHAPEFRAME);
  pWxui->Start();

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
