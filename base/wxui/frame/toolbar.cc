#include <wxui.h>
wxBEGIN_EVENT_TABLE(IToolbar, wxFrame) EVT_SIZE(IToolbar::OnSize)
    EVT_MOVE(IToolbar::OnMove) EVT_CLOSE(IToolbar::OnClose)
        EVT_MOTION(IToolbar::OnMouseMove)
            EVT_LEFT_DOWN(IToolbar::OnMouseLeftDown)
                EVT_LEFT_DCLICK(IToolbar::OnMouseLeftDClick)
                    EVT_LEFT_UP(IToolbar::OnMouseLeftUp) wxEND_EVENT_TABLE();

IToolbar::IToolbar(wxWindow *parent, wxWindowID id, const wxString &title,
                   const wxPoint &pos, const wxSize &size, long style,
                   const wxString &name)
    : wxFrame(parent, id, title, wxPoint(0, 0), wxSize(800, 40),
              /*(wxDEFAULT_FRAME_STYLE & ~wxCLOSE_BOX & ~wxCAPTION)*/
              wxNO_BORDER | wxFRAME_NO_TASKBAR /*| wxRESIZE_BORDER*/, name) {
}
IToolbar::~IToolbar() {
}
void IToolbar::OnPosUpdated() const {
}
void IToolbar::OnFullScreenShown() {
}
void IToolbar::LayoutEx() {
}
void IToolbar::OnToolEvent(wxCommandEvent &evt) {
  evt.Skip();
}
void IToolbar::OnSize(wxSizeEvent &event) {
  LayoutEx();
  Refresh();
  event.Skip();
}
void IToolbar::OnMove(wxMoveEvent &event) {
  OnPosUpdated();
  event.Skip();
}
void IToolbar::OnClose(wxCloseEvent &event) {
  auto shape = dynamic_cast<wxFrame *>(
      wxDynamicCast(wxApp::GetInstance(), App)->FrameWorkGet());
  int res = wxMessageBox(L"Are you sure you want to exit system?", L"Memade®",
                         wxYES_NO, shape ? shape : this);
  if (res != wxYES) {
    event.Veto();
  } else {
    auto handle = wxApp::GetInstance();
    if (handle) {
      wxQueueEvent(
          handle, new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_FrameDestroy));
    }
    event.Skip();
  }
}
void IToolbar::OnMouseMove(wxMouseEvent &event) {
  wxPoint pt = event.GetPosition();
  if (event.Dragging() && event.LeftIsDown()) {
    is_dragging_.store(true);
    wxPoint pos = ClientToScreen(pt); // pos为点击位置

    Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));

    is_fullscreen_shown_.store((pos.y - m_delta.y) <= 0);
    OnFullScreenShown();
  }
}
void IToolbar::OnMouseLeftDClick(wxMouseEvent &event) {
  event.Skip();
}
void IToolbar::OnMouseLeftDown(wxMouseEvent &event) {
  CaptureMouse();
  wxPoint pt = ClientToScreen(event.GetPosition());
  wxPoint origin = GetPosition();
  int dx = pt.x - origin.x;
  int dy = pt.y - origin.y;
  m_delta = wxPoint(dx, dy);
  if (!is_fullscreen_shown_.load()) {
    prev_frame_tool_rect_ = GetRect();
    prev_frame_work_rect_ =
        wxDynamicCast(wxApp::GetInstance(), App)
            ->FrameGet(ComponentFrameType::RECORDING_WORKSPACE)
            ->GetRect();
  }
}
void IToolbar::OnMouseLeftUp(wxMouseEvent &event) {
  if (HasCapture()) {
    ReleaseMouse();
  }
  Global::ffxShowWindow(!is_fullscreen_shown_.load());
  is_dragging_.store(false);
}