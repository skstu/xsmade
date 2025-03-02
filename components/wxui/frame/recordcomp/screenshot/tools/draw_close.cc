#include <wxui.h>
namespace screenshot {
DrawCloseTool::DrawCloseTool(wxWindow *parent, wxWindowID id,
                             const wxBitmapBundle &bitmap, const wxPoint &pos,
                             const wxSize &size, long style,
                             const wxValidator &validator, const wxString &name)
    : IDrawTool(parent, id, bitmap, pos, size, style, validator, name) {
  SetToolTip(gpCommandToolTipMap[CommandTool(id)]);
}
DrawCloseTool::~DrawCloseTool() {
}
void DrawCloseTool::OnClicked(wxCommandEvent &evt) {
  wxQueueEvent(wxApp::GetInstance(),
               new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_ScreenShotClose));
  evt.Skip();
}
} // namespace screenshot
