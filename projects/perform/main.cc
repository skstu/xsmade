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

template <typename T> static T getRandomValue(const T &a, const T &b) {
  static std::random_device rd;  // 随机设备（硬件随机数生成器）
  static std::mt19937 gen(rd()); // 使用随机设备初始化 Mersenne Twister 引擎

  std::uniform_real_distribution<> dis_a_b(static_cast<double>(a),
                                           static_cast<double>(b));

  // 如果类型是浮点类型
  if constexpr (std::is_floating_point<T>::value) {
    return static_cast<T>(dis_a_b(gen));
  }
  // 如果类型是整数类型
  else if constexpr (std::is_integral<T>::value) {
    std::uniform_int_distribution<T> dis(static_cast<T>(a), static_cast<T>(b));
    return dis(gen);
  }

  return T();
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
  int int_val = getRandomValue(-10, 0); // 返回一个在 1 和 10 之间的整数
  double double_val =
      getRandomValue(0-1.5, 0.0); // 返回一个在 0.5 和 1.5 之间的浮动值

  PerformCmdLine::Create(cmdline_);
  auto pTools = local::Components::Get();
  Perform::Get()->Run();
  Perform::Destroy();
  local::Components::Destroy();
  PerformCmdLine::Destroy();

  return 0;
}
