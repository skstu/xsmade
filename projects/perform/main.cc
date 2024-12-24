#include "perform.h"
// launchctl submit -l com.example.hidden_app -- /path/to/hidden_app
#ifdef __OSWIN__
bool ProcessCreateA(const std::string &exePathname,
                    const std::string &startParamenters, DWORD &outPID,
                    const bool &Inheriting_parent_process = false,
                    const bool &isShow = false,
                    const DWORD &wait_time = 10000) {
  bool result = false;
  do {
    STARTUPINFOA si = {0};
    si.cb = sizeof(si);
    if (!isShow) {
      si.dwXSize = 1;
      si.dwYSize = 1;
      si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESIZE;
    } else
      si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = isShow ? SW_SHOW : SW_HIDE;
    PROCESS_INFORMATION pi = {0};
    if (0 == ::CreateProcessA(
                 exePathname.empty()
                     ? NULL
                     : exePathname.c_str(), // No module name (use command line)
                 startParamenters.empty()
                     ? NULL
                     : const_cast<char *>(
                           ("/c " + startParamenters).c_str()), // Command line
                 NULL, // Process handle not inheritable
                 NULL, // Thread handle not inheritable
                 Inheriting_parent_process
                     ? TRUE
                     : FALSE, // Set handle inheritance to FALSE
                 !Inheriting_parent_process ? CREATE_NEW_CONSOLE
                                            : NULL, // No creation flags
                 NULL, // Use parent's environment block
                 NULL, // Use parent's starting directory
                 &si,  // Pointer to STARTUPINFO structure
                 &pi)  // Pointer to PROCESS_INFORMATION structure
    )
      break;
    result = (outPID = pi.dwProcessId) != 0;
    ::WaitForSingleObject(pi.hProcess, result ? wait_time : 0);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
  } while (0);
  return result;
}
bool EnableDebugPrivilege(const bool &bEnable = true) {
  bool result = false;
  HANDLE hToken = nullptr;
  do {
    LUID luid = {0};
    if (!::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES,
                            &hToken))
      break;
    if (!::LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
      break;
    TOKEN_PRIVILEGES tokenPriv;
    tokenPriv.PrivilegeCount = 1;
    tokenPriv.Privileges[0].Luid = luid;
    tokenPriv.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;
    if (0 == ::AdjustTokenPrivileges(hToken, FALSE, &tokenPriv,
                                     sizeof(TOKEN_PRIVILEGES), nullptr,
                                     nullptr))
      break;
    result = ::GetLastError() == ERROR_SUCCESS;
  } while (0);
  CloseHandle(hToken);
  return result;
}
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline,
                     int cmdshow) {
  EnableDebugPrivilege();
  std::string cmdline_ = cmdline ? cmdline : "";
#else
int main(int argc, char **argv) {
  std::string cmdline_ = stl::CmdLine::PackageCommandLine(argc, argv);
#endif
#if 0
  std::vector<std::string> brw_startup_args_;
  brw_startup_args_.emplace_back("--no-first-run");
  brw_startup_args_.emplace_back("--disable-sync");
  brw_startup_args_.emplace_back("--disable-gaia-services");
  brw_startup_args_.emplace_back("--disable-account-consistency");
  brw_startup_args_.emplace_back(
      "--disable-features=ChromeSignin,AccountConsistency");
  brw_startup_args_.emplace_back("--disable-background-mode");
  brw_startup_args_.emplace_back("--no-default-browser-check");
  // brw_startup_args_.emplace_back(R"(--user-data-dir=C:\Users\k34ub\AppData\Roaming\MarsProjects\userdata\525c36a14d4da77712db610af924c390)");

  std::vector<const char *> startup_args;
  for (const auto &node : brw_startup_args_)
    startup_args.emplace_back(node.c_str());
  startup_args.emplace_back(nullptr);

  char *path = nullptr;
  size_t path_size = 0;
  xs_sys_get_appdata_path(&path, &path_size);

  MessageBoxA(NULL, path, NULL, MB_TOPMOST);
  
  const char *chrome_path =
      R"(C:\Users\k34ub\AppData\Roaming\MarsProjects\chromium\130.0.6723.59\chrome.exe)";
  DWORD pid = 0;
  xs_process_id_t pid_ = 0;
  // ProcessCreateA(chrome_path, "", pid, true, true);
  int status = xs_sys_process_spawn(chrome_path, &startup_args[0], 1, &pid_);
#endif
  PerformCmdLine::Create(cmdline_);
  auto pTools = Components::Get();
  Perform::Get()->Run();
  Perform::Destroy();
  Components::Destroy();
  PerformCmdLine::Destroy();
  return 0;
}
