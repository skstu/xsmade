#include <xs.h>
#include <stl.hpp>
#include <component.h>
int main(int argc, char **argv) {
  IComponent *testNswxskin = IComponent::Create(R"(libnswxskin.dll)");
  testNswxskin->Start();
  std::string input;
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input == "q" || std::cin.eof()) {
      testNswxskin->Stop();
      break;
    } else {
    }
  } while (1);

  IComponent::Destroy(&testNswxskin);
  return 0;
}
