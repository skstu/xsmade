#if defined(_WIN32) || defined(_WIN64)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#ifdef __cplusplus
extern "C" {
#endif

#define NSISAPI __declspec(dllexport) void __cdecl

// NSISAPI wxui(HWND hwndParent, int string_size, char *variables,
//              stack_t **stacktop, extra_parameters *extra) {
//   // EXDLL_INIT();
//   MessageBox(hwndParent, "Hello World!", "Hello", MB_OK);
// }
NSISAPI NSIS_CreateUI(void) {
}
NSISAPI NSIS_ShowUI(void) {
}
NSISAPI NSIS_DestroyUI(void) {
}
#ifdef __cplusplus
}
#endif
#endif // _WIN32 || _WIN64