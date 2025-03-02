#include "wxui.h"
extra_parameters *nsis_extra_parameters = nullptr;
#ifdef __cplusplus
extern "C" {
#endif
#define NSISAPI __declspec(dllexport) void __cdecl

NSISAPI StartInstall(HWND hwndParent, int string_size, TCHAR *variables,
                     stack_t **stacktop, extra_parameters *extra) {
  Global::Get()->SetExtra(extra);
  EXDLL_INIT();

  auto wxui = Wxui::Create();
  wxui->Start();
  Global::Get()->SignalGet()->wait_for_event(std::chrono::milliseconds(0));
}

NSISAPI StartUninstall(HWND hwndParent, int string_size, TCHAR *variables,
                       stack_t **stacktop, extra_parameters *extra) {
  Global::Get()->SetExtra(extra);
  EXDLL_INIT();
  auto wxui = Wxui::Create();
  wxui->Start();
}
#ifdef __cplusplus
}
#endif

// MessageBoxW(NULL, L"InitInstallPage", NULL, MB_TOPMOST);
// MessageBoxW(NULL, L"InitInstallPage", NULL, MB_TOPMOST);