#include <wxui.h>
wxBEGIN_EVENT_TABLE(IBackground, wxFrame) EVT_SIZE(IBackground::OnSize)
    EVT_CLOSE(IBackground::OnClose) EVT_MOTION(IBackground::OnMouseMove)
        EVT_LEFT_DOWN(IBackground::OnMouseLeftDown)
            EVT_LEFT_UP(IBackground::OnMouseLeftUp)
                EVT_KEY_DOWN(IBackground::OnKeyDown)
                    EVT_CHAR(IBackground::OnChar) EVT_SHOW(IBackground::OnShow)
                        EVT_PAINT(IBackground::OnPaint) wxEND_EVENT_TABLE();

IBackground::IBackground(wxWindow *parent, wxWindowID id, const wxString &title,
                         const wxPoint &pos, const wxSize &size, long style,
                         const wxString &name)
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
IBackground::~IBackground() {
}
void IBackground::OnSize(wxSizeEvent &event) {
  event.Skip();
}

void IBackground::OnClose(wxCloseEvent &event) {
  event.Skip();
}

void IBackground::OnMouseMove(wxMouseEvent &event) {
  if (drawing_.load()) {
    endPoint_ = event.GetPosition();
    Refresh();
  }
}

void IBackground::OnMouseLeftDown(wxMouseEvent &event) {
  startPoint_ = event.GetPosition();
  endPoint_ = startPoint_;
  drawing_.store(true);
}
void IBackground::OnKeyDown(wxKeyEvent &event) {
  event.Skip();
}
void IBackground::OnChar(wxKeyEvent &event) {
  switch (wxKeyCode(event.GetKeyCode())) {
  case wxKeyCode::WXK_ESCAPE: {
#if 0
    drawing_.store(false);
    Refresh();
    Show(false);
#endif
    wxQueueEvent(wxApp::GetInstance(),
                 new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_FrameDestroy));
  } break;
  default:
    break;
  }
  event.Skip();
}
void IBackground::OnShow(wxShowEvent &event) {
  if (event.IsShown()) {
    SetCursor(wxCursor(wxCURSOR_CROSS));
    SetWindowStyle(GetWindowStyle() | wxSTAY_ON_TOP);
  } else {
    SetCursor(wxCursor(wxCURSOR_ARROW));
    SetWindowStyle(GetWindowStyle() & ~wxSTAY_ON_TOP);
  }
  event.Skip();
}
void IBackground::OnMouseLeftUp(wxMouseEvent &event) {
  do {
    if (!drawing_.load())
      break;
    endPoint_ = event.GetPosition();
    drawing_.store(false);
    Refresh();
    Show(false);
    do {
#if 0
      auto app = wxDynamicCast(wxApp::GetInstance(), App);
      auto comp_screenshot =
          app->FrameComponentGet(FrameComponentType::SCREENSHOT);

      wxRect rect(startPoint_.x, startPoint_.y, endPoint_.x - startPoint_.x,
                  endPoint_.y - startPoint_.y);

      comp_screenshot->SetPos(rect);
      comp_screenshot->Show(true);
#endif
      do {
        auto app = wxDynamicCast(wxApp::GetInstance(), App);
        wxRect pos(startPoint_.x, startPoint_.y, endPoint_.x - startPoint_.x,
                   endPoint_.y - startPoint_.y);

        IFrameComponent *record_component =
            app->FrameComponentGet(FrameComponentType::RECORDING);
        if (!record_component)
          break;

        wxRect pos_prev(pos);
        if (pos.width < 0 || pos.height < 0) {
          pos.SetLeft(pos.x + pos.width);
          pos.SetTop(pos.y + pos.height);
          pos.SetRight(pos_prev.x);
          pos.SetBottom(pos_prev.y);
        }
        record_component->SetPos(pos);
        record_component->Show(true);

#if 0
        wxCommandEvent sender;

        std::string jsonRect = fmt::format("x:{},y:{},width:{},height:{}",
                                           pos.x, pos.y, pos.width, pos.height);
        jsonRect.insert(0, "{");
        jsonRect.append("}");
        sender.SetString(wxString(jsonRect));
        auto tEvt = new wxThreadEvent(
            wxEVT_THREAD, wxAppThreadEvt_RecordingBoxSelectionFinished);
        tEvt->SetEventObject(&sender);
        wxQueueEvent(wxApp::GetInstance(), tEvt);
#endif
      } while (0);

      startPoint_.x = 0;
      startPoint_.y = 0;
      endPoint_.x = 0;
      endPoint_.y = 0;
      Refresh();
    } while (0);
  } while (0);
}

void IBackground::OnPaint(wxPaintEvent &event) {
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