#include "wxui.h"
wxBEGIN_EVENT_TABLE(FrameWork, wxFrame) EVT_SIZE(FrameWork::OnSize)
    EVT_CLOSE(FrameWork::OnClose) EVT_PAINT(FrameWork::OnPaint)
        wxEND_EVENT_TABLE();

FrameWork::FrameWork(wxWindow *parent, wxWindowID id, const wxString &title,
                     const wxPoint &pos, const wxSize &size, long style,
                     const wxString &name)
    : FrameBase(parent, id, title, pos, size,
                wxFRAME_SHAPED | wxNO_BORDER | wxFRAME_NO_TASKBAR, name) {
  //  SetBackgroundColour(wxColour(183, 110, 121));
  //			// Color color(20, 255, 215, 0);//!@ 土豪金
  SetBackgroundColour(wxColour(183, 110, 121));
  SetTransparent(50);
#if 0
  wxDisplay display;
  wxRect workArea = display.GetGeometry();
  SetSize(0, 0, workArea.GetWidth(), workArea.GetHeight());
#if defined(__OSWIN__)
  SetWindowPos(GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#endif
#endif
}
FrameWork::~FrameWork() {
}
void FrameWork::OnSize(wxSizeEvent &event) {
  Refresh();
  event.Skip();
}
void FrameWork::OnClose(wxCloseEvent &event) {
  event.Skip();
}
#if 0
void FrameWork::OnPaint(wxPaintEvent &event) {
  wxPaintDC dc(this);

  wxPen redPen(wxColour(255, 0, 0), 5);
  dc.SetPen(redPen);

  dc.SetBrush(wxBrush(wxColour(0, 0, 0), wxTRANSPARENT));

  SetShape(wxRegion(0, 0, GetSize().x, GetSize().y));

  event.Skip();
}
#endif

void FrameWork::OnPaint(wxPaintEvent &event) {
  wxPaintDC dc(this);
  wxPen redPen(wxColour(255, 215, 0), 2);
  dc.SetPen(redPen);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  wxSize size = GetSize();
  dc.DrawRectangle(2, 2, size.x - 2, size.y - 2);
  dc.DrawLine(2, 2, 2, size.y - 2);
  dc.DrawLine(size.x - 2, 2, size.x - 2, size.y - 2);
  dc.DrawLine(2, size.y - 2, size.x - 2, size.y - 2);
  event.Skip();
}

#if 0
  if (drawing_.load() || startPoint_ != endPoint_) {
    wxRect rect(startPoint_.x, startPoint_.y, endPoint_.x - startPoint_.x,
                endPoint_.y - startPoint_.y);
    dc.DrawRectangle(rect);

    wxRegion region(0, 0, GetSize().x, GetSize().y);
    wxRect cutout(startPoint_.x, startPoint_.y, endPoint_.x - startPoint_.x,
                  endPoint_.y - startPoint_.y);
    region.Subtract(cutout);
    SetShape(region);
  } else {
    SetShape(wxRegion(0, 0, GetSize().x, GetSize().y));
  }
#endif
#if 0
  wxRegion region(0, 0, GetSize().x, GetSize().y);
  wxRect cutout(startPoint_.x, startPoint_.y, endPoint_.x - startPoint_.x,
                endPoint_.y - startPoint_.y);
  region.Subtract(cutout);
  SetShape(region);
#endif