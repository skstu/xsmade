#include <wxui.h>

FrameScreenShot::WorkSpace::TextInputCtrl::TextInputCtrl(
    const wxBitmap &bgnImg, wxWindow *parent, const wxPoint &pos,
    const wxSize &size, const wxString &value, wxWindowID id, long style)
    : wxRichTextCtrl(parent, id, value, pos, size, style),
      background_src_(bgnImg), background_dest_(bgnImg) {
  Bind(wxEVT_PAINT, &FrameScreenShot::WorkSpace::TextInputCtrl::OnPaint, this);
  Bind(wxEVT_TEXT, &FrameScreenShot::WorkSpace::TextInputCtrl::OnTextChanged,
       this);
  Bind(wxEVT_MOUSE_CAPTURE_LOST,
       &FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseCaptureLost, this);
  Bind(wxEVT_MOVE, &FrameScreenShot::WorkSpace::TextInputCtrl::OnMove, this);
  Bind(wxEVT_MOTION, &FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseMove,
       this);
  Bind(wxEVT_LEFT_DOWN,
       &FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseLeftDown, this);
  Bind(wxEVT_LEFT_UP, &FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseLeftUp,
       this);
  SetBackgroundStyle(wxBG_STYLE_CUSTOM);
  ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
  // wxClientDC dc(this);
  // dc.SetFont(Global::Get()->GetScreenShotDrawTextFont());
  // dc.GetTextExtent("a", &text_width_, &text_height_);

  // SetSize(background_src_.GetSize());
  // SetSize(text_width_, text_width_);
  wxSize fontSize = Global::Get()->GetScreenShotDrawTextFont().GetPixelSize();
  // SetSize(20, fontSize.GetHeight());
  SetSize(50, fontSize.GetHeight() * 1);
  SetInsertionPointEnd();
  // SetInsertionPoint();
  //  SetCustomCaret();
  SetFocus();
}
FrameScreenShot::WorkSpace::TextInputCtrl::~TextInputCtrl() {
  Unbind(wxEVT_PAINT, &FrameScreenShot::WorkSpace::TextInputCtrl::OnPaint,
         this);
  Unbind(wxEVT_TEXT, &FrameScreenShot::WorkSpace::TextInputCtrl::OnTextChanged,
         this);
  Unbind(wxEVT_MOUSE_CAPTURE_LOST,
         &FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseCaptureLost, this);
  Unbind(wxEVT_MOVE, &FrameScreenShot::WorkSpace::TextInputCtrl::OnMove, this);
  Unbind(wxEVT_MOTION, &FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseMove,
         this);
  Unbind(wxEVT_LEFT_DOWN,
         &FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseLeftDown, this);
  Unbind(wxEVT_LEFT_UP,
         &FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseLeftUp, this);
}
bool FrameScreenShot::WorkSpace::TextInputCtrl::IsTextEmtpy() const {
  return GetValue().IsEmpty();
}
void FrameScreenShot::WorkSpace::TextInputCtrl::SetCustomCaret() {
  wxClientDC dc(this);
  dc.SetFont(GetFont());
  wxCoord charWidth(0), charHeight(0);
  dc.GetTextExtent("A", &charWidth, &charHeight);

  // 设置光标为红色 2px 宽
  wxCaret *caret = GetCaret();
  if (!caret) {
    caret = new wxCaret(this, 2, charHeight); // 宽度 2px，高度根据字体设置
    SetCaret(caret);
  }
  wxWindow *caretWindow = caret->GetWindow();
  caretWindow->SetBackgroundColour(wxColour(255, 0, 0));
  caret->SetSize(2, charHeight); // 确保光标大小正确
  caret->Hide();                 // 显示光标

#if 0
wxCaret* caret = richTextCtrl->GetCaret();
if (caret) {
    caret->Hide();
}
#endif
}
void FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseCaptureLost(
    wxMouseCaptureLostEvent &evt) {
  evt.Skip();
}
void FrameScreenShot::WorkSpace::TextInputCtrl::OnBackgroundUpdate() {
  wxRect rect = GetRect();
  if (rect.x < 0)
    rect.SetLeft(0);
  if (rect.y < 0)
    rect.SetTop(0);

  if (rect.x + rect.width > background_src_.GetWidth())
    rect.SetWidth(rect.width -
                  ((rect.x + rect.width) - background_src_.GetWidth()));
  if (rect.y + rect.height > background_src_.GetHeight())
    rect.SetHeight(rect.height -
                   ((rect.y + rect.height) - background_src_.GetHeight()));
  if (!((rect.x >= 0) && (rect.y >= 0) &&
        (rect.x + rect.width <= background_src_.GetWidth()) &&
        (rect.y + rect.height <= background_src_.GetHeight())))
    return;
  background_dest_ = background_src_.GetSubBitmap(rect);
  Refresh();
}
void FrameScreenShot::WorkSpace::TextInputCtrl::OnSize(wxSizeEvent &evt) {
  OnBackgroundUpdate();
  evt.Skip();
}
void FrameScreenShot::WorkSpace::TextInputCtrl::OnMove(wxMoveEvent &evt) {
  OnBackgroundUpdate();
  evt.Skip();
}
void FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseMove(wxMouseEvent &evt) {
  wxPoint pt = evt.GetPosition();
  int desk_x(0), desk_y(0);
  wxGetMousePosition(&desk_x, &desk_y);
  if (evt.Dragging() && evt.LeftIsDown()) {
    do {
      if (!is_allow_move_.load())
        break;
      is_dragging_.store(true);
      wxPoint pos = ClientToScreen(pt); // pos为点击位置
      Move(wxPoint(pos.x - mouse_left_down_point_.x,
                   pos.y - mouse_left_down_point_.y));
    } while (0);
  }
}
void FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseLeftDown(
    wxMouseEvent &evt) {
  do {
    if (!HasCapture()) {
      CaptureMouse();
      SetCursor(wxCursor(wxCURSOR_SIZING));
    }
    wxPoint pt = ClientToScreen(evt.GetPosition());
    wxPoint origin = GetPosition();
    int dx = pt.x - origin.x;
    int dy = pt.y - origin.y;
    mouse_left_down_point_ = wxPoint(dx, dy);
    mouse_left_down_rect_ = GetRect();
  } while (0);
}
void FrameScreenShot::WorkSpace::TextInputCtrl::OnMouseLeftUp(
    wxMouseEvent &evt) {
  if (HasCapture()) {
    SetFocus();
    SetCursor(wxCursor(wxCURSOR_ARROW));
    ReleaseMouse();
    // 获取鼠标点击位置（相对于控件的客户区坐标）
    wxPoint clickPt = evt.GetPosition();
    // 转换鼠标位置到文本插入点
    long pos = -1;
    wxTextCoord col, row;
    if (HitTest(clickPt, &col, &row)) {
      pos = XYToPosition(col, row); // 根据行列转换为插入点
    }
    if (pos != -1) {
      SetInsertionPoint(pos); // 设置文本插入点
    }
  }
  is_dragging_.store(false);
}

void FrameScreenShot::WorkSpace::TextInputCtrl::OnEraseBackground(
    wxEraseEvent &evt) {
}
void FrameScreenShot::WorkSpace::TextInputCtrl::OnTextChanged(
    wxCommandEvent &evt) {
  // 使用客户端设备上下文计算文本的尺寸
  wxClientDC dc(this);
  dc.SetFont(Global::Get()->GetScreenShotDrawTextFont());
  // 获取控件的文本
  wxString text = GetValue();
  wxSize textSize = dc.GetMultiLineTextExtent(text);

  wxArrayString lines = wxSplit(text, '\n', '\0');
  size_t lineCount = lines.GetCount();

  int new_text_width = 0;
  int new_text_height = 0;
  for (size_t i = 0; i < lineCount; i++) {
    wxSize lineSize = dc.GetTextExtent(lines[i]);
    new_text_width = wxMax(new_text_width, lineSize.GetWidth());
    new_text_height += lineSize.GetHeight();
  }
  // SetInsertionPoint(textSize.GetWidth());
  // SetCaretPosition(new_text_width);
  // SetInsertionPointEnd();
  // 获取光标位置（字符位置）
  long cursorPos = GetInsertionPoint(); // 获取当前光标位置

  // 获取光标前文本的宽度
  dc.SetFont(GetFont());
  wxCoord x, y;
  dc.GetTextExtent(text.Left(cursorPos), &x, &y); // 获取光标前的文本宽度

  // 确保光标位置正确
  // SetInsertionPoint(cursorPos); // 确保光标位置正确

  textSize.SetWidth(new_text_width + 10);
  textSize.SetHeight(new_text_height);
  if (textSize != GetSize()) {
    SetSize(textSize);
  }

  // long pos = -1;
  // wxTextCoord col, row;
  // GetCaretPosition();
  // wxPoint clickPt = ScreenToClient(wxGetMousePosition());
  // if (HitTest(clickPt, &col, &row)) {
  //   pos = XYToPosition(col, row); // 根据行列转换为插入点
  // }
  // if (pos != -1) {
  //   SetInsertionPoint(pos); // 设置文本插入点
  // }

  // SetCaretPos(30, 3);
  GetCaret()->Hide();
  Refresh();
}
// 处理绘制事件
void FrameScreenShot::WorkSpace::TextInputCtrl::OnPaint(wxPaintEvent &evt) {
  wxPaintDC dc(this);
  do {
    if (!background_dest_.IsOk())
      break;
    const wxRect clientRect = GetClientRect();
    // wxBitmap bgnImg =
    //     backgroundBitmap_; //.GetSubBitmap(wxRect(0, 0, 100, 200));
    // dc.DrawBitmap(background_src_, 0, 0, true);
    dc.DrawBitmap(background_dest_, 0, 0, true);
    // 设置字体和文本颜色
    // wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
    //              wxFONTWEIGHT_NORMAL);
    dc.SetFont(Global::Get()->GetScreenShotDrawTextFont());
    dc.SetTextForeground(*wxRED); // 设置文本颜色

    // 获取控件文本并绘制
    wxString text = GetValue();
    wxCoord font_x, font_y;
    dc.GetTextExtent(wxT(" "), &font_x, &font_y);
    wxSize textSize = dc.GetTextExtent(text);

    // 计算文本位置并绘制
    // int textX = 5;
    // int textY = (GetClientSize().y - textSize.y) / 2; // 垂直居中
    dc.DrawText(text, 0, 0);

    //!@ 设置光标
    // SetInsertionPointEnd();
    // SetCaretPos(textSize.x, textSize.y - font_y);
    // SetCaretPosition(textSize.GetWidth() + 1);
    // SetInsertionPoint(textSize.GetWidth() + 1);
    //!@ 画边框
#if 1
    wxPen pen(*wxRED, 2, wxPENSTYLE_SOLID);
    dc.SetPen(pen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(clientRect.x, clientRect.y, clientRect.width + 1,
                     clientRect.height + 1);
#endif
  } while (0);

#if 0
  do {
    // 获取插入点位置
    long pos = GetInsertionPoint();
    wxRichTextBuffer &buffer = GetBuffer();
    if (!buffer.IsEmpty())
      break;

    // 获取控件的内容
    wxString text = GetValue();

    wxPoint caretPos;
    if (text.IsEmpty()) {
      // 如果没有输入文本，将光标绘制在起始位置
      wxCoord charHeight = GetCharHeight();
      caretPos = wxPoint(2, 2); // 默认偏移量（2像素边距）
    } else {
      // 获取光标的像素位置
      wxRichTextDrawingContext context(&buffer);
      if (!buffer.GetCaretPositionForCharacter(pos, caretPos, &context)) {
        break; // 无法获取位置时直接返回
      }
      buffer.getca
    }

    // 绘制红色光标
    dc.SetPen(wxPen(wxColour(255, 0, 0), 2)); // 红色，2px
    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawRectangle(caretPos.x, caretPos.y, 2, GetCharHeight());
  } while (0);
#endif
}

#if 0
FrameScreenShot::WorkSpace::TextInputCtrl::TextInputCtrl(
    wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos,
    const wxSize &size, long style)
    : wxRichTextCtrl(parent, id, value, pos, size,
                     wxTE_MULTILINE | wxBORDER_NONE) {
  Bind(wxEVT_PAINT, &FrameScreenShot::WorkSpace::TextInputCtrl::OnPaint, this);
  Bind(wxEVT_TEXT, &FrameScreenShot::WorkSpace::TextInputCtrl::OnTextChanged,
       this);
  SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}
FrameScreenShot::WorkSpace::TextInputCtrl::~TextInputCtrl() {
  Unbind(wxEVT_PAINT, &FrameScreenShot::WorkSpace::TextInputCtrl::OnPaint,
         this);
  Unbind(wxEVT_TEXT, &FrameScreenShot::WorkSpace::TextInputCtrl::OnTextChanged,
         this);
}

// 设置背景图片
void FrameScreenShot::WorkSpace::TextInputCtrl::SetBackgroundBitmap(
    wxImage *image) {
  if (image && image->IsOk()) {
    // 设置控件大小为图片大小
    SetSize(image->GetSize());
    SK_DELETE_PTR(backgroundBitmap_);
    backgroundBitmap_ = new wxBitmap(*image);
    Refresh();
    Update();
  }
}

void FrameScreenShot::WorkSpace::TextInputCtrl::OnTextChanged(
    wxCommandEvent &event) {

  // 在文本更改时，刷新界面
  Refresh();
}

// 处理绘制事件
void FrameScreenShot::WorkSpace::TextInputCtrl::OnPaint(wxPaintEvent &evt) {
  wxPaintDC dc(this);

  // 绘制背景图片，如果有的话
  if (backgroundBitmap_ && backgroundBitmap_->IsOk()) {
    dc.DrawBitmap(*backgroundBitmap_, 0, 0, true);
  }

  // 设置字体和文本颜色
  wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
              wxFONTWEIGHT_NORMAL);
  dc.SetFont(font);
  dc.SetTextForeground(*wxRED); // 设置文本颜色

  // 获取控件文本并绘制
  wxString text = GetValue();
  wxSize textSize = dc.GetTextExtent(text);

  // 计算文本位置并绘制
  // int textX = 5;
  // int textY = (GetClientSize().y - textSize.y) / 2; // 垂直居中
  dc.DrawText(text, 20, 0);
}
#endif