#include <wxui.h>

namespace screenshot {

wxBEGIN_EVENT_TABLE(IDrawTool, wxBitmapButton)
    EVT_COMMAND(wxID_ANY, wxEVT_NotifyType, IDrawTool::OnNotify)
        wxEND_EVENT_TABLE();

IDrawTool::IDrawTool(wxWindow *parent, wxWindowID id,
                     const wxBitmapBundle &bitmap, const wxPoint &pos,
                     const wxSize &size, long style,
                     const wxValidator &validator, const wxString &name)
    : wxBitmapButton(parent, id, bitmap, pos, size, style, validator, name) {
  SetToolTip(gpCommandToolTipMap[CommandTool(id)]);
  Bind(wxEVT_BUTTON, &IDrawTool::OnClicked, this, id);
  // Bind(wxEVT_NotifyType, &IDrawTool::OnNotify, this);
}
IDrawTool::~IDrawTool() {
  Unbind(wxEVT_BUTTON, &IDrawTool::OnClicked, this, GetId());
  // Unbind(wxEVT_NotifyType, &IDrawTool::OnNotify, this);
}
void IDrawTool::OnClicked(wxCommandEvent &evt) {
  evt.Skip();
}
void IDrawTool::OnNotify(wxCommandEvent &evt) {
  auto ss = 0;
}
} // namespace screenshot
