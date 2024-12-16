#include <wxui.h>
using namespace record;

IActionTool::IActionTool(wxWindow *parent, wxWindowID id,
                         const wxBitmapBundle &bitmap, const wxPoint &pos,
                         const wxSize &size, long style,
                         const wxValidator &validator, const wxString &name)
    : wxBitmapButton(parent, id, bitmap, pos, size, style, validator, name) {
  SetToolTip(gpCommandToolTipMap[CommandTool(id)]);
  Bind(wxEVT_BUTTON, &IActionTool::OnClicked, this, id);
}
IActionTool::~IActionTool() {
  Unbind(wxEVT_BUTTON, &IActionTool::OnClicked, this, GetId());
}
void IActionTool::OnClicked(wxCommandEvent &evt) {
  evt.Skip();
}
