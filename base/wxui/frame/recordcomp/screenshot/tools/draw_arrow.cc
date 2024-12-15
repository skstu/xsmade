#include <wxui.h>
namespace screenshot {
DrawArrowTool::DrawArrowTool(wxWindow *parent, wxWindowID id,
                             const wxBitmapBundle &bitmap, const wxPoint &pos,
                             const wxSize &size, long style,
                             const wxValidator &validator, const wxString &name)
    : IDrawTool(parent, id, bitmap, pos, size, style, validator, name) {
}
DrawArrowTool::~DrawArrowTool() {
  auto ss = 0;
}
void DrawArrowTool::OnClicked(wxCommandEvent &evt) {
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
  parent->RefreshToolbar();
}
} // namespace screenshot