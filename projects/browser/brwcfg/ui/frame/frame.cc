#include <brwcfg.h>
wxBEGIN_EVENT_TABLE(IFrame, wxFrame) EVT_SIZE(IFrame::OnSize)
    EVT_CLOSE(IFrame::OnClose) wxEND_EVENT_TABLE();

IFrame::IFrame(wxWindow *parent, wxWindowID id, const wxString &title,
               const wxPoint &pos, const wxSize &size, long style,
               const wxString &name)
    : wxFrame(parent, id, title, pos, size, style, name) {
}

IFrame::~IFrame() {
}
void IFrame::OnSize(wxSizeEvent &) {
}
void IFrame::OnClose(wxCloseEvent &wxEvt) {
  int res = wxMessageBox(L"Are you sure you want to exit system?", L"Memade®",
                         wxYES_NO, this);
  if (res != wxYES) {
    wxEvt.Veto();
  } else {
    auto handle = wxApp::GetInstance();
    if (handle) {
      wxQueueEvent(
          handle, new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_FrameDestroy));
    }
    wxEvt.Skip();
  }
}
#if 0
BEGIN_EVENT_TABLE(Frame, wxFrame)
EVT_MOTION(Frame::OnMouseMove)
EVT_PAINT(Frame::OnPaint)
EVT_LEFT_DOWN(Frame::OnMouseLeftDown)
EVT_LEFT_UP(Frame::OnMouseLeftUp)
EVT_ERASE_BACKGROUND(Frame::OnErase)
#ifdef __WXGTK__
EVT_WINDOW_CREATE(Frame::OnWindowCreate)
#endif
END_EVENT_TABLE()

Frame::Frame(wxWindow *parent, wxWindowID id, const wxString &title,
             const wxPoint &pos, const wxSize &size, long style,
             const wxString &name)
    : wxFrame(parent, id, title, pos, size,
              wxNO_BORDER | wxFRAME_SHAPED /*| wxFRAME_NO_TASKBAR*/, name) {
  //image_ = Global::Get()->GetResImage(u"test.png");
  m_bmp = wxBitmap(*image_);
  // int width = image->GetWidth();
  // int height = image->GetHeight();
  // SetSize(wxSize(width, height));
  // SetShape(*image);
  SetBackgroundStyle(wxBG_STYLE_PAINT);
  // SetBackgroundColour(wxColour(255, 0, 0, wxALPHA_OPAQUE));
  // SetBackgroundColour(wxColour(0, 0, 0, 0));
  // Layout();
  // Refresh();
}
Frame::~Frame() {
}
bool Frame::SetShape(const wxBufferedPaintDC &dc) {
  if (image_) {
    wxImage m = *image_;

    // 确保图像包含 alpha 通道
    if (m.HasAlpha()) {
      // 生成一个路径来表示图像的透明区域
      wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
      if (gc) {
        m_shapePath = gc->CreatePath();

        // 获取图像大小
        int width = m.GetWidth();
        int height = m.GetHeight();

        // 使用图像的 alpha 通道来确定透明区域的边缘
        bool inShape = false;
        for (int y = 0; y < height; ++y) {
          for (int x = 0; x < width; ++x) {
            // 检查当前像素的 alpha 值，决定是否属于透明区域
            if (m.GetAlpha(x, y) > 0) {
              if (!inShape) {
                // 进入形状区域，开始路径
                m_shapePath.MoveToPoint(x, y);
                inShape = true;
              } else {
                // 在形状区域内继续绘制路径
                m_shapePath.AddLineToPoint(x, y);
              }
            } else {
              if (inShape) {
                // 退出形状区域，完成当前路径
                m_shapePath.CloseSubpath();
                inShape = false;
              }
            }
          }
        }

        // 如果最后仍然在形状区域，则关闭路径
        if (inShape) {
          m_shapePath.CloseSubpath();
        }

        delete gc; // 完成路径创建后可以删除 wxGraphicsContext
      }
    }

    if (image_) {
      wxImage m = *image_;
      if (m.HasAlpha()) {
        m.ConvertAlphaToMask();
      }
      wxRegion region(m);
      if (region.IsOk()) {
        wxNonOwnedWindow::SetShape(region);
      }
      Refresh();
      return true;
    }

    return true;
  }
  return false;
}
#if 0
bool Frame::SetShape() {
  if (image_) {
    wxImage m = *image_;
    if (m.HasAlpha()) {
      m.ConvertAlphaToMask();
    }
    wxRegion region(m);
    if (region.IsOk()) {
      wxNonOwnedWindow::SetShape(region);
    }
    Refresh();
    return true;
  }
  return false;
}
#endif
void Frame::OnMouseMove(wxMouseEvent &event) {
  wxPoint pt = event.GetPosition();
  if (event.Dragging() && event.LeftIsDown()) {
    wxPoint pos = ClientToScreen(pt); // pos为点击位置
    Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));
  }
}
void Frame::OnMouseLeftDown(wxMouseEvent &event) {
  CaptureMouse();
  wxPoint pt = ClientToScreen(event.GetPosition());
  wxPoint origin = GetPosition();
  int dx = pt.x - origin.x;
  int dy = pt.y - origin.y;
  m_delta = wxPoint(dx, dy);
}
void Frame::OnMouseLeftUp(wxMouseEvent &event) {
  if (HasCapture()) {
    ReleaseMouse();
  }
}
void Frame::OnErase(wxEraseEvent &wxEvent) {
  wxEvent.Skip();
}
void Frame::OnPaint(wxPaintEvent &event) {
#if 0
  do {
    int width{0}, height{0};
    GetSize(&width, &height);
    if (width <= 0 || height <= 0)
      break;

    wxBufferedPaintDC BufferDC(this);
    BufferDC.SetBrush(*wxTRANSPARENT_BRUSH);
    BufferDC.Clear();
    wxGraphicsContext *gc = wxGraphicsContext::Create(BufferDC);
    if (gc) {
      gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);
      gc->DrawBitmap(m_bmp, 0, 0, m_bmp.GetWidth(), m_bmp.GetHeight());
      delete gc;
    }
  } while (0);
#endif
#if 0
  // 使用双缓冲设备上下文
  wxBufferedPaintDC dc(this);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  // 清除背景为透明
  dc.Clear(); // 清除背景，防止出现灰色或黑色背景

  // 获取图形上下文对象
  wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

  if (gc) {
    // 设置透明背景
    gc->SetBrush(*wxTRANSPARENT_BRUSH);
    gc->SetPen(*wxTRANSPARENT_PEN);

    gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);
    gc->DrawBitmap(m_bmp, 0, 0, m_bmp.GetWidth(), m_bmp.GetHeight());

    // 获取窗口大小
    wxSize size = GetClientSize();
    float width = size.GetWidth();
    float height = size.GetHeight();
    float radius = 30.0f; // 圆角半径

    // 创建圆角矩形路径
    wxGraphicsPath path = gc->CreatePath();
    path.AddRoundedRectangle(0, 0, width, height, radius);

    // 填充圆角矩形背景
    gc->FillPath(path);

    // 设置红色边框
    gc->SetPen(wxPen(*wxRED, 5)); // 红色边框，宽度5
    gc->StrokePath(path);

    delete gc;
  }

  // 在窗口上设置形状为圆角矩形
  // SetWindowShape();
  SetShape();
#endif

#if 0
  wxBufferedPaintDC dc(this);
  dc.SetBrush(*wxTRANSPARENT_BRUSH); // 使用透明背景
  dc.Clear();                        // 清除背景

  wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
  if (gc) {
    // 启用抗锯齿
    gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

    // 设置绘制的红色边框
    gc->SetPen(wxPen(wxColour(255, 0, 0), 2));
    gc->DrawRectangle(10, 10, 200,
                      150); // 绘制矩形（可以根据需要调整位置和尺寸）

    delete gc;
  }
#endif
  wxBufferedPaintDC dc(this);
  dc.SetBrush(*wxTRANSPARENT_BRUSH); // 使用透明背景
  dc.Clear();                        // 清除背景

  SetShape(dc);
  wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
  if (gc) {
    // 启用抗锯齿
    gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);

    // 设置绘制的红色边框
    gc->SetPen(wxPen(wxColour(255, 0, 0), 2)); // 红色边框，宽度 2
    gc->StrokePath(m_shapePath);               // 使用保存的路径来绘制边框

    delete gc; // 绘制完成后删除 wxGraphicsContext
  }
}

#if 0
wxBEGIN_EVENT_TABLE(Frame, wxFrame) EVT_PAINT(Frame::OnPaint)
    EVT_SIZE(Frame::OnSize) EVT_ERASE_BACKGROUND(Frame::OnErase)
        wxEND_EVENT_TABLE()
    class Frame : public wxFrame {
public:
  Frame(wxWindow *)
      : wxFrame(nullptr, wxID_ANY, "圆角矩形 Frame", wxDefaultPosition,
                wxSize(400, 300), wxNO_BORDER | wxFRAME_SHAPED) {
    // 设置背景颜色
    SetBackgroundStyle(wxBG_STYLE_PAINT);
  }

  void OnErase(wxEraseEvent &event) {
  }
  void OnPaint(wxPaintEvent &event) {
    // 使用双缓冲设备上下文
    wxBufferedPaintDC dc(this);

    // 清除背景为透明
    dc.Clear(); // 清除背景，防止出现灰色或黑色背景

    // 获取图形上下文对象
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc) {
      // 设置透明背景
      gc->SetBrush(*wxTRANSPARENT_BRUSH);
      gc->SetPen(*wxTRANSPARENT_PEN);

      // 获取窗口大小
      wxSize size = GetClientSize();
      float width = size.GetWidth();
      float height = size.GetHeight();
      float radius = 30.0f; // 圆角半径

      // 创建圆角矩形路径
      wxGraphicsPath path = gc->CreatePath();
      path.AddRoundedRectangle(0, 0, width, height, radius);

      // 填充圆角矩形背景
      gc->FillPath(path);

      // 设置红色边框
      gc->SetPen(wxPen(*wxRED, 5)); // 红色边框，宽度5
      gc->StrokePath(path);

      delete gc;
    }

    // 在窗口上设置形状为圆角矩形
    SetWindowShape();
  }

  void SetWindowShape() {
    // 创建一个带透明背景的 wxBitmap
    wxSize size = GetClientSize();
    wxBitmap bmp;
    bmp.Create(size.GetWidth(), size.GetHeight(), 32);
    // 使用 wxGraphicsContext 绘制圆角矩形到 bmp 上
    wxMemoryDC memDC(bmp);
    wxGraphicsContext *gc = wxGraphicsContext::Create(memDC);

    if (gc) {
      // 设置透明背景
      gc->SetBrush(*wxTRANSPARENT_BRUSH);
      gc->SetPen(*wxTRANSPARENT_PEN);

      // 获取窗口大小
      float width = size.GetWidth();
      float height = size.GetHeight();
      float radius = 30.0f; // 圆角半径

      // 创建圆角矩形路径
      wxGraphicsPath path = gc->CreatePath();
      path.AddRoundedRectangle(0, 0, width, height, radius);

      // 填充背景
      gc->FillPath(path);

      delete gc;
    }

    // 将 wxBitmap 转换为 wxImage
    wxImage img = bmp.ConvertToImage();

    // 转换 alpha 通道为掩码
    if (img.HasAlpha()) {
      img.ConvertAlphaToMask(); // 将透明区域转换为掩码
    }

    // 使用掩码创建 wxRegion 并设置窗口形状
    SetShape(wxRegion(img)); // 使用 wxRegion 来设置窗口的形状
  }

  void OnSize(wxSizeEvent &event) {
    Refresh(); // 尺寸改变时刷新窗口
    event.Skip();
  }

private:
  wxDECLARE_EVENT_TABLE();
};
#endif
#if 0
Frame::Frame(wxWindow *parent, wxWindowID id, const wxString &title,
             const wxPoint &pos, const wxSize &size, long style,
             const wxString &name)
    : IBackground(parent, id, title, pos, size, style, name) {
  is_allow_move_.store(true);
  //  SetBackgroundColour(wxColour(183, 110, 121));
  //			// Color color(20, 255, 215, 0);//!@ 土豪金
  // SetBackgroundColour(wxColour(183, 110, 121));
  // SetTransparent(50);
  SetBackgroundColour(wxColour(183, 110, 121));
  SetTransparent(20);
#if 0
  wxImage *image = Global::Get()->GetResImage(u"test.png");
  m_bmp = wxBitmap(*image);
  int width = image->GetWidth();
  int height = image->GetHeight();
  SetSize(wxSize(width, height));
  SetShape(*image);
  // SetBackgroundColour(wxColour(255, 0, 0, wxALPHA_OPAQUE));
  // SetBackgroundColour(wxColour(0, 0, 0, 0));
  Layout();
  Refresh();
#endif
}
Frame::~Frame() {
}
#endif
#endif