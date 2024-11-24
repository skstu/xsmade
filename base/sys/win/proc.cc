#include "sys.h"

XS_EXTERN int xs_sys_process_spawn(const char *proc, const char **args,
                                   int show_flag, xs_process_id_t *out_pid) {
  int r = -1;
  do {
    STARTUPINFOA si = {0};
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
    
    BOOL status = CreateProcessA(
        proc, // No module name (use command line)
        cmdlines.empty()
            ? NULL
            : const_cast<char *>(("/c " + cmdlines).c_str()), // Command line
        NULL,               // Process handle not inheritable
        NULL,               // Thread handle not inheritable
        FALSE,              // Set handle inheritance to FALSE
        CREATE_NEW_CONSOLE, // No creation flags
        NULL,               // Use parent's environment block
        NULL,               // Use parent's starting directory
        &si,                // Pointer to STARTUPINFO structure
        &pi);               // Pointer to PROCESS_INFORMATION structure
    if (FALSE == status)
      break;
    *out_pid = pi.dwProcessId;
    r = 0;
  } while (0);
  return r;
}
XS_EXTERN int xs_sys_process_kill(xs_process_id_t pid) {
  int r = 0;
  HANDLE hProcess = nullptr;
  do {
    if (pid <= 4)
      break;
    hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, static_cast<DWORD>(pid));
    if (!hProcess)
      break;
    if (::TerminateProcess(hProcess, 3762) != TRUE)
      break;
    r = 0;
  } while (0);
  if (hProcess) {
    CloseHandle(hProcess);
    hProcess = nullptr;
  }
  return r;
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
XS_EXTERN int xs_sys_process_getpath(char **path, size_t *path_len) {
  int r = -1;
  *path = NULL;
  *path_len = 0;
  do {
    std::string strPath;
    strPath.resize(PATH_MAX, 0x00);
    *path_len = GetModuleFileNameA(NULL, &strPath[0], strPath.size());
    if (*path_len <= 0)
      break;
    *path_len += 1;
    strPath.resize(*path_len, 0x00);
    *path = (char *)malloc(*path_len);
    memcpy(*path, strPath.data(), *path_len);
    r = 0;
  } while (0);
  return r;
}
XS_EXTERN int xs_sys_process_getpid(xs_process_id_t *pid) {
  *pid = (xs_process_id_t)GetCurrentProcessId();
  return 0;
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
    HANDLE hMutex = CreateMutexA(NULL, FALSE, "LaunchProjectsMutex.Service");
    if (ERROR_ALREADY_EXISTS == GetLastError()) {
      r = 0;
      break;
    }
  } while (0);
  return r;
}