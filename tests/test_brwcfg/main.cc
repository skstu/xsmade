#include <xs.h>
#include <system.hpp>
#include <dlfcn.h>
#include <rapidjson.h>
#include <projects/browser/configure.hpp>
#include <projects/browser/ibrwsvr.h>
#include <projects/browser/ibrwcfg.h>
#include <projects/browser/protocol.hpp>

int main(int argc, char **argv) {
  const std::string current_dir = System::GetCurrentProcessPath();
#if defined(__OSWIN__)
  browser::IBrwcfg *pBrwcfg = browser::IBrwcfg::Create(
      (current_dir + "/../components/libbrwcfg.dll").c_str());
#elif defined(__OSLINUX__)
  brwcfg::IBrwcfg *pBrwcfg = brwcfg::IBrwcfg::Create(
      (current_dir + "/../components/libbrwcfg.so").c_str());
#endif
  // xs_process_id_t pid = 0;
  // xs_sys_process_getpid(&pid);
  char *path = nullptr;
  size_t path_size = 0;
  xs_sys_get_cache_path(&path, &path_size);
  if (pBrwcfg)
    pBrwcfg->Start();

  stl::MainProc([](const std::string &input, bool &exit) {
    if (input == "q") {
      exit = true;
    } else {
    }
  });
  if (pBrwcfg) {
    pBrwcfg->Stop();
    pBrwcfg->OnBrowserClosing();
  }
  return 0;
}
