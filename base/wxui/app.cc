#include "wxui.h"

#if 0
// 定义Frame类
class ShapedFrame : public wxFrame {
public:
  ShapedFrame();
  ~ShapedFrame();

private:
  wxBitmap m_bmp;
  bool m_hasShape;
  wxPoint m_delta;

  void OnMouseMove(wxMouseEvent &event);
  void OnPaint(wxPaintEvent &event);
  void OnMouseLeftDown(wxMouseEvent &event);
  void OnMouseLeftUp(wxMouseEvent &event);

  void SetWindowShape();
#ifdef __WXGTK__
  void OnWindowCreate(wxWindowCreateEvent &event);
#endif
  DECLARE_EVENT_TABLE()
};

// 建立事件处理连接。鼠标移动事件由OnMouseMove捕获，重绘事件由OnPaint捕获，鼠标左键按下事件由OnMouseLeftDown捕获~
BEGIN_EVENT_TABLE(ShapedFrame, wxFrame)
EVT_MOTION(ShapedFrame::OnMouseMove)
EVT_PAINT(ShapedFrame::OnPaint)
EVT_LEFT_DOWN(ShapedFrame::OnMouseLeftDown)
EVT_LEFT_UP(ShapedFrame::OnMouseLeftUp)
#ifdef __WXGTK__
EVT_WINDOW_CREATE(ShapedFrame::OnWindowCreate)
#endif
END_EVENT_TABLE()

ShapedFrame::ShapedFrame()
    : wxFrame((wxFrame *)NULL, wxID_ANY, wxEmptyString, wxDefaultPosition,
              wxSize(1920, 1080),
              wxFRAME_SHAPED | wxSIMPLE_BORDER | wxFRAME_NO_TASKBAR) {

  int width = 1920;  // 矩形的宽度
  int height = 1080; // 矩形的高度

  // 创建一个空白的位图，并确保它支持 alpha 通道
  m_bmp.Create(width, height, 32); // 32 表示支持 alpha 通道

  // 使用 wxMemoryDC 来绘制位图
  wxMemoryDC dc;
  dc.SelectObject(m_bmp);

  // 设置画笔和刷子的颜色
  dc.SetBrush(wxBrush(wxColor(55, 55, 55, 210))); // 半透明的灰色
  dc.SetPen(*wxTRANSPARENT_PEN);                  // 完全透明的边框

  // 绘制一个圆角矩形
  int x = 0;       // 左上角的x坐标
  int y = 0;       // 左上角的y坐标
  int radius = 20; // 圆角的半径
  dc.DrawRoundedRectangle(x, y, width, height, radius);

  // 释放位图
  dc.SelectObject(wxNullBitmap);

  m_hasShape = false;
  SetSize(wxSize(m_bmp.GetWidth(), m_bmp.GetHeight()));

  SetWindowShape();

  // 设置窗口的透明度
  SetTransparent(210); // 0-255 之间的值，255 表示完全不透明
}

#ifdef __WXGTK__
void ShapedFrame::OnWindowCreate(wxWindowCreateEvent &event) {
  SetWindowShape();
}
#endif

void ShapedFrame::SetWindowShape() {
  // 创建一个与位图相同尺寸的 wxRegion
  wxRegion region(m_bmp, wxColour(0, 0, 0, 0)); // 使用完全透明的颜色作为掩码
  SetShape(region);
  m_hasShape = true;
}

void ShapedFrame::OnMouseMove(wxMouseEvent &event) {
  wxPoint pt = event.GetPosition();

  if (event.Dragging() && event.LeftIsDown()) {
    wxPoint pos = ClientToScreen(pt); // pos为点击位置

    Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));
  }
}

void ShapedFrame::OnMouseLeftDown(wxMouseEvent &event) {
  CaptureMouse();
  wxPoint pt = ClientToScreen(event.GetPosition());
  wxPoint origin = GetPosition();
  int dx = pt.x - origin.x;
  int dy = pt.y - origin.y;
  m_delta = wxPoint(dx, dy);
}

void ShapedFrame::OnMouseLeftUp(wxMouseEvent &event) {
  if (HasCapture()) {
    ReleaseMouse();
  }
}

void ShapedFrame::OnPaint(wxPaintEvent &event) {
  wxPaintDC dc(this);
  dc.DrawBitmap(m_bmp, 0, 0, true);
}

ShapedFrame::~ShapedFrame() {
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////

App::App() {
}
App::~App() {
}
bool App::OnInit() {
  bool result = false;
  do {
    if (!wxApp::OnInit()) {
      break;
    }
    wxAppBase::SetExitOnFrameDelete(false);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtFrameDestroy, this,
                       wxAppThreadEvt_FrameDestroy);

    OnFrameCreate();
    result = true;
  } while (0);
  return result;
}
int App::OnExit() {
  int result = 0;
  do {
    OnFrameDestroy();
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtFrameDestroy, this,
                         wxAppThreadEvt_FrameDestroy);
    result = wxApp::OnExit();
  } while (0);
  return result;
}
void App::OnThreadEvtFrameDestroy(wxThreadEvent &event) {
  ExitMainLoop();
}
void App::OnFrameDestroy() {
  do {
#if 0
    logo_.FreeResource();
#endif
  } while (0);
}
void App::OnFrameCreate() {
  do {
    wxFrame *frame = nullptr;
    switch (Config::Get()->GetFrameType()) {
    case FrameType::FRAME: {
      frame_ = new Frame(nullptr);
      frame = dynamic_cast<wxFrame *>(frame_);
    } break;
    case FrameType::SHAPEFRAME: {
      frame_shape_ = new ShapeFrame(nullptr);
      frame_ = new FrameToolbar(nullptr);
      // dynamic_cast<FrameToolbar *>(frame_)->SetTheme(0);
      frame = dynamic_cast<wxFrame *>(frame_);
      // frame_toolbar_ = new FrameToolbar(nullptr);
      // frame_toolbar_->Show();

    } break;
    default:
      break;
    }
    frame->Show(true);
    frame->Center();
#if 0
    logo_.CreateFromHICON(shared::Win::Window::LoadMemIcon(
        std::string((char *)rawLogoIco, sizeof(rawLogoIco))));
    frame_ = new MDIFrame(nullptr, wxID_ANY, wxString(L"BrwControl®"),
                          wxDefaultPosition, wxSize(1024, 768));
    dynamic_cast<MDIFrame *>(frame_)->wxWindowBase::Center();
    dynamic_cast<MDIFrame *>(frame_)->wxTopLevelWindowBase::SetIcon(logo_);
    // dynamic_cast<MDIFrame*>(frame_)->Show(true);
#endif
  } while (0);
}
IFrame *App::FrameGet() const {
  return frame_;
}
IFrame *App::FrameShapeGet() const {
  return frame_shape_;
}
/////////////////////////////////////////////////////////////////////////////
wxIMPLEMENT_APP_NO_MAIN(App);
const int wxAppThreadEvt_FrameDestroy = wxNewId();
const int wxAppThreadEvt_BroadcastEvent = wxNewId();
