#include <wxui.h>

wxBEGIN_EVENT_TABLE(IWorkSpace, wxFrame) EVT_SIZE(IWorkSpace::OnSize)
    EVT_CLOSE(IWorkSpace::OnClose) EVT_PAINT(IWorkSpace::OnPaint)
        EVT_MOVE(IWorkSpace::OnMove) EVT_MOTION(IWorkSpace::OnMouseMove)
            EVT_LEFT_DOWN(IWorkSpace::OnMouseLeftDown)
                EVT_LEFT_UP(IWorkSpace::OnMouseLeftUp) wxEND_EVENT_TABLE();

IWorkSpace::IWorkSpace(wxWindow *parent, wxWindowID id, const wxString &title,
                       const wxPoint &pos, const wxSize &size, long style,
                       const wxString &name)
    : wxFrame(parent, id, title, pos, size, style, name) {
  //  SetBackgroundColour(wxColour(183, 110, 121));
  //			// Color color(20, 255, 215, 0);//!@ 土豪金
  // SetBackgroundColour(wxColour(183, 110, 121));
  // SetTransparent(50);
}
IWorkSpace::~IWorkSpace() {
}
void IWorkSpace::OnSize(wxSizeEvent &event) {
  Refresh();
  OnWorkSpaceSizeChanged(GetRect());
  event.Skip();
}
void IWorkSpace::OnMove(wxMoveEvent &event) {
  OnWorkSpaceSizeChanged(GetRect());
  event.Skip();
}
void IWorkSpace::OnClose(wxCloseEvent &event) {
  event.Skip();
}

void IWorkSpace::OnPaint(wxPaintEvent &event) {
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
void IWorkSpace::OnMouseMove(wxMouseEvent &event) {
  wxPoint pt = event.GetPosition();
  int desk_x(0), desk_y(0);
  wxGetMousePosition(&desk_x, &desk_y);
  if (event.Dragging() && event.LeftIsDown()) {
    is_dragging_.store(true);
    switch (resize_mode_.load()) {
    case ResizeMode::Left: {
      if (!is_allow_stretch_.load())
        break;
      long offset_x = mouse_left_down_rect_.GetLeft() - desk_x;
      wxRect current = mouse_left_down_rect_;
      current.SetWidth(mouse_left_down_rect_.GetWidth() + offset_x);
      current.SetLeft(desk_x);
      if (current.GetWidth() <= area_width_min_)
        break;
      SetSize(current);
    } break;
    case ResizeMode::Right: {
      if (!is_allow_stretch_.load())
        break;
      long offset_x = mouse_left_down_rect_.GetLeft() - desk_x;
      wxRect current = mouse_left_down_rect_;
      current.SetWidth(mouse_left_down_rect_.GetWidth() + offset_x);
      current.SetRight(desk_x);
      if (current.GetWidth() <= area_width_min_)
        break;
      SetSize(current);
    } break;
    case ResizeMode::Bottom: {
      if (!is_allow_stretch_.load())
        break;
      long offset_y = mouse_left_down_rect_.GetTop() - desk_y;
      wxRect current = mouse_left_down_rect_;
      current.SetHeight(mouse_left_down_rect_.GetHeight() + offset_y);
      current.SetBottom(desk_y);
      if (current.GetHeight() <= area_height_min_)
        break;
      SetSize(current);
    } break;
    case ResizeMode::LeftBottom: {
      if (!is_allow_stretch_.load())
        break;
      long offset_x = mouse_left_down_rect_.GetLeft() - desk_x;
      long offset_y = mouse_left_down_rect_.GetTop() - desk_y;
      wxRect current = mouse_left_down_rect_;
      if (current.GetWidth() > area_width_min_) {
        current.SetWidth(mouse_left_down_rect_.GetWidth() + offset_x);
        current.SetLeft(desk_x);
      }
      if (current.GetHeight() > area_height_min_) {
        current.SetHeight(mouse_left_down_rect_.GetHeight() + offset_y);
        current.SetBottom(desk_y);
      }
      SetSize(current);
    } break;
    case ResizeMode::RightBottom: {
      if (!is_allow_stretch_.load())
        break;
      long offset_x = mouse_left_down_rect_.GetLeft() - desk_x;
      long offset_y = mouse_left_down_rect_.GetTop() - desk_y;
      wxRect current = mouse_left_down_rect_;
      if (current.GetWidth() > area_width_min_) {
        current.SetWidth(mouse_left_down_rect_.GetWidth() + offset_x);
        current.SetRight(desk_x);
      }
      if (current.GetHeight() > area_height_min_) {
        current.SetHeight(mouse_left_down_rect_.GetHeight() + offset_y);
        current.SetBottom(desk_y);
      }
      SetSize(current);
    } break;
    case ResizeMode::None: {
      if (!is_allow_move_.load())
        break;
      wxPoint pos = ClientToScreen(pt); // pos为点击位置
      Move(wxPoint(pos.x - mouse_left_down_point_.x,
                   pos.y - mouse_left_down_point_.y));
    } break;
    default:
      break;
    }
    // is_fullscreen_shown_.store((pos.y - m_delta.y) <= 0);
    // OnFullScreenShown();
  }

  do { //!@ 拖动(设置光标图标)
    if (!is_allow_move_.load())
      break;
    if (is_dragging_.load())
      break;
    wxPoint pos = event.GetPosition();
    wxSize clientSize = GetClientSize();
    const int border_width_ = 5;
    //!@ 左下角
    if (pos.x <= border_width_ &&
        (clientSize.GetHeight() - pos.y) <= border_width_) {
      SetCursor(wxCursor(wxCURSOR_SIZENESW));
      resize_mode_.store(ResizeMode::LeftBottom);
    } else if (pos.x >= (clientSize.GetWidth() - border_width_) &&
               pos.y >= (clientSize.GetHeight() - border_width_)) { //!@ 右下角
      SetCursor(wxCursor(wxCURSOR_SIZENWSE));
      resize_mode_.store(ResizeMode::RightBottom);
    } else if (pos.x <= border_width_ && pos.y > border_width_) { //!@ 左边
      SetCursor(wxCursor(wxCURSOR_SIZEWE));
      resize_mode_.store(ResizeMode::Left);
    } else if (pos.x >= (clientSize.GetWidth() - border_width_) &&
               pos.y > border_width_) { //!@ 右边
      SetCursor(wxCursor(wxCURSOR_SIZEWE));
      resize_mode_.store(ResizeMode::Right);
    } else if (pos.y >= (clientSize.GetHeight() - border_width_)) { //!@ 下边
      SetCursor(wxCursor(wxCURSOR_SIZENS));
      resize_mode_.store(ResizeMode::Bottom);
    } else {
      resize_mode_.store(ResizeMode::None);
      if (pos.x > border_width_ && pos.x < clientSize.x &&
          pos.y > border_width_ && pos.y < clientSize.y) {
        SetCursor(wxCursor(wxCURSOR_SIZING));
      } else {
        SetCursor(wxCursor(wxCURSOR_ARROW));
      }
    }
  } while (0);
}
void IWorkSpace::OnMouseLeftDown(wxMouseEvent &event) {
  if (!HasCapture()) {
    CaptureMouse();
  }
  wxPoint pt = ClientToScreen(event.GetPosition());
  wxPoint origin = GetPosition();
  int dx = pt.x - origin.x;
  int dy = pt.y - origin.y;
  mouse_left_down_point_ = wxPoint(dx, dy);
  mouse_left_down_rect_ = GetRect();
}
void IWorkSpace::OnMouseLeftUp(wxMouseEvent &event) {
  if (HasCapture()) {
    ReleaseMouse();
  }
  is_dragging_.store(false);
}