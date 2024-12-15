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

} // namespace screenshot
