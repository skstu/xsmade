#include <wxui.h>
using namespace record;

ActionScreenshot::ActionScreenshot(wxWindow *parent, wxWindowID id,
                                   const wxBitmapBundle &bitmap,
                                   const wxPoint &pos, const wxSize &size,
                                   long style, const wxValidator &validator,
                                   const wxString &name)
    : IActionTool(parent, id, bitmap, pos, size, style, validator, name) {
}
ActionScreenshot::~ActionScreenshot() {
  auto ss = 0;
}
void ActionScreenshot::OnClicked(wxCommandEvent &evt) {
  wxQueueEvent(
      wxApp::GetInstance(),
      new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_ScreenShotFinished));
  evt.Skip();
}