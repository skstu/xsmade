#include <wxui.h>

FrameRecording::WorkSpace::WorkSpace(wxWindow *parent, wxWindowID id,
                                     const wxString &title, const wxPoint &pos,
                                     const wxSize &size, long style,
                                     const wxString &name)
    : IWorkSpace(parent, id, title, pos, size,
                 wxFRAME_SHAPED | wxNO_BORDER | wxFRAME_NO_TASKBAR, name) {
  is_allow_move_.store(true);
  is_allow_stretch_.store(true);
  //  SetBackgroundColour(wxColour(183, 110, 121));
  //			// Color color(20, 255, 215, 0);//!@ 土豪金
  SetBackgroundColour(wxColour(183, 110, 121));
  SetTransparent(50);
}
FrameRecording::WorkSpace::~WorkSpace() {
}
void FrameRecording::WorkSpace::OnWorkSpaceSizeChanged(const wxRect &rect) {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    IFrameComponent *frame_record =
        app->FrameComponentGet(FrameComponentType::RECORDING);
    if (!frame_record)
      break;
    frame_record->OnWorkspacePosUpdate(rect);
  } while (0);
}