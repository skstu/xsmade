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
#if 0
  wxQueueEvent(
      wxApp::GetInstance(),
      new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_ScreenShotFinalSuccess));
#endif
  // std::string screenshot_image_stream;
  // Global::ffxScreenShot(screenshot_region, screenshot_image_stream);
  wxCommandEvent notify(wxEVT_NotifyType,
                        NotifyEventID::EVT_NOTIFY_DRAWTOOL_SCREENSHOT);
  notify.SetInt(GetId());
  Global::SendEvent(notify);

  evt.Skip();
}
} // namespace screenshot
