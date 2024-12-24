#include <wxui.h>
namespace screenshot {
DrawNoTool::DrawNoTool(wxWindow *parent, wxWindowID id,
                       const wxBitmapBundle &bitmap, const wxPoint &pos,
                       const wxSize &size, long style,
                       const wxValidator &validator, const wxString &name)
    : IDrawTool(parent, id, bitmap, pos, size, style, validator, name) {
  SetToolTip(gpCommandToolTipMap[CommandTool(id)]);
}
DrawNoTool::~DrawNoTool() {
}
void DrawNoTool::OnClicked(wxCommandEvent &evt) {
  evt.Skip();
  IToolbar *parent = dynamic_cast<IToolbar *>(GetParent()->GetParent());
  if (!parent)
    return;
  wxBoxSizer *sizer = nullptr;
  wxPanel *panel = nullptr;
  parent->GetExpandToolbar(&panel, &sizer);
  if (!sizer || !panel)
    return;
  sizer->Clear(true);
  pressed_.store(false);

  parent->RefreshToolbar();

  wxCommandEvent notify(wxEVT_NotifyType,
                        NotifyEventID::EVT_NOTIFY_DRAWTOOL_ACTIVATE);
  notify.SetInt(GetId());
  Global::SendEvent(notify);
}
} // namespace screenshot
