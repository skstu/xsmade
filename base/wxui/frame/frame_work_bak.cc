#include "wxui.h"
#if 0
/*EVT_CONTEXT_MENU(FrameWork::OnContextMenu)*/
wxBEGIN_EVENT_TABLE(FrameWork, wxFrame) EVT_SIZE(FrameWork::OnSize)
    EVT_PAINT(FrameWork::OnPaint) EVT_CLOSE(FrameWork::OnClose)
        EVT_LEFT_DOWN(FrameWork::OnLeftDown) EVT_LEFT_UP(FrameWork::OnLeftUp)
            EVT_RIGHT_DOWN(FrameWork::OnRightDown)
                EVT_RIGHT_UP(FrameWork::OnRightUp)
                    EVT_MOUSE_CAPTURE_LOST(FrameWork::OnMouseLost)
                        EVT_MOTION(FrameWork::OnMotion)
                            EVT_ERASE_BACKGROUND(FrameWork::OnErase)
                                EVT_ENTER_WINDOW(FrameWork::OnEnterWindow)
                                    EVT_LEAVE_WINDOW(FrameWork::OnLeaveWindow)
                                        wxEND_EVENT_TABLE();

FrameWork::FrameWork(wxWindow *parent, wxWindowID id, const wxString &title,
                     const wxPoint &pos, const wxSize &size, long style,
                     const wxString &name)
    : FrameBase(parent, id, title, pos, wxSize(640, 480),
                wxFRAME_SHAPED | wxFRAME_NO_TASKBAR, name) {
  m_MouseRightPopupMenu.Append(0, "&About");
  // m_MouseRightPopupMenu.Append(1, "&Submenu", CreateDummyMenu(NULL));
  m_MouseRightPopupMenu.Append(2, "To be &deleted");
  m_MouseRightPopupMenu.AppendCheckItem(3, "To be &checked");
  m_MouseRightPopupMenu.Append(4, "To be &greyed",
                               "This menu item should be initially greyed out");
  m_MouseRightPopupMenu.AppendSeparator();
  m_MouseRightPopupMenu.Append(5, "E&xit")
      ->SetBitmap(wxArtProvider::GetBitmapBundle(wxART_QUIT, wxART_MENU));
  SetTheme(0);
}

FrameWork::~FrameWork() {
}
void FrameWork::SetRegion(long x, long y, long cx, long cy) {
  wxFrameBase::SetPosition(wxPoint(x, y));
  wxFrameBase::SetSize(wxSize(cx, cy));
  SetTheme(0);
}
void FrameWork::OnSize(wxSizeEvent &wxEvent) {
  wxEvent.Skip();
}
void FrameWork::OnClose(wxCloseEvent &wxEvent) {
  wxEvent.Skip();
}
void FrameWork::OnErase(wxEraseEvent &wxEvent) {
  wxEvent.Skip();
}
void FrameWork::OnPaint(wxPaintEvent &wxEvent) {
  do {
    // break;
    int width{0}, height{0};
    GetSize(&width, &height);
    width += region_offset_x_;
    height += region_offset_y_;
    if (width <= 0 || height <= 0)
      break;
    wxBufferedPaintDC BufferDC(this);
    BufferDC.SetBrush(*wxTRANSPARENT_BRUSH);
    BufferDC.Clear();

    SetBackgroundColour(wxColour(255, 0, 0, wxALPHA_OPAQUE));
    if (theme_) {
      BufferDC.SetBrush(*wxTRANSPARENT_BRUSH);
      BufferDC.Clear();
      BufferDC.DrawBitmap(
          wxBitmap(theme_->GetShapeImage().Scale(width, height)),
          region_offset_x_, region_offset_y_, true);
    }
  } while (0);
  wxEvent.Skip();
}
bool FrameWork::SetTheme(const wxui::tfThemeIdentify &theme_identify) {
  bool result = false;
#if 0
  do {
    theme_ = const_cast<Theme *>(Config::Get()->GetTheme(theme_identify));
    if (!theme_)
      break;
    wxSize size = GetSize();
    size.x += region_offset_x_;
    size.y += region_offset_y_;
    if (!SetShape(theme_->GetShapeImage().Scale(size.x, size.y)))
      break;

    SetBackgroundColour(wxColour(255, 0, 0, wxALPHA_OPAQUE));
    Layout();
    Refresh();
    // Center();
#if defined(__OSWIN__)
    SetWindowPos(GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
#endif
  } while (0);
#endif
  do { //!@ theme
    wxImage *themeImg = Config::Get()->GetResImage("theme.png");
    if (!themeImg)
      break;
    wxSize size = GetSize();
    size.x += region_offset_x_;
    size.y += region_offset_y_;
    if (!SetShape(themeImg->Scale(size.x, size.y)))
      break;

    SetBackgroundColour(wxColour(255, 0, 0, wxALPHA_OPAQUE));
    Layout();
    Refresh();
  } while (0);
  return result;
}
bool FrameWork::SetShape(const wxImage &img) {
  wxImage m = img;
  if (m.HasAlpha())
    m.ConvertAlphaToMask();
  wxRegion region(m);
  return wxNonOwnedWindow::SetShape(region);
}

void FrameWork::OnMotion(wxMouseEvent &wxEvent) {
  wxPoint pt = wxEvent.GetPosition();
  bool isDown = wxEvent.LeftIsDown();
  if (isDown && wxEvent.Dragging() && HasCapture()) {
    wxPoint mouse_pos = ClientToScreen(pt);
    if (m_offset.x != -1) {
      wxPoint dp = mouse_pos - m_offset;
      this->Move(dp);
    }
  }
}
void FrameWork::OnLeftDown(wxMouseEvent &wxEvent) {
  wxPoint pt = wxEvent.GetPosition();
  if (!HasCapture() && !m_rect.Contains(pt))
    CaptureMouse();
  wxPoint mouse_pos = ClientToScreen(pt);
  wxPoint wnd_pos = this->GetPosition();
  m_offset.x = mouse_pos.x - wnd_pos.x;
  m_offset.y = mouse_pos.y - wnd_pos.y;
  std::cout << __FUNCTION__ << std::endl;
}
void FrameWork::OnLeftUp(wxMouseEvent &wxEvent) {
  m_offset = wxPoint(-1, -1);
  //   if (HasCapture())
  //     ReleaseMouse();
  std::cout << __FUNCTION__ << std::endl;
}
void FrameWork::OnContextMenu(wxContextMenuEvent &) {
  std::cout << __FUNCTION__ << std::endl;
}
void FrameWork::OnRightDown(wxMouseEvent &wxEvent) {
  auto sk = 0;
  std::cout << __FUNCTION__ << std::endl;
}
void FrameWork::OnRightUp(wxMouseEvent &wxEvent) {
  auto sk = 0;
  std::cout << __FUNCTION__ << std::endl;

  wxPoint point = wxEvent.GetPosition();
  //// If from keyboard
  // if (point.x == -1 && point.y == -1) {
  //  wxSize size = GetSize();
  //  point.x = size.x / 2;
  //  point.y = size.y / 2;
  // }
  // else {
  //  point = ScreenToClient(point);
  // }

  PopupMenu(&m_MouseRightPopupMenu, point);
  std::cout << __FUNCTION__ << std::endl;
}
void FrameWork::OnMouseLost(wxMouseCaptureLostEvent &wxEvent) {
  m_offset = wxPoint(-1, -1);
  //   if (HasCapture())
  //     ReleaseMouse();
  std::cout << __FUNCTION__ << std::endl;
}
void FrameWork::OnEnterWindow(wxMouseEvent &wxEvent) {
  /* wxEvent.Skip();*/
  // CaptureMouse();
  std::cout << __FUNCTION__ << std::endl;
}
void FrameWork::OnLeaveWindow(wxMouseEvent &wxEvent) {

  // wxEvent.Skip();

  // Refresh();
  //
#if 0
   //鼠标拖动事件，当鼠标离开窗口时，发送信号告诉窗口
   //这个是为了解决拖动速度过快导致窗口没有跟踪上鼠标
   bool isDown = wxEvent.LeftIsDown();
   bool isDragging = wxEvent.Dragging();
   if (isDown && isDragging)
   {
    wxCommandEvent ev(wxEVT_MOTION, GetId());
    ev.SetEventObject(this);
    GetEventHandler()->ProcessEvent(ev);
   }
#endif
  //   if (HasCapture())
  //     ReleaseMouse();
  std::cout << __FUNCTION__ << std::endl;
  auto sk = 0;
}
#endif