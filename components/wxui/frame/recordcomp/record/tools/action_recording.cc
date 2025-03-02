#include <wxui.h>
using namespace record;

ActionRecording::ActionRecording(wxWindow *parent, wxWindowID id,
                                 const wxBitmapBundle &bitmap,
                                 const wxPoint &pos, const wxSize &size,
                                 long style, const wxValidator &validator,
                                 const wxString &name)
    : IActionTool(parent, id, bitmap, pos, size, style, validator, name) {
}
ActionRecording::~ActionRecording() {
  auto ss = 0;
}
void ActionRecording::OnClicked(wxCommandEvent &evt) {
  wxMessageBox(wxT("当前录屏功能暂时屏蔽!\n该版本主要是为了体验截屏等功能。"),
               wxT("提示"), wxOK | wxICON_INFORMATION);
  evt.Skip();
}
