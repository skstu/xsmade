#include <wxui.h>

namespace screenshot {
IDrawTool::IDrawTool(wxWindow *parent, wxWindowID id,
                     const wxBitmapBundle &bitmap, const wxPoint &pos,
                     const wxSize &size, long style,
                     const wxValidator &validator, const wxString &name)
    : wxBitmapButton(parent, id, bitmap, pos, size, style, validator, name) {
  SetToolTip(gpCommandToolTipMap[CommandTool(id)]);
  Bind(wxEVT_BUTTON, &IDrawTool::OnClicked, this, id);
}
IDrawTool::~IDrawTool() {
  Unbind(wxEVT_BUTTON, &IDrawTool::OnClicked, this, GetId());
}
void IDrawTool::OnClicked(wxCommandEvent &evt) {
  evt.Skip();
}
} // namespace screenshot
