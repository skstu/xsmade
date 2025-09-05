#include "config.h"
#ifdef __OSWIN__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR __cmdline__,
                     int cmdshow)
#elif defined(__OSLINUX__)
int main(int argc, char *args[])
#endif
{
  if (0 == xs_sys_process_already_exists(0))
    return 1;
  Config::CreateOrGet();
  std::string cmdLine(__cmdline__);
  std::string cmdlineTextPath =
      Config::CreateOrGet()->GetProjectRouteDir() + "/chromium_cmdline.txt";
  do {
    if (cmdLine.find("--user-data-dir") == std::string::npos)
      break;
    stl::File::WriteFile(cmdlineTextPath, cmdLine);
    const std::string proc = Config::CreateOrGet()->GetChromiumProcessPath();
    if (!stl::File::Exists(proc))
      break;
    xs_process_id_t pid = 0;
    std::vector<const char *> startup_args{nullptr};
    if (xs_sys_process_spawn(proc.c_str(), &startup_args[0], nullptr, 1, &pid))
      break;
    bool success = true;
  } while (0);
  Config::Destroy();
  return 0;
}
