#include <wxui.h>
using namespace record;

ActionSystemClose::ActionSystemClose(wxWindow *parent, wxWindowID id,
                                     const wxBitmapBundle &bitmap,
                                     const wxPoint &pos, const wxSize &size,
                                     long style, const wxValidator &validator,
                                     const wxString &name)
    : IActionTool(parent, id, bitmap, pos, size, style, validator, name) {
}
ActionSystemClose::~ActionSystemClose() {
  auto ss = 0;
}
void ActionSystemClose::OnClicked(wxCommandEvent &evt) {
  int res = wxMessageBox(L"Are you sure you want to exit system?", L"Memade®",
                         wxYES_NO, this);
  if (res != wxYES) {
    // evt.Veto();
    return;
  } else {
    wxAppConsole *handle = wxApp::GetInstance();
    IFrameComponent *frame_component_recording =
        wxDynamicCast(handle, App)
            ->FrameComponentGet(FrameComponentType::RECORDING);
    frame_component_recording->Show(false);
    wxQueueEvent(handle,
                 new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_FrameDestroy));
  }
  evt.Skip();
}