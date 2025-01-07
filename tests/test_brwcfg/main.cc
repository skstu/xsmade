#include <xs.h>
#include <system.hpp>
#include <fmt/format.h>
#include <projects/browser/brwcfg/export.h>

int main(int argc, char **argv) {
#if defined(__OSWIN__)
  browser::IBrwcfg *pBrwcfg = browser::IBrwcfg::Create(
      (System::GetCurrentProcessPath() + "/plugins/brwcfg.dll").c_str());
#elif defined(__OSMAC__)
#endif
  pBrwcfg->OnMainProcessStartup();
  std::string input;
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input == "q" || std::cin.eof()) {
      pBrwcfg->OnMainProcessShutdown(0);
      break;
    }
  } while (1);
  browser::IBrwcfg::Destroy(&pBrwcfg);
  return 0;
}
