#include <wxui.h>
using namespace record;

ActionBoxSelection::ActionBoxSelection(wxWindow *parent, wxWindowID id,
                                       const wxBitmapBundle &bitmap,
                                       const wxPoint &pos, const wxSize &size,
                                       long style, const wxValidator &validator,
                                       const wxString &name)
    : IActionTool(parent, id, bitmap, pos, size, style, validator, name) {
}
ActionBoxSelection::~ActionBoxSelection() {
  auto ss = 0;
}
void ActionBoxSelection::OnClicked(wxCommandEvent &evt) {
  // wxQueueEvent(
  //     wxApp::GetInstance(),
  //     new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_RecordingBoxSelection));
  //MessageBoxW(NULL, L"333", NULL, 0);
  evt.Skip();
}
