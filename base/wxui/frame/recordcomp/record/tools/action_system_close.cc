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
  evt.Skip();
}