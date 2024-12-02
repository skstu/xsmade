#include "wxui.h"
wxBEGIN_EVENT_TABLE(FrameBgk, wxFrame) EVT_SIZE(FrameBgk::OnSize)
    EVT_CLOSE(FrameBgk::OnClose) EVT_MOTION(FrameBgk::OnMouseMove)
        EVT_LEFT_DOWN(FrameBgk::OnMouseLeftDown)
            EVT_LEFT_UP(FrameBgk::OnMouseLeftUp) EVT_PAINT(FrameBgk::OnPaint)
                wxEND_EVENT_TABLE();

FrameBgk::FrameBgk(wxWindow *parent, wxWindowID id, const wxString &title,
                   const wxPoint &pos, const wxSize &size, long style,
                   const wxString &name)
    : FrameBase(parent, id, title, pos, size,
                wxFRAME_SHAPED | wxNO_BORDER | wxFRAME_NO_TASKBAR, name) {
  wxDisplay display;
  wxRect workArea = display.GetGeometry();
  SetSize(0, 0, workArea.GetWidth(), workArea.GetHeight());
  SetBackgroundColour(wxColour(183, 110, 121));
  SetTransparent(50);
#if defined(__OSWIN__)
  SetWindowPos(GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#endif
}
FrameBgk::~FrameBgk() {
}
void FrameBgk::OnSize(wxSizeEvent &event) {
  event.Skip();
}

void FrameBgk::OnClose(wxCloseEvent &event) {
  event.Skip();
}

void FrameBgk::OnMouseMove(wxMouseEvent &event) {
  if (drawing_.load()) {
    endPoint_ = event.GetPosition();
    Refresh();
  }
}

void FrameBgk::OnMouseLeftDown(wxMouseEvent &event) {
  startPoint_ = event.GetPosition();
  endPoint_ = startPoint_;
  drawing_.store(true);
}

void FrameBgk::OnMouseLeftUp(wxMouseEvent &event) {
  endPoint_ = event.GetPosition();
  drawing_.store(false);
  Refresh();
  Show(false);
  auto handle = wxApp::GetInstance();
  do {
    wxCommandEvent *evtObj = new wxCommandEvent(wxEVT_COMMAND_THREAD);
    evtObj->SetClientData(new wxRect(startPoint_.x, startPoint_.y,
                                     endPoint_.x - startPoint_.x,
                                     endPoint_.y - startPoint_.y));
    auto tEvt = new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_CaptureFinished);
    tEvt->SetEventObject(evtObj);
    wxQueueEvent(wxApp::GetInstance(), tEvt);
    startPoint_.x = 0;
    startPoint_.y = 0;
    endPoint_.x = 0;
    endPoint_.y = 0;
    Refresh();
  } while (0);
}

void FrameBgk::OnPaint(wxPaintEvent &event) {
  wxPaintDC dc(this);

  wxPen redPen(wxColour(255, 0, 0), 5);
  dc.SetPen(redPen);

  dc.SetBrush(wxBrush(wxColour(0, 0, 0), wxTRANSPARENT));

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
}