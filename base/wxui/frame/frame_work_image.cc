#include "wxui.h"
wxBEGIN_EVENT_TABLE(FrameWorkImage, wxFrame) EVT_SIZE(FrameWorkImage::OnSize)
    EVT_CLOSE(FrameWorkImage::OnClose) EVT_PAINT(FrameWorkImage::OnPaint)
        wxEND_EVENT_TABLE();

FrameWorkImage::FrameWorkImage(wxWindow *parent, wxWindowID id,
                               const wxString &title, const wxPoint &pos,
                               const wxSize &size, long style,
                               const wxString &name)
    : FrameBase(parent, id, title, pos, size, wxNO_BORDER | wxFRAME_NO_TASKBAR,
                name) {
}
FrameWorkImage::~FrameWorkImage() {
}
bool FrameWorkImage::SetBackgroundBitmap(const std::string &imgPath) {
  bool result = false;
  SK_DELETE_PTR(backgroundBitmap_);
  do {
    if (!stl::File::Exists(imgPath))
      break;
    wxImage *img = nullptr;
    wxComm::LoadImg(imgPath, &img);
    if (!img)
      break;
    if (!img->IsOk())
      break;
    backgroundBitmap_ = new wxBitmap(*img);
    result = true;
  } while (0);
  return result;
}
void FrameWorkImage::OnSize(wxSizeEvent &event) {
  event.Skip();
}
void FrameWorkImage::OnClose(wxCloseEvent &event) {
  event.Skip();
}
void FrameWorkImage::OnPaint(wxPaintEvent &event) {
  do {
    if (!backgroundBitmap_)
      break;
    if (!backgroundBitmap_->IsOk()) {
      SK_DELETE_PTR(backgroundBitmap_);
      break;
    }
    wxPaintDC dc(this);
    dc.DrawBitmap(*backgroundBitmap_, 0, 0, true);
  } while (0);

  event.Skip();
}
