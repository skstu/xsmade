#include <xs.h>
#include <system.hpp>
#include <fmt/format.h>
#include <projects/engine/jsonnet/export.h>

int main(int argc, char **argv) {
  engine::IJsonnet *pJosnnet = engine::IJsonnet::Create(
      (System::GetCurrentProcessPath() + "/engine/jsonnet.dll").c_str());

  
  std::string input;
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input == "q" || std::cin.eof()) {
      break;
    }
  } while (1);
  engine::IJsonnet::Destroy(&pJosnnet);
  return 0;
}
