#include <wxui.h>
namespace screenshot {
DrawTextTool::DrawTextTool(wxWindow *parent, wxWindowID id,
                           const wxBitmapBundle &bitmap, const wxPoint &pos,
                           const wxSize &size, long style,
                           const wxValidator &validator, const wxString &name)
    : IDrawTool(parent, id, bitmap, pos, size, style, validator, name) {
  SetToolTip(gpCommandToolTipMap[CommandTool(id)]);
}
DrawTextTool::~DrawTextTool() {
}

} // namespace screenshot
