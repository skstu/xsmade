#include "version.h"

// 不要包含 winver.h

static HMODULE hOriginal = NULL;

FARPROC GetOriginalProc(LPCSTR name) {
  if (!hOriginal) {
    char sysdir[MAX_PATH];
    GetSystemDirectoryA(sysdir, MAX_PATH);
    strcat_s(sysdir, "\\version.dll");
    hOriginal = LoadLibraryA(sysdir);
  }
  return GetProcAddress(hOriginal, name);
}

extern "C" {

// 1
__declspec(dllexport) BOOL WINAPI GetFileVersionInfoA(LPCSTR lptstrFilename,
                                                      DWORD dwHandle,
                                                      DWORD dwLen,
                                                      LPVOID lpData) {
  typedef BOOL(WINAPI * PFN)(LPCSTR, DWORD, DWORD, LPVOID);
  static PFN fn = (PFN)GetOriginalProc("GetFileVersionInfoA");
  return fn(lptstrFilename, dwHandle, dwLen, lpData);
}

// 2
__declspec(dllexport) BOOL WINAPI GetFileVersionInfoByHandle(HANDLE hFile,
                                                             DWORD dwHandle,
                                                             DWORD dwLen,
                                                             LPVOID lpData) {
  typedef BOOL(WINAPI * PFN)(HANDLE, DWORD, DWORD, LPVOID);
  static PFN fn = (PFN)GetOriginalProc("GetFileVersionInfoByHandle");
  return fn(hFile, dwHandle, dwLen, lpData);
}

// 3
__declspec(dllexport) BOOL WINAPI GetFileVersionInfoExA(DWORD dwFlags,
                                                        LPCSTR lpwstrFilename,
                                                        DWORD dwHandle,
                                                        DWORD dwLen,
                                                        LPVOID lpData) {
  typedef BOOL(WINAPI * PFN)(DWORD, LPCSTR, DWORD, DWORD, LPVOID);
  static PFN fn = (PFN)GetOriginalProc("GetFileVersionInfoExA");
  return fn(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

// 4
__declspec(dllexport) BOOL WINAPI GetFileVersionInfoExW(DWORD dwFlags,
                                                        LPCWSTR lpwstrFilename,
                                                        DWORD dwHandle,
                                                        DWORD dwLen,
                                                        LPVOID lpData) {
  typedef BOOL(WINAPI * PFN)(DWORD, LPCWSTR, DWORD, DWORD, LPVOID);
  static PFN fn = (PFN)GetOriginalProc("GetFileVersionInfoExW");
  return fn(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
}

// 5
__declspec(dllexport) DWORD WINAPI
GetFileVersionInfoSizeA(LPCSTR lptstrFilename, LPDWORD lpdwHandle) {
  typedef DWORD(WINAPI * PFN)(LPCSTR, LPDWORD);
  static PFN fn = (PFN)GetOriginalProc("GetFileVersionInfoSizeA");
  return fn(lptstrFilename, lpdwHandle);
}

// 6
__declspec(dllexport) DWORD WINAPI GetFileVersionInfoSizeExA(
    DWORD dwFlags, LPCSTR lpwstrFilename, LPDWORD lpdwHandle) {
  typedef DWORD(WINAPI * PFN)(DWORD, LPCSTR, LPDWORD);
  static PFN fn = (PFN)GetOriginalProc("GetFileVersionInfoSizeExA");
  return fn(dwFlags, lpwstrFilename, lpdwHandle);
}

// 7
__declspec(dllexport) DWORD WINAPI GetFileVersionInfoSizeExW(
    DWORD dwFlags, LPCWSTR lpwstrFilename, LPDWORD lpdwHandle) {
  typedef DWORD(WINAPI * PFN)(DWORD, LPCWSTR, LPDWORD);
  static PFN fn = (PFN)GetOriginalProc("GetFileVersionInfoSizeExW");
  return fn(dwFlags, lpwstrFilename, lpdwHandle);
}

// 8
__declspec(dllexport) DWORD WINAPI
GetFileVersionInfoSizeW(LPCWSTR lptstrFilename, LPDWORD lpdwHandle) {
  typedef DWORD(WINAPI * PFN)(LPCWSTR, LPDWORD);
  static PFN fn = (PFN)GetOriginalProc("GetFileVersionInfoSizeW");
  return fn(lptstrFilename, lpdwHandle);
}

// 9
__declspec(dllexport) BOOL WINAPI GetFileVersionInfoW(LPCWSTR lptstrFilename,
                                                      DWORD dwHandle,
                                                      DWORD dwLen,
                                                      LPVOID lpData) {
  typedef BOOL(WINAPI * PFN)(LPCWSTR, DWORD, DWORD, LPVOID);
  static PFN fn = (PFN)GetOriginalProc("GetFileVersionInfoW");
  //MessageBoxW(NULL, L"GetFileVersionInfoW called", L"Info", MB_OK);
  return fn(lptstrFilename, dwHandle, dwLen, lpData);
}

// 10
__declspec(dllexport) DWORD WINAPI VerFindFileA(
    DWORD uFlags, LPSTR szFileName, LPSTR szWinDir, LPSTR szAppDir,
    LPSTR szCurDir, PUINT lpuCurDirLen, LPSTR szDestDir, PUINT lpuDestDirLen) {
  typedef DWORD(WINAPI * PFN)(DWORD, LPSTR, LPSTR, LPSTR, LPSTR, PUINT, LPSTR,
                              PUINT);
  static PFN fn = (PFN)GetOriginalProc("VerFindFileA");
  return fn(uFlags, szFileName, szWinDir, szAppDir, szCurDir, lpuCurDirLen,
            szDestDir, lpuDestDirLen);
}

// 11
__declspec(dllexport) DWORD WINAPI
VerFindFileW(DWORD uFlags, LPWSTR szFileName, LPWSTR szWinDir, LPWSTR szAppDir,
             LPWSTR szCurDir, PUINT lpuCurDirLen, LPWSTR szDestDir,
             PUINT lpuDestDirLen) {
  typedef DWORD(WINAPI * PFN)(DWORD, LPWSTR, LPWSTR, LPWSTR, LPWSTR, PUINT,
                              LPWSTR, PUINT);
  static PFN fn = (PFN)GetOriginalProc("VerFindFileW");
  return fn(uFlags, szFileName, szWinDir, szAppDir, szCurDir, lpuCurDirLen,
            szDestDir, lpuDestDirLen);
}

// 12
__declspec(dllexport) DWORD WINAPI VerInstallFileA(
    DWORD uFlags, LPSTR szSrcFileName, LPSTR szDestFileName, LPSTR szSrcDir,
    LPSTR szDestDir, LPSTR szCurDir, LPSTR szTmpFile, PUINT lpuTmpFileLen) {
  typedef DWORD(WINAPI * PFN)(DWORD, LPSTR, LPSTR, LPSTR, LPSTR, LPSTR, LPSTR,
                              PUINT);
  static PFN fn = (PFN)GetOriginalProc("VerInstallFileA");
  return fn(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir,
            szCurDir, szTmpFile, lpuTmpFileLen);
}

// 13
__declspec(dllexport) DWORD WINAPI VerInstallFileW(
    DWORD uFlags, LPWSTR szSrcFileName, LPWSTR szDestFileName, LPWSTR szSrcDir,
    LPWSTR szDestDir, LPWSTR szCurDir, LPWSTR szTmpFile, PUINT lpuTmpFileLen) {
  typedef DWORD(WINAPI * PFN)(DWORD, LPWSTR, LPWSTR, LPWSTR, LPWSTR, LPWSTR,
                              LPWSTR, PUINT);
  static PFN fn = (PFN)GetOriginalProc("VerInstallFileW");
  return fn(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir,
            szCurDir, szTmpFile, lpuTmpFileLen);
}

// 16
__declspec(dllexport) BOOL WINAPI VerQueryValueA(LPCVOID pBlock,
                                                 LPCSTR lpSubBlock,
                                                 LPVOID *lplpBuffer,
                                                 PUINT puLen) {
  typedef BOOL(WINAPI * PFN)(LPCVOID, LPCSTR, LPVOID *, PUINT);
  static PFN fn = (PFN)GetOriginalProc("VerQueryValueA");
  return fn(pBlock, lpSubBlock, lplpBuffer, puLen);
}

// 17
__declspec(dllexport) BOOL WINAPI VerQueryValueW(LPCVOID pBlock,
                                                 LPCWSTR lpSubBlock,
                                                 LPVOID *lplpBuffer,
                                                 PUINT puLen) {
  typedef BOOL(WINAPI * PFN)(LPCVOID, LPCWSTR, LPVOID *, PUINT);
  static PFN fn = (PFN)GetOriginalProc("VerQueryValueW");
  return fn(pBlock, lpSubBlock, lplpBuffer, puLen);
}

} // extern "C"