#include "config.h"
#ifdef __OSWIN__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
// int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR __cmdline__,
//                      int cmdshow)
int main(int argc, char *args[])
#elif defined(__OSLINUX__)
int main(int argc, char *args[])
#endif
{
  if (0 == xs_sys_process_already_exists(0))
    return 1;
  char *__cmdline__ = nullptr;
  size_t __cmdline_size__ = 0;
  xs_sys_get_commandline(&__cmdline__, &__cmdline_size__);
  if (!__cmdline__)
    return 0;
  stl::tfCommandLines cmdline = stl::CmdLine::ParserCommandLines(
      std::string(__cmdline__, __cmdline_size__), false);
  xs_sys_free((void **)&__cmdline__);

  auto f_mode = cmdline.find("--mode");
  Config::CreateOrGet();
  if (f_mode == cmdline.end()) {
    Startup::GetOrCreate()->Run();
  } else if (f_mode->second == "release") {
    Startup::GetOrCreate(RunMode::kReleaseModel)->Run();
  }
  Config::Destroy();
  return 0;
}
