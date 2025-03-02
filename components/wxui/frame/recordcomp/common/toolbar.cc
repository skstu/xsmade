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
    : wxFrame(parent, id, title, wxPoint(0, 0), size,
              /*(wxDEFAULT_FRAME_STYLE & ~wxCLOSE_BOX & ~wxCAPTION)*/
              wxNO_BORDER | wxFRAME_NO_TASKBAR /*| wxRESIZE_BORDER*/, name) {
}
IToolbar::~IToolbar() {
}
void IToolbar::OnToolEvent(wxCommandEvent &evt) {
  evt.Skip();
}
void IToolbar::OnSize(wxSizeEvent &event) {
  OnLayout();
  Refresh();
  event.Skip();
}
void IToolbar::OnMove(wxMoveEvent &event) {
  OnToolbarSizeChanged(GetRect());
  event.Skip();
}
void IToolbar::OnMouseMove(wxMouseEvent &event) {
  do {
    if (!is_allow_move_.load())
      break;
    wxPoint pt = event.GetPosition();
    if (event.Dragging() && event.LeftIsDown()) {
      is_dragging_.store(true);
      wxPoint pos = ClientToScreen(pt); // pos为点击位置
      Move(wxPoint(pos.x - delta_.x, pos.y - delta_.y));
      is_fullscreen_shown_.store((pos.y - delta_.y) <= 0);
      OnFullScreenShown();
    }
  } while (0);
}
void IToolbar::OnMouseLeftDClick(wxMouseEvent &event) {
  event.Skip();
}
void IToolbar::OnMouseLeftDown(wxMouseEvent &event) {
  do {
    if (!is_allow_move_.load())
      break;
    CaptureMouse();
    wxPoint pt = ClientToScreen(event.GetPosition());
    wxPoint origin = GetPosition();
    int dx = pt.x - origin.x;
    int dy = pt.y - origin.y;
    delta_ = wxPoint(dx, dy);
    if (!is_fullscreen_shown_.load()) {
      prev_frame_tool_rect_ = GetRect();
      prev_frame_work_rect_ =
          wxDynamicCast(wxApp::GetInstance(), App)
              ->FrameGet(ComponentFrameType::RECORDING_WORKSPACE)
              ->GetRect();
    }
  } while (0);
  event.Skip();
}
void IToolbar::OnMouseLeftUp(wxMouseEvent &event) {
  do {
    if (!is_allow_move_.load())
      break;
    if (HasCapture()) {
      ReleaseMouse();
    }
  } while (0);
  is_dragging_.store(false);
  event.Skip();
}