#include "sys.h"

XS_EXTERN xs_errno_t xs_sys_get_commandline(char **out, size_t *out_size) {
  xs_errno_t r = xs_errno_t::XS_NO;
  do {
    auto pstrwCmdline = GetCommandLineW();
    if (!pstrwCmdline)
      break;
    std::string u8 = Conv::ws_to_u8(pstrwCmdline);
    *out_size = u8.size();
    *out = (char *)malloc(*out_size);
    memcpy(*out, u8.data(), *out_size);
    r = xs_errno_t::XS_OK;
  } while (0);
  return r;
}
xs_errno_t xs_sys_process_spawn(const char *proc, const char **args,
                                const char **envp, int show_flag,
                                xs_process_id_t *out_pid) {
  xs_errno_t r = xs_errno_t::XS_NO;
  do {
    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    if (!show_flag) {
      si.wShowWindow = show_flag == 0 ? SW_HIDE : SW_SHOW;
    }
    std::string cmdlines;
    if (args && (*args)) {
      size_t count = 0;
      while (args[count] != NULL) {
        cmdlines.append(args[count]).append(" ");
        count++;
      }
    }
    std::wstring proc_ws = Conv::u8_to_ws(proc);
    std::wstring cmdlines_ws = Conv::u8_to_ws(cmdlines);
    BOOL status = CreateProcessW(
        proc_ws.c_str(), // No module name (use command line)
        cmdlines.empty() ? NULL
                         : const_cast<wchar_t *>(
                               (L"/c " + cmdlines_ws).c_str()), // Command line
        NULL, // Process handle not inheritable
        NULL, // Thread handle not inheritable
        TRUE, // Set handle inheritance to FALSE
        NULL, // CREATE_NEW_CONSOLE, // No creation flags
        NULL, // Use parent's environment block
        NULL, // Use parent's starting directory
        &si,  // Pointer to STARTUPINFO structure
        &pi); // Pointer to PROCESS_INFORMATION structure
    if (FALSE == status)
      break;
    *out_pid = pi.dwProcessId;
    r = xs_errno_t::XS_OK;
  } while (0);
  return r;
}
XS_EXTERN xs_errno_t xs_sys_process_kill(xs_process_id_t pid, int /*signal*/) {
  xs_errno_t err = xs_errno_t::XS_NO;
  HANDLE hProcess = nullptr;
  do {
    if (pid <= 4)
      break;
    hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, static_cast<DWORD>(pid));
    if (!hProcess)
      break;
    if (::TerminateProcess(hProcess, 3762) != TRUE)
      break;
    err = xs_errno_t::XS_OK;
  } while (0);
  if (hProcess) {
    CloseHandle(hProcess);
    hProcess = nullptr;
  }
  return err;
}
XS_EXTERN int xs_sys_process_has_exit(xs_process_id_t pid) {
  int r = -1;
  HANDLE hProcess = nullptr;
  do {
    if (pid <= 0)
      break;
    hProcess = OpenProcess(SYNCHRONIZE, FALSE, pid);
    if (hProcess == nullptr) {
      r = 0;
      break;
    }
    DWORD rWait = WaitForSingleObject(hProcess, 0);
    r = ((rWait == WAIT_OBJECT_0) ? 0 : (int)rWait);
    /*switch (rWait) {
    case WAIT_OBJECT_0: {
      r = 0;
    } break;
    default:
      break;
    }*/
  } while (0);
  if (hProcess) {
    CloseHandle(hProcess);
    hProcess = nullptr;
  }
  return r;
}
XS_EXTERN xs_errno_t xs_sys_process_getpath(char **path, size_t *path_len) {
  xs_errno_t r = xs_errno_t::XS_NO;
  *path = NULL;
  *path_len = 0;
  do {
    std::wstring strPath;
    strPath.resize(PATH_MAX, 0x00);
    int len = GetModuleFileNameW(NULL, &strPath[0], strPath.size());
    if (len <= 0)
      break;
    strPath.resize(len);
    strPath = stl::Path::PathnameToPath(strPath);
    std::string u8 = Conv::ws_to_u8(strPath);
    *path_len = u8.size();
    *path = (char *)malloc(*path_len + 1);
    memcpy(*path, u8.data(), *path_len);
    (*path)[*path_len] = 0;
    r = xs_errno_t::XS_OK;
  } while (0);
  return r;
}
XS_EXTERN xs_errno_t xs_sys_process_getpid(xs_process_id_t *pid) {
  *pid = (xs_process_id_t)GetCurrentProcessId();
  return xs_errno_t::XS_OK;
}
XS_EXTERN int
xs_sys_process_already_exists(xs_process_id_t pid /*==0 ? current*/) {
  int r = -1;
  do {
    if (pid == 0)
      break;
    if (xs_sys_process_has_exit(pid) != 0) {
      r = 0;
    }
  } while (0);
  do {
    if (pid != 0)
      break;
    HANDLE hMutex = CreateMutexW(NULL, FALSE, L"LaunchProjectsMutex.Service");
    if (ERROR_ALREADY_EXISTS == GetLastError()) {
      r = 0;
      break;
    }
  } while (0);
  return r;
}