#include <wxui.h>

namespace screenshot {

IDrawTool::IDrawTool(wxWindow *parent, wxWindowID id,
                     const wxBitmapBundle &bitmap, const wxPoint &pos,
                     const wxSize &size, long style,
                     const wxValidator &validator, const wxString &name)
    : wxBitmapButton(parent, id, bitmap, pos, size, style, validator, name) {
  SetToolTip(gpCommandToolTipMap[CommandTool(id)]);
  Bind(wxEVT_BUTTON, &IDrawTool::OnClicked, this, id);
  Bind(wxEVT_NotifyType, &IDrawTool::OnActivate, this);
}
IDrawTool::~IDrawTool() {
  Unbind(wxEVT_BUTTON, &IDrawTool::OnClicked, this, GetId());
  Unbind(wxEVT_NotifyType, &IDrawTool::OnActivate, this);
}
bool IDrawTool::Activate() const {
  return pressed_.load();
}
void IDrawTool::OnActivate(wxCommandEvent &evt) {
  switch (NotifyEventID(evt.GetId())) {
  case NotifyEventID::EVT_NOTIFY_DRAWTOOL_ACTIVATE: {
    if (evt.GetInt() == GetId())
      break;
    pressed_.store(false);
  } break;
  default:
    break;
  }
}
void IDrawTool::OnClicked(wxCommandEvent &evt) {
  evt.Skip();
}

} // namespace screenshot
