#include <xs.h>
#include <stl.hpp>
#include <interface.hpp>
#include <system.hpp>
#include <projects/chromium/libsettings/export.h>
#include <projects/chromium/include/yunlogin/yunlogin_config.hpp>

int main(int argc, char **argv) {

  const std::string current_dir = System::GetCurrentProcessPath();

  chromium::yunlogin::IConfigure ylcfg("");
  std::string ylcfgBuffer;
  ylcfg >> ylcfgBuffer;

  stl::File::WriteFile(current_dir + "/ylcfg.json", ylcfgBuffer);

  std::string libPathname = current_dir + "/components/libsettings";
  IXSiumioSettings *pSettings = nullptr;

  typedef void *(*tf_interface_init)(void *, unsigned long);
  typedef void (*tf_interface_uninit)(void);
  tf_interface_init interface_init = nullptr;
  tf_interface_uninit interface_uninit = nullptr;
  void *handle_ = nullptr;
  do {
    handle_ = dlopen(libPathname.c_str(), /*RTLD_NOW*/ RTLD_LAZY);
    if (!handle_) {
      char *err = dlerror();
      std::cout << err << std::endl;
      break;
    }
    interface_init =
        decltype(interface_init)(dlsym(handle_, name_interface_init));
    interface_uninit =
        decltype(interface_uninit)(dlsym(handle_, name_interface_uninit));
    if (!interface_init || !interface_uninit)
      break;
    std::string xmlData =
        stl::File::ReadFile(current_dir + "/settings/settings.xml");
    if (xmlData.empty())
      break;
    interface_init((void *)xmlData.c_str(),
                   static_cast<unsigned long>(xmlData.size()));
    stl::MainProc([](const std::string &input, bool &exit) {
      if (input == "q") {
        exit = true;
      } else {
      }
    });
  } while (0);
  return 0;
}
