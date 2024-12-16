#include <wxui.h>
FrameScreenShot::WorkSpace::WorkSpace(wxWindow *parent, wxWindowID id,
                                      const wxString &title, const wxPoint &pos,
                                      const wxSize &size, long style,
                                      const wxString &name)
    : IWorkSpace(parent, id, title, pos, size,
                 wxFRAME_SHAPED | wxNO_BORDER | wxFRAME_NO_TASKBAR, name) {
  //  SetBackgroundColour(wxColour(183, 110, 121));
  //			// Color color(20, 255, 215, 0);//!@ 土豪金
  is_allow_move_.store(true);
  // SetBackgroundColour(wxColour(183, 110, 121));
  SetTransparent(255);
}
FrameScreenShot::WorkSpace::~WorkSpace() {
}
void FrameScreenShot::WorkSpace::OnPaint(wxPaintEvent &evt) {
  do {
    if (!backgroundBitmap_)
      break;
    if (!backgroundBitmap_->IsOk()) {
      SK_DELETE_PTR(backgroundBitmap_);
      break;
    }
    wxPaintDC dc(dynamic_cast<wxWindow *>(this));

    dc.DrawBitmap(*backgroundBitmap_, 0, 0, true);
    wxPen pen(*wxRED, 3, wxPENSTYLE_SOLID);
    dc.SetPen(pen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(GetClientRect());

  } while (0);

  evt.Skip();
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
void FrameScreenShot::WorkSpace::SetImage(const wxImage *image) {
  do {
    if (!image)
      break;
    if (!image->IsOk())
      break;
    SetSize(image->GetSize());
    SK_DELETE_PTR(backgroundBitmap_);
    backgroundBitmap_ = new wxBitmap(*image);
  } while (0);
}
