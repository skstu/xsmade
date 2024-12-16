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
  evt.Skip();
}
