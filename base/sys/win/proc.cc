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
XS_EXTERN xs_errno_t xs_sys_process_spawn(const char *proc, const char **args,
                                const char **envp, int show_flag,
                                xs_process_id_t *out_pid) {
  xs_errno_t r = xs_errno_t::XS_NO;
  do {
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = (show_flag == 0) ? SW_HIDE : SW_SHOW;

    if (!proc)
      break;

    // Build command line: quoted executable path + arguments
    std::wstring proc_ws = Conv::u8_to_ws(proc);
    std::wstring full_cmd = L"\"";
    full_cmd.append(proc_ws);
    full_cmd.append(L"\"");

    if (args && (*args)) {
      size_t i = 0;
      while (args[i] != NULL) {
        full_cmd.append(L" ");
        full_cmd.append(Conv::u8_to_ws(args[i]));
        ++i;
      }
    }

    // CreateProcess requires a writable buffer for lpCommandLine
    std::vector<wchar_t> cmd_buf(full_cmd.begin(), full_cmd.end());
    cmd_buf.push_back(L'\0');

    BOOL inherit_handles = FALSE;
    DWORD creation_flags = 0;
    if (show_flag == 0) {
      creation_flags |= CREATE_NO_WINDOW;
    }

    // Use NULL lpApplicationName and pass full command line (writable)
    BOOL status = CreateProcessW(
        NULL,                   // lpApplicationName
        cmd_buf.data(),         // lpCommandLine (writable)
        NULL,                   // lpProcessAttributes
        NULL,                   // lpThreadAttributes
        inherit_handles,        // bInheritHandles
        creation_flags,         // dwCreationFlags
        NULL,                   // lpEnvironment
        NULL,                   // lpCurrentDirectory
        &si,                    // lpStartupInfo
        &pi);                   // lpProcessInformation

    if (status == FALSE) {
      // optional: DWORD err = GetLastError();
      break;
    }

    if (out_pid)
      *out_pid = static_cast<xs_process_id_t>(pi.dwProcessId);

    // Close returned handles to avoid leaks; process continues running.
    if (pi.hThread) {
      CloseHandle(pi.hThread);
      pi.hThread = NULL;
    }
    if (pi.hProcess) {
      CloseHandle(pi.hProcess);
      pi.hProcess = NULL;
    }

    r = xs_errno_t::XS_OK;
  } while (0);
  return r;
}
XS_EXTERN xs_errno_t xs_sys_process_kill_name(const char *name,
                                              xs_process_id_t *out_pid) {
  xs_errno_t err = xs_errno_t::XS_NO;
  *out_pid = 0;
  do {
    if (!name)
      break;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE)
      break;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    BOOL found = FALSE;
    if (Process32First(hSnap, &pe)) {
      do {
        std::string exe_name = Conv::ws_to_u8(pe.szExeFile);
        if (stl::String::Lower(exe_name) == stl::String::Lower(name)) {
          HANDLE hProc =
              OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
          if (hProc) {
            if (TerminateProcess(hProc, 3762)) {
              *out_pid = pe.th32ProcessID;
              err = xs_errno_t::XS_OK;
              CloseHandle(hProc);
              found = TRUE;
              break;
            }
            CloseHandle(hProc);
          }
        }
      } while (Process32Next(hSnap, &pe));
    }
    CloseHandle(hSnap);
  } while (0);
  return err;
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