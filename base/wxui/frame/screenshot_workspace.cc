#include <wxui.h>
FrameScreenShot::WorkSpace::WorkSpace(wxWindow *parent, wxWindowID id,
                                      const wxString &title, const wxPoint &pos,
                                      const wxSize &size, long style,
                                      const wxString &name)
    : IWorkSpace(parent, id, title, pos, size,
                 wxFRAME_SHAPED | wxNO_BORDER | wxFRAME_NO_TASKBAR, name) {
  //  SetBackgroundColour(wxColour(183, 110, 121));
  //			// Color color(20, 255, 215, 0);//!@ 土豪金
  SetBackgroundColour(wxColour(183, 110, 121));
  SetTransparent(50);
}
FrameScreenShot::WorkSpace::~WorkSpace() {
}
void FrameScreenShot::WorkSpace::OnWorkSpaceSizeChanged(const wxRect &rect) {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    IFrameComponent *frame_screenshot =
        app->FrameComponentGet(FrameComponentType::SCREENSHOT);
    if (!frame_screenshot)
      break;
    frame_screenshot->OnWorkspacePosUpdate(rect);
  } while (0);
}