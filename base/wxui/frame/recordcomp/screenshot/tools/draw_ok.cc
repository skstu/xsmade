#include <wxui.h>
namespace screenshot {
DrawOkTool::DrawOkTool(wxWindow *parent, wxWindowID id,
                       const wxBitmapBundle &bitmap, const wxPoint &pos,
                       const wxSize &size, long style,
                       const wxValidator &validator, const wxString &name)
    : IDrawTool(parent, id, bitmap, pos, size, style, validator, name) {
  SetToolTip(gpCommandToolTipMap[CommandTool(id)]);
}
DrawOkTool::~DrawOkTool() {
}
void DrawOkTool::OnClicked(wxCommandEvent &evt) {
  evt.Skip();
}
} // namespace screenshot
