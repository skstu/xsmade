#include <wxui.h>
FrameRecording::Background::Background(wxWindow *parent, wxWindowID id,
                                       const wxString &title,
                                       const wxPoint &pos, const wxSize &size,
                                       long style, const wxString &name)
    : IBackground(parent, id, title, pos, size,
                  wxFRAME_SHAPED | wxNO_BORDER | wxFRAME_NO_TASKBAR, name) {
  wxDisplay display;
  wxRect workArea = display.GetGeometry();
  SetSize(0, 0, workArea.GetWidth(), workArea.GetHeight());
  SetBackgroundColour(wxColour(183, 110, 121));
  SetTransparent(50);
#if defined(__OSWIN__)
  SetWindowPos(GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#endif
}
FrameRecording::Background::~Background() {
}
