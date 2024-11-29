#include "wxui.h"

/*EVT_CONTEXT_MENU(ShapeFrame::OnContextMenu)*/
wxBEGIN_EVENT_TABLE(ShapeFrame, wxFrame) EVT_SIZE(ShapeFrame::OnSize)
    EVT_PAINT(ShapeFrame::OnPaint) EVT_CLOSE(ShapeFrame::OnClose)
        EVT_LEFT_DOWN(ShapeFrame::OnLeftDown) EVT_LEFT_UP(ShapeFrame::OnLeftUp)
            EVT_RIGHT_DOWN(ShapeFrame::OnRightDown)
                EVT_RIGHT_UP(ShapeFrame::OnRightUp)
                    EVT_MOUSE_CAPTURE_LOST(ShapeFrame::OnMouseLost)
                        EVT_MOTION(ShapeFrame::OnMotion)
                            EVT_ERASE_BACKGROUND(ShapeFrame::OnErase)
                                EVT_ENTER_WINDOW(ShapeFrame::OnEnterWindow)
                                    EVT_LEAVE_WINDOW(ShapeFrame::OnLeaveWindow)
                                        wxEND_EVENT_TABLE();

ShapeFrame::ShapeFrame(wxWindow *parent, wxWindowID id, const wxString &title,
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

  Bind(wxEVT_BUTTON, &ShapeFrame::OnToolbarEvent, this);
}

ShapeFrame::~ShapeFrame() {
  Unbind(wxEVT_BUTTON, &ShapeFrame::OnToolbarEvent, this);
}
void ShapeFrame::SetRegion(long x, long y, long cx, long cy) {
  wxFrameBase::SetPosition(wxPoint(x, y));
  wxFrameBase::SetSize(wxSize(cx, cy));
  SetTheme(0);
}
void ShapeFrame::OnSize(wxSizeEvent &wxEvent) {
  wxEvent.Skip();
}
void ShapeFrame::OnClose(wxCloseEvent &wxEvent) {
  int res = wxMessageBox("Are you sure you want to exit system?", "tip",
                         wxYES_NO, this);
  if (res != wxYES) {
    wxEvent.Veto();
  } else {
    auto handle = wxApp::GetInstance();
    if (handle)
      wxQueueEvent(
          handle, new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_FrameDestroy));
    wxEvent.Skip();
  }
}
void ShapeFrame::OnErase(wxEraseEvent &wxEvent) {
  wxEvent.Skip();
}
void ShapeFrame::OnPaint(wxPaintEvent &wxEvent) {
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
bool ShapeFrame::SetTheme(const wxui::tfThemeIdentify &theme_identify) {
  bool result = false;
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
#if _WIN32
    SetWindowPos(GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
#endif
  } while (0);
  return result;
}
bool ShapeFrame::SetShape(const wxImage &img) {
  wxImage m = img;
  if (m.HasAlpha())
    m.ConvertAlphaToMask();
  wxRegion region(m);
  return wxNonOwnedWindow::SetShape(region);
}

void ShapeFrame::OnMotion(wxMouseEvent &wxEvent) {
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
void ShapeFrame::OnLeftDown(wxMouseEvent &wxEvent) {
  wxPoint pt = wxEvent.GetPosition();
  if (!HasCapture() && !m_rect.Contains(pt))
    CaptureMouse();
  wxPoint mouse_pos = ClientToScreen(pt);
  wxPoint wnd_pos = this->GetPosition();
  m_offset.x = mouse_pos.x - wnd_pos.x;
  m_offset.y = mouse_pos.y - wnd_pos.y;
  std::cout << __FUNCTION__ << std::endl;
}
void ShapeFrame::OnLeftUp(wxMouseEvent &wxEvent) {
  m_offset = wxPoint(-1, -1);
  //   if (HasCapture())
  //     ReleaseMouse();
  std::cout << __FUNCTION__ << std::endl;
}
void ShapeFrame::OnContextMenu(wxContextMenuEvent &) {
  std::cout << __FUNCTION__ << std::endl;
}
void ShapeFrame::OnRightDown(wxMouseEvent &wxEvent) {
  auto sk = 0;
  std::cout << __FUNCTION__ << std::endl;
}
void ShapeFrame::OnRightUp(wxMouseEvent &wxEvent) {
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
void ShapeFrame::OnMouseLost(wxMouseCaptureLostEvent &wxEvent) {
  m_offset = wxPoint(-1, -1);
  //   if (HasCapture())
  //     ReleaseMouse();
  std::cout << __FUNCTION__ << std::endl;
}
void ShapeFrame::OnEnterWindow(wxMouseEvent &wxEvent) {
  /* wxEvent.Skip();*/
  // CaptureMouse();
  std::cout << __FUNCTION__ << std::endl;
}
void ShapeFrame::OnLeaveWindow(wxMouseEvent &wxEvent) {

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
void ShapeFrame::OnToolbarEvent(wxCommandEvent &evt) {
  switch (evt.GetId()) {
  case CommandTool::BTN_SCALING_UP: {
  } break;
  case CommandTool::BTN_SCALING_DOWN: {
  } break;
  default:
    break;
  }
  evt.Skip();
}
#if 0
bool ShapeFrame::AppendTheme(Theme *theme) {
  bool result = false;
  do {
    if (!theme->Ready())
      break;
    auto found = m_Themes.find(theme->Identify());
    if (found != m_Themes.end())
      m_Themes.erase(found);
    m_Themes.emplace(theme->Identify(), theme);
    result = true;
  } while (0);
  return result;
}
bool ShapeFrame::SetTheme(const IdentifyTheme &current /*= ""*/) {
  bool result = false;
  do {
    Theme *pos = nullptr;
    if (m_Themes.empty())
      break;
    if (!current.empty()) {
      auto found = m_Themes.find(current);
      if (found == m_Themes.end())
        break;
      pos = found->second;
    } else
      pos = m_Themes.begin()->second;
    m_CurrentTheme = pos->Identify();
    auto size = pos->MainWindowSize();
    SetSize(size);
    if (!SetShape(pos->ImgShape().Scale(size.x, size.y)))
      break;

    SetBackgroundColour(wxColour(255, 0, 0, wxALPHA_OPAQUE));
    Layout();
    Refresh();
    result = true;
  } while (0);
  return result;
}
#endif