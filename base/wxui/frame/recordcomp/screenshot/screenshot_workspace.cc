#include <wxui.h>
FrameScreenShot::WorkSpace::WorkSpace(wxWindow *parent, wxWindowID id,
                                      const wxString &title, const wxPoint &pos,
                                      const wxSize &size, long style,
                                      const wxString &name)
    : IWorkSpace(parent, id, title, pos, size,
                 wxFRAME_SHAPED | wxNO_BORDER | wxFRAME_NO_TASKBAR |
                     wxTE_NO_VSCROLL,
                 name) {
  // SetBackgroundColour(wxColour(183, 110, 121));
  // Color color(20, 255, 215, 0);//!@ 土豪金
  is_allow_move_.store(true);
  // SetBackgroundColour(wxColour(183, 110, 121));
  SetTransparent(255);
  wxEvtHandler::Bind(wxEVT_NotifyType,
                     &FrameScreenShot::WorkSpace::OnDrawToolbar, this);
  //  wxEvtHandler::Bind(wxEVT_NotifyType,
  //                     &FrameScreenShot::WorkSpace::OnScreenShot, this);
}
FrameScreenShot::WorkSpace::~WorkSpace() {
  wxEvtHandler::Unbind(wxEVT_NotifyType,
                       &FrameScreenShot::WorkSpace::OnDrawToolbar, this);
  //  wxEvtHandler::Unbind(wxEVT_NotifyType,
  //                       &FrameScreenShot::WorkSpace::OnScreenShot, this);
}
void FrameScreenShot::WorkSpace::OnMouseMove(wxMouseEvent &event) {
  do {
    if (OnUserDraw(event))
      break;
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
                 pos.y >=
                     (clientSize.GetHeight() - border_width_)) { //!@ 右下角
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
  } while (0);
}
void FrameScreenShot::WorkSpace::OnMove(wxMoveEvent &evt) {
  // evt.SetPosition(wxGetMousePosition());
  OnWorkSpaceSizeChanged(GetRect());
  evt.Skip();
}
void FrameScreenShot::WorkSpace::OnScreenShot(wxCommandEvent &event) {
  do {
    // if (event.GetInt() != GetId())
    //   break;
    DrawSave();
    if (draw_success_cache_.empty()) {
      break;
    }
    auto wxImg = *draw_success_cache_.back();
    if (!wxImg) {
      break;
    }
    std::string imgStream;
    if (!wxComm::GetImgStream(wxImg, imgStream)) {
      break;
    }
    if (imgStream.empty()) {
      break;
    }
    stl::File::WriteFile(Config::Get()->GetScreecshotCachePath(), imgStream);
    //     std::string imgStream = wxComm::SaveImgToStream(wxImg);
    // wxComm::LoadImg(const std::string &imgPath, wxImage **outputImg) if
    // (cache)
    //     draw_success_cache_.push_back(const_cast<wxImage *>(image));

    wxMessageBox(wxT("截图成功!"), wxT("提示"), wxOK | wxICON_INFORMATION);
  } while (0);
}
void FrameScreenShot::WorkSpace::OnMouseLeftDown(wxMouseEvent &event) {
  do {
    if (OnUserDraw(event))
      break;
    if (!HasCapture()) {
      CaptureMouse();
    }
    wxPoint pt = ClientToScreen(event.GetPosition());
    wxPoint origin = GetPosition();
    int dx = pt.x - origin.x;
    int dy = pt.y - origin.y;
    mouse_left_down_point_ = wxPoint(dx, dy);
    mouse_left_down_rect_ = GetRect();
  } while (0);
}
void FrameScreenShot::WorkSpace::OnMouseLeftUp(wxMouseEvent &event) {
  do {
    if (OnUserDraw(event))
      break;
    if (HasCapture()) {
      ReleaseMouse();
    }
    is_dragging_.store(false);
  } while (0);
}
void FrameScreenShot::WorkSpace::OnWorkSpaceSizeChanged(const wxRect &rect) {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    IFrameComponent *frame_screenshot =
        app->FrameComponentGet(FrameComponentType::SCREENSHOT);
    if (!frame_screenshot)
      break;
    frame_screenshot->OnWorkspacePosUpdate(rect);
  } while (0);
}
void FrameScreenShot::WorkSpace::OnSize(wxSizeEvent &event) {
  Refresh();
  OnWorkSpaceSizeChanged(GetRect());
  event.Skip();
}
void FrameScreenShot::WorkSpace::OnEraseBackground(wxEraseEvent &event) {
  event.Skip();
}
void FrameScreenShot::WorkSpace::OnPaint(wxPaintEvent &evt) {
  do {
    if (!backgroundBitmap_)
      break;
    if (!backgroundBitmap_->IsOk()) {
      SK_DELETE_PTR(backgroundBitmap_);
      break;
    }
    wxPaintDC dc(dynamic_cast<wxWindow *>(this));

    dc.DrawBitmap(*backgroundBitmap_, 0, 0, true);
    wxPen pen(*wxRED, 3, wxPENSTYLE_SOLID);
    dc.SetPen(pen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(GetClientRect());

    draw_cache_.iterate(
        [](std::tuple<CommandTool, std::vector<wxPoint>> &node) {
          const CommandTool type = std::get<0>(node);
          const std::vector<wxPoint> points = std::get<1>(node);
          switch (type) {
          case CommandTool::TOOL_SCREENSHOT_ROUND: {
            if (points.empty())
              break;
          } break;
          case CommandTool::TOOL_SCREENSHOT_RECTANGLE: {
            if (points.size() < 2)
              break;

            auto asss = 0;
          } break;
          case CommandTool::TOOL_SCREENSHOT_ARROW: {

          } break;
          default:
            break;
          }
        });
  } while (0);

  evt.Skip();
}
void FrameScreenShot::WorkSpace::DrawSave() {
  wxRect window = GetRect();
  xs_image_stream_t *image_stream = nullptr;
  xs_sys_capturescreen(
      xs_position_t{window.x, window.y, window.width, window.height},
      xs_image_stream_type_t::PNG, &image_stream);
  wxImage *wximg = nullptr;
  wxComm::LoadImgFormStream(
      std::string(image_stream->buffer, image_stream->len), &wximg);
  xs_sys_image_stream_destroy(&image_stream);
  SetImage(wximg);
}

bool FrameScreenShot::WorkSpace::OnUserDraw(const wxMouseEvent &evt) {
  bool result = true;
  switch (draw_mode_.load()) {
  case CommandTool::TOOL_SCREENSHOT_TEXT: {
    if (evt.LeftDown()) {
      if (!HasCapture()) {
        CaptureMouse();
        // 获取鼠标点击位置，作为文本输入的起始点
        wxPoint start_text_position_ = evt.GetPosition();
        draw_text_cache_.iterate([](TextInputCtrl *ctrl, bool &clear) {
          ctrl->Show(false);
          if (ctrl->IsTextEmtpy()) {
            ctrl->Close();
            SK_DELETE_PTR(ctrl);
            clear = true;
          }
        });
        auto text_input_ctrl = new TextInputCtrl(
            *backgroundBitmap_, this,
            wxPoint(start_text_position_.x, start_text_position_.y));
        draw_text_cache_.push_back(text_input_ctrl);
      }
    } else if (evt.LeftUp()) {
      if (HasCapture()) {
        ReleaseMouse();
        DrawSave();
        overlay_.Reset();
      }
    } else if (evt.Dragging()) {
#if 0
      // 画图逻辑（假设您还想在鼠标拖动时绘制一些东西）
      draw_arbitrary_cache_.push_back(evt.GetPosition());
      wxOverlayDC dc(overlay_, this);
      PrepareDC(dc);
      dc.Clear();

      // 设置画笔和画刷
      dc.SetPen(wxPen(*wxRED, 1));  // 红色画笔
      dc.SetBrush(wxBrush(*wxRED)); // 红色填充
      draw_arbitrary_cache_.iterate(
          [&](wxPoint &pt) { dc.DrawPoint(pt.x, pt.y); });
#endif
    }
  } break;
  case CommandTool::TOOL_SCREENSHOT_ROUND: {
    if (evt.LeftDown()) {
      if (!HasCapture()) {
        CaptureMouse();
        draw_point_begin_ = evt.GetPosition();
      }
    } else if (evt.LeftUp()) {
      if (HasCapture()) {
        ReleaseMouse();
        draw_point_end_ = evt.GetPosition();
        DrawSave();
        overlay_.Reset();
      }
    } else if (evt.Dragging()) {
      wxPoint draw_point_current_ = evt.GetPosition();
      int x1 = draw_point_begin_.x, y1 = draw_point_begin_.y;
      int x2 = draw_point_current_.x, y2 = draw_point_current_.y;

#if 0 //!@ 画圆
      // 计算圆心坐标
      int center_x = (x1 + x2) / 2;
      int center_y = (y1 + y2) / 2;

      // 计算半径
      double radius =
          std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)) / 2;

      wxOverlayDC dc(overlay_, this);
      PrepareDC(dc);
      dc.Clear();

      dc.SetPen(*wxRED_PEN);             // 设置红色画笔
      dc.SetBrush(*wxTRANSPARENT_BRUSH); // 设置透明画刷
      dc.DrawCircle(center_x, center_y, static_cast<int>(radius)); // 绘制圆
#else //!@ 画椭圆
      // 计算椭圆的中心坐标
      int center_x = (x1 + x2) / 2;
      int center_y = (y1 + y2) / 2;
      // 计算椭圆的宽度和高度
      int width = std::abs(x2 - x1);
      int height = std::abs(y2 - y1);

      // 计算椭圆的左上角坐标
      int left = center_x - width / 2;
      int top = center_y - height / 2;

      wxOverlayDC dc(overlay_, this);
      PrepareDC(dc);
      dc.Clear();
      // 使用 DrawEllipse 绘制椭圆
      dc.SetPen(*wxRED_PEN);                    // 设置红色画笔
      dc.SetBrush(*wxTRANSPARENT_BRUSH);        // 设置透明画刷
      dc.DrawEllipse(left, top, width, height); // 绘制椭圆
#endif
    }
  } break;
  case CommandTool::TOOL_SCREENSHOT_RECTANGLE: {
    if (evt.LeftDown()) {
      if (!HasCapture()) {
        CaptureMouse();
        draw_point_begin_ = evt.GetPosition();
      }
    } else if (evt.LeftUp()) {
      if (HasCapture()) {
        ReleaseMouse();
        draw_point_end_ = evt.GetPosition();
        DrawSave();
        overlay_.Reset();
      }
    } else if (evt.Dragging()) {
      wxPoint draw_point_current_ = evt.GetPosition();

      int x1 = draw_point_begin_.x, y1 = draw_point_begin_.y;
      int x2 = draw_point_current_.x, y2 = draw_point_current_.y;

      int left = std::min(x1, x2);
      int top = std::min(y1, y2);
      int width = std::abs(x2 - x1);
      int height = std::abs(y2 - y1);

      wxOverlayDC dc(overlay_, this);
      PrepareDC(dc);
      dc.Clear();
      dc.SetPen(wxPen(*wxRED, 1));
      dc.SetBrush(*wxTRANSPARENT_BRUSH);
      dc.DrawRectangle(left, top, width, height);
    }
  } break;
  case CommandTool::TOOL_SCREENSHOT_ARROW: {
    if (evt.LeftDown()) {
      if (!HasCapture()) {
        CaptureMouse();
        draw_point_begin_ = evt.GetPosition();
      }
    } else if (evt.LeftUp()) {
      if (HasCapture()) {
        ReleaseMouse();
        draw_point_end_ = evt.GetPosition();
        DrawSave();
        overlay_.Reset();
      }
    } else if (evt.Dragging()) {
      wxPoint draw_point_current_ = evt.GetPosition(); // 当前鼠标位置

      // 计算箭头的方向和头部的两个小线段
      double angle = std::atan2(draw_point_current_.y - draw_point_begin_.y,
                                draw_point_current_.x - draw_point_begin_.x);

      // 箭头头部的大小
      double arrowSize = 20;

      // 箭头的两个小线段的端点
      wxPoint arrow1(
          draw_point_current_.x -
              static_cast<int>(arrowSize * std::cos(angle - M_PI / 6)),
          draw_point_current_.y -
              static_cast<int>(arrowSize * std::sin(angle - M_PI / 6)));
      wxPoint arrow2(
          draw_point_current_.x -
              static_cast<int>(arrowSize * std::cos(angle + M_PI / 6)),
          draw_point_current_.y -
              static_cast<int>(arrowSize * std::sin(angle + M_PI / 6)));

      // 绘制箭头
      wxOverlayDC dc(overlay_, this);
      PrepareDC(dc);
      dc.Clear();

      // 设置画笔和画刷
      dc.SetPen(wxPen(*wxRED, 1));  // 红色画笔
      dc.SetBrush(wxBrush(*wxRED)); // 红色填充

      // 绘制箭头的直线部分
      dc.DrawLine(draw_point_begin_, draw_point_current_);

      // 绘制箭头的头部（三角形）
      wxPoint arrowPoints[3] = {draw_point_current_, arrow1, arrow2};
      dc.DrawPolygon(3, arrowPoints); // 绘制一个三角形
    }
  } break;
  case CommandTool::TOOL_SCREENSHOT_EIDT: { //!@ brush
    if (evt.LeftDown()) {
      if (!HasCapture()) {
        CaptureMouse();
        draw_arbitrary_cache_.clear();
        draw_arbitrary_cache_.push_back(evt.GetPosition());
      }
    } else if (evt.LeftUp()) {
      if (HasCapture()) {
        ReleaseMouse();
        draw_arbitrary_cache_.push_back(evt.GetPosition());
        DrawSave();
        overlay_.Reset();
        draw_arbitrary_cache_.clear();
      }
    }
    // else if (evt.Moving()) {
    // }
    else if (evt.Dragging()) {
      draw_arbitrary_cache_.push_back(evt.GetPosition());
      wxOverlayDC dc(overlay_, this);
      PrepareDC(dc);
      dc.Clear();

      // 设置画笔和画刷 [点线]
      dc.SetPen(wxPen(*wxRED, 1));  // 红色画笔
      dc.SetBrush(wxBrush(*wxRED)); // 红色填充
      draw_arbitrary_cache_.iterate(
          [&](wxPoint &pt) { dc.DrawPoint(pt.x, pt.y); });
    }
  } break;
  case CommandTool::TOOL_SCREENSHOT_MOSAIC: {
    if (evt.LeftDown()) {
      if (!HasCapture()) {
        CaptureMouse();
        draw_mosaic_cache_.clear();
        draw_mosaic_cache_.push_back(evt.GetPosition());
      }
    } else if (evt.LeftUp()) {
      if (HasCapture()) {
        ReleaseMouse();
        draw_mosaic_cache_.push_back(evt.GetPosition());
        DrawSave();
        overlay_.Reset();
        draw_mosaic_cache_.clear();
      }
    } else if (evt.Dragging()) {
      // 在拖动时记录位置
      draw_mosaic_cache_.push_back(evt.GetPosition());

      // 使用 overlay 绘制
      wxOverlayDC dc(overlay_, this);
      PrepareDC(dc);
      dc.Clear();

      // 设置画笔和画刷 [点线]
      // dc.SetPen(wxPen(*wxRED, 1));  // 红色画笔
      // dc.SetBrush(wxBrush(*wxRED)); // 红色填充

      dc.SetBrush(*wxTRANSPARENT_BRUSH);
      auto img =
          Config::Get()->GetResImage("btn_screenshot_toolbar_mosaic.png");
      wxBitmap mosaicBitmap(*img);
      // 遍历保存的点，绘制马赛克
      draw_mosaic_cache_.iterate([&](wxPoint &pt) {
        // 将鼠标拖动路径绘制成圆形区域
        // 这里绘制的是以pt为中心的圆形区域
        dc.DrawCircle(pt.x, pt.y, 10); // 画出圆形区域

        // // 将准备好的马赛克图片绘制到该区域
        // // 假设您已经准备好了一张马赛克图片 mosaic_image_
        // wxBitmap mosaicBitmap(*img); // 加载马赛克图像
        // 在圆形区域内填充马赛克图片
        wxRect drawRect(pt.x - 10, pt.y - 10, 20,
                        20); // 绘制区域，圆形的直径是 20
        dc.DrawBitmap(mosaicBitmap, drawRect.x, drawRect.y, true);
      });
    }
  } break;
  default:
    result = false;
    break;
  }
  // draw_mode_.store(CommandTool::TOOL_NULL);
  return result;
}
void FrameScreenShot::WorkSpace::OnDrawToolbar(wxCommandEvent &evt) {
  if (NotifyEventID::EVT_NOTIFY_DRAWTOOL_SCREENSHOT ==
      NotifyEventID(evt.GetId())) {
    OnScreenShot(evt);
  } else if (NotifyEventID::EVT_NOTIFY_DRAWTOOL_ACTIVATE ==
             NotifyEventID(evt.GetId())) {
    draw_mode_.store(CommandTool(evt.GetInt()));
    switch (draw_mode_.load()) {
    case CommandTool::TOOL_SCREENSHOT_ARROW: {
      SetCursor(wxCursor(wxCURSOR_RIGHT_ARROW));
    } break;
    case CommandTool::TOOL_SCREENSHOT_ROUND: {
      SetCursor(wxCursor(wxCURSOR_CROSS));
    } break;
    case CommandTool::TOOL_SCREENSHOT_RECTANGLE: {
      SetCursor(wxCursor(wxCURSOR_CROSS));
    } break;
    case CommandTool::TOOL_SCREENSHOT_MOSAIC: {
      auto img = Config::Get()->GetResImage("mouse_mosaic.png");
      if (!img) {
        SetCursor(wxCursor(wxCURSOR_PAINT_BRUSH));
        break;
      }
      img->Rescale(20, 20);
      SetCursor(wxCursor(*img));
    } break;
    case CommandTool::TOOL_SCREENSHOT_CLOSE: {

      auto ss = 0;
    } break;
    case CommandTool::TOOL_SCREENSHOT_REVOCATION: {
      if (draw_success_cache_.size() <= 1) {
        SetImage(*draw_success_cache_.back(), false);
      } else {
        draw_success_cache_.pop_back();
        SetImage(*draw_success_cache_.back(), false);
      }
    } break;
    case CommandTool::TOOL_SCREENSHOT_OK: {

      auto ss = 0;
    } break;
    case CommandTool::TOOL_SCREENSHOT_TEXT: {
      SetCursor(wxCursor(wxCURSOR_IBEAM));
    } break;
    case CommandTool::TOOL_SCREENSHOT_EIDT: {
      SetCursor(wxCursor(wxCURSOR_PENCIL));
    } break;
    default: {
      SetCursor(wxCursor(wxCURSOR_ARROW));
    } break;
    }
  }
}
void FrameScreenShot::WorkSpace::SetImage(const wxImage *image,
                                          const bool &cache /*= true*/) {
  do {
    if (!image)
      break;
    if (!image->IsOk())
      break;
    SetSize(image->GetSize());
    SK_DELETE_PTR(backgroundBitmap_);
    backgroundBitmap_ = new wxBitmap(*image);
    Refresh(false);
    Update();
    if (cache)
      draw_success_cache_.push_back(const_cast<wxImage *>(image));
  } while (0);
}