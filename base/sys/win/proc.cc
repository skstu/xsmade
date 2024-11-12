#include "sys.h"

XS_EXTERN int xs_sys_process_spawn(const char *proc, const char **args,
                                   long long *out_pid) {
  int r = -1;
  do {
    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

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
XS_EXTERN int xs_sys_process_kill(long long pid) {
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
XS_EXTERN int xs_sys_process_has_exit(long long pid) {
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
    DWORD r = WaitForSingleObject(hProcess, 0);
    switch (r) {
    case WAIT_OBJECT_0: {
      r = 0;
    } break;
    default: {
      r = 1;
    } break;
    }
  } while (0);
  if (hProcess) {
    CloseHandle(hProcess);
    hProcess = nullptr;
  }
  return r;
}