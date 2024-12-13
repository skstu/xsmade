#include <wxui.h>
FrameScreenShot::Background::Background(wxWindow *parent, wxWindowID id,
                                        const wxString &title,
                                        const wxPoint &pos, const wxSize &size,
                                        long style, const wxString &name)
    : IBackground(parent, id, title, pos, size,
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
FrameScreenShot::Background::~Background() {
}

#if 0
FrameScreenShot::Background::Background(wxWindow *parent, wxWindowID id,
                                        const wxString &title,
                                        const wxPoint &pos, const wxSize &size,
                                        long style, const wxString &name)
    : wxFrame(parent, id, title, pos, size,
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
FrameScreenShot::Background::~Background() {
}
void FrameScreenShot::Background::OnSize(wxSizeEvent &event) {
  event.Skip();
}

void FrameScreenShot::Background::OnClose(wxCloseEvent &event) {
  event.Skip();
}

void FrameScreenShot::Background::OnMouseMove(wxMouseEvent &event) {
  if (drawing_.load()) {
    endPoint_ = event.GetPosition();
    Refresh();
  }
}

void FrameScreenShot::Background::OnMouseLeftDown(wxMouseEvent &event) {
  startPoint_ = event.GetPosition();
  endPoint_ = startPoint_;
  drawing_.store(true);
}

void FrameScreenShot::Background::OnMouseLeftUp(wxMouseEvent &event) {
  do {
    if (!drawing_.load())
      break;
    endPoint_ = event.GetPosition();
    drawing_.store(false);
    Refresh();
    Show(false);
    do {
      auto app = wxDynamicCast(wxApp::GetInstance(), App);
      auto comp_screenshot =
          app->FrameComponentGet(FrameComponentType::SCREENSHOT);

      wxRect rect(startPoint_.x, startPoint_.y, endPoint_.x - startPoint_.x,
                  endPoint_.y - startPoint_.y);

      comp_screenshot->SetPos(rect);
      comp_screenshot->Show(true);
#if 0
      wxCommandEvent *evtObj = new wxCommandEvent(wxEVT_COMMAND_THREAD);
      evtObj->SetClientData(new wxRect(startPoint_.x, startPoint_.y,
                                       endPoint_.x - startPoint_.x,
                                       endPoint_.y - startPoint_.y));
      auto tEvt =
          new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_CaptureFinished);
      tEvt->SetEventObject(evtObj);
      wxQueueEvent(wxApp::GetInstance(), tEvt);
#endif

      startPoint_.x = 0;
      startPoint_.y = 0;
      endPoint_.x = 0;
      endPoint_.y = 0;
      Refresh();
    } while (0);
  } while (0);
}

void FrameScreenShot::Background::OnPaint(wxPaintEvent &event) {
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
#endif