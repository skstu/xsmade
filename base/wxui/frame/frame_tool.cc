#include "wxui.h"

wxBEGIN_EVENT_TABLE(FrameTool, wxFrame) EVT_SIZE(FrameTool::OnSize)
    EVT_MOVE(FrameTool::OnMove) EVT_CLOSE(FrameTool::OnClose)
        EVT_MOTION(FrameTool::OnMouseMove)
            EVT_LEFT_DOWN(FrameTool::OnMouseLeftDown)
                EVT_LEFT_DCLICK(FrameTool::OnMouseLeftDClick)
                    EVT_LEFT_UP(FrameTool::OnMouseLeftUp) wxEND_EVENT_TABLE();

FrameTool::FrameTool(wxWindow *parent, wxWindowID id, const wxString &title,
                     const wxPoint &pos, const wxSize &size, long style,
                     const wxString &name)
    : FrameBase(parent, id, title, wxPoint(0, 0), wxSize(640, 40),
                /*(wxDEFAULT_FRAME_STYLE & ~wxCLOSE_BOX & ~wxCAPTION)*/
                wxNO_BORDER | wxFRAME_NO_TASKBAR /*| wxRESIZE_BORDER*/, name) {

  SetBackgroundColour(wxColour(252, 252, 252));

  wxImage *img = Config::Get()->GetResImage("btn_close.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_close_ = new wxBitmapButton(this, CommandTool::TOOL_SYSTEM_CLOSE,
                                    wxBitmapBundle::FromImage(*img));
    btn_close_->SetToolTip(gpCommandToolTipMap[CommandTool::TOOL_SYSTEM_CLOSE]);
    btn_close_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_recording_start.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_recording_start_ =
        new wxBitmapButton(this, CommandTool::TOOL_RECORDING_START,
                           wxBitmapBundle::FromImage(*img));
    btn_recording_start_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_RECORDING_START]);
    btn_recording_start_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_recording_stop.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_recording_stop_ =
        new wxBitmapButton(this, CommandTool::TOOL_RECORDING_STOP,
                           wxBitmapBundle::FromImage(*img));
    btn_recording_stop_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_RECORDING_STOP]);
    btn_recording_stop_->SetSize(wxSize(btn_size, btn_size));
    btn_recording_stop_->Show(false);
  }
  img = Config::Get()->GetResImage("btn_window.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_window_ = new wxBitmapButton(this, CommandTool::TOOL_WINDOW,
                                     wxBitmapBundle::FromImage(*img));
    btn_window_->SetToolTip(gpCommandToolTipMap[CommandTool::TOOL_WINDOW]);
    btn_window_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_scaling_down.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_scaling_down_ = new wxBitmapButton(this, CommandTool::TOOL_SCALING_DOWN,
                                           wxBitmapBundle::FromImage(*img));
    btn_scaling_down_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCALING_DOWN]);
    btn_scaling_down_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_scaling_up.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_scaling_up_ = new wxBitmapButton(this, CommandTool::TOOL_SCALING_UP,
                                         wxBitmapBundle::FromImage(*img));
    btn_scaling_up_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCALING_UP]);
    btn_scaling_up_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_settings.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_settings_ = new wxBitmapButton(this, CommandTool::TOOL_SETTINGS,
                                       wxBitmapBundle::FromImage(*img));
    btn_settings_->SetSize(wxSize(btn_size, btn_size));
    btn_settings_->SetToolTip(gpCommandToolTipMap[CommandTool::TOOL_SETTINGS]);
  }
  img = Config::Get()->GetResImage("btn_screenshot.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_screenshot_ = new wxBitmapButton(this, CommandTool::TOOL_SCREENSHOT,
                                         wxBitmapBundle::FromImage(*img));
    btn_screenshot_->SetSize(wxSize(btn_size, btn_size));
    btn_screenshot_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCREENSHOT]);
  }
  // img = Config::Get()->GetResImage("btn_screenshot_edit.png");
  // if (img) {
  //   img->Rescale(btn_size, btn_size);
  //   btn_screenshot_edit_ =
  //       new wxBitmapButton(this, CommandTool::TOOL_SCREENSHOT_EIDT,
  //                          wxBitmapBundle::FromImage(*img));
  //   btn_screenshot_edit_->SetSize(wxSize(btn_size, btn_size));
  //   btn_screenshot_edit_->SetToolTip(
  //       gpCommandToolTipMap[CommandTool::TOOL_SCREENSHOT_EIDT]);
  // }
  LayoutEx();
  Bind(wxEVT_BUTTON, &FrameTool::OnToolEvent, this);
}
FrameTool::~FrameTool() {
  Unbind(wxEVT_BUTTON, &FrameTool::OnToolEvent, this);
}
void FrameTool::LayoutEx() {
  int offset_r = 1;
  int offset_l = 1;
  wxSize cursize = GetSize();
  wxPoint curpt = GetPosition();
  if (btn_close_) {
    btn_close_->SetPosition(
        wxPoint(cursize.GetWidth() - btn_size - btn_offset_x_ * offset_r,
                btn_offset_y_));
  }
  if (btn_screenshot_edit_) {
    ++offset_r;
    btn_screenshot_edit_->SetPosition(wxPoint(
        cursize.GetWidth() - btn_size * offset_r - btn_offset_x_ * offset_r,
        btn_offset_y_));
  }
  if (btn_screenshot_) {
    ++offset_r;
    btn_screenshot_->SetPosition(wxPoint(
        cursize.GetWidth() - btn_size * offset_r - btn_offset_x_ * offset_r,
        btn_offset_y_));
  }

  if (btn_recording_start_) {
    ++offset_r;
    btn_recording_start_->SetPosition(wxPoint(
        cursize.GetWidth() - btn_size * offset_r - btn_offset_x_ * offset_r,
        btn_offset_y_));
  }
  if (btn_recording_stop_) {
    ++offset_r;
    btn_recording_stop_->SetPosition(wxPoint(
        cursize.GetWidth() - btn_size * offset_r - btn_offset_x_ * offset_r,
        btn_offset_y_));
  }

  if (btn_settings_) {
    btn_settings_->SetPosition(wxPoint(0 + btn_offset_x_ * 1, btn_offset_y_));
  }
  if (btn_window_) {
    btn_window_->SetPosition(
        wxPoint(btn_size * 1 + btn_offset_x_ * 2, btn_offset_y_));
  }
  if (btn_scaling_up_) {
    btn_scaling_up_->SetPosition(
        wxPoint(btn_size * 2 + btn_offset_x_ * 3, btn_offset_y_));
  }
  if (btn_scaling_down_) {
    btn_scaling_down_->SetPosition(
        wxPoint(btn_size * 3 + btn_offset_x_ * 4, btn_offset_y_));
  }

  Global::ffxLayout();
}
void FrameTool::OnToolEvent(wxCommandEvent &evt) {
  switch (evt.GetId()) {
  case CommandTool::TOOL_SCALING_UP: {
    Global::ffxScaling(1.2f);
  } break;
  case CommandTool::TOOL_SCALING_DOWN: {
    Global::ffxScaling(0.8f);
  } break;
  case CommandTool::TOOL_SETTINGS: {

  } break;
  case CommandTool::TOOL_SCREENSHOT: {
#if 0
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    auto frame_shape = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    if (!frame_shape)
      break;
#if defined(_DEBUG)
    std::string save_path = stl::Path::Mormalize(
        R"(C:\Users\k34ub\AppData\Roaming\MarsProjects\userdata\)");
#else
    std::string save_path =
        stl::Path::Mormalize(System::GetCurrentProcessPath());
#endif
    save_path.append("/")
        .append(
            std::to_string(stl::Time::TimeStamp<std::chrono::microseconds>()))
        .append(".png");

    wxRect rect = frame_shape->GetRect();
    xs_image_stream_t *imgStream = nullptr;
    Global::ffxShowWindow(false);
    xs_sys_capturescreen(xs_position_t{rect.GetLeft(), rect.GetTop(),
                                       rect.GetWidth(), rect.GetHeight()},
                         xs_image_stream_type_t::PNG, &imgStream);
    Global::ffxShowWindow(true);
    if (!imgStream)
      break;
    stl::File::WriteFile(save_path,
                         std::string(imgStream->buffer, imgStream->len));
    xs_sys_free((void **)&imgStream);
    wxString msg =
        wxString::Format(wxT("截屏完成!\n图片保存在[%s]\n"), save_path);
    wxMessageBox(msg, wxT("提示"));
#endif
    //!@ 进入框选
    Global::ffxShowWindow(false);
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    app->SetCapturingHostType(CapturingHostType::CAPTUREING_SCREENSHOT);
    auto frame_bgk = dynamic_cast<wxFrame *>(app->FrameBgkGet());
    if (!frame_bgk)
      break;
    frame_bgk->Show();
  } break;
  case CommandTool::TOOL_WINDOW: {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    app->SetCapturingHostType(CapturingHostType::CAPTUREING_RECORDING);
    Global::ffxShowBkg(true);
    Global::ffxShowWindow(false);
  } break;
  case CommandTool::TOOL_RECORDING_START: {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    auto frame_shape = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    if (!frame_shape)
      break;
    if (recording_running_.load())
      break;
    wxRect rt = frame_shape->GetRect();
    long x = rt.GetLeft();
    long y = rt.GetTop();
    long cx = rt.GetWidth();
    long cy = rt.GetHeight();
    cx -= (cx % 2);
    cy -= (cy % 2);
    RecordingArgs *args = new RecordingArgs();
    args->SetPos(x, y, cx, cy);
    Config::Get()->OnRecordingStart(args);
    args->Release();
    recording_running_.store(true);
    wxBitmapButton *btn = (wxBitmapButton *)evt.GetEventObject();
    btn->Show(false);
    btn_recording_stop_->Show();
  } break;
  case CommandTool::TOOL_RECORDING_STOP: {
    if (!recording_running_.load())
      break;
    recording_running_.store(false);
    Config::Get()->OnRecordingStop();
    wxBitmapButton *btn = (wxBitmapButton *)evt.GetEventObject();
    btn->Show(false);
    btn_recording_start_->Show();
  } break;
  case CommandTool::TOOL_SYSTEM_CLOSE: {
    Close();
  } break;
  default:
    break;
  }
  evt.Skip();
}
void FrameTool::OnSize(wxSizeEvent &event) {
  LayoutEx();
  Refresh();
  event.Skip();
}
void FrameTool::OnMove(wxMoveEvent &event) {
  LayoutEx();
  event.Skip();
}
void FrameTool::OnClose(wxCloseEvent &event) {
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
void FrameTool::OnMouseMove(wxMouseEvent &event) {
  wxPoint pt = event.GetPosition();
  if (event.Dragging() && event.LeftIsDown()) {
    is_dragging_.store(true);
    wxPoint pos = ClientToScreen(pt); // pos为点击位置

    Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));

    is_fullscreen_shown_.store((pos.y - m_delta.y) <= 0);
    Global::ffxFullScreen(is_fullscreen_shown_.load(), prev_frame_tool_size_,
                          prev_frame_work_size_);
  }
}
void FrameTool::OnMouseLeftDClick(wxMouseEvent &event) {
  event.Skip();
}
void FrameTool::OnMouseLeftDown(wxMouseEvent &event) {
  CaptureMouse();
  wxPoint pt = ClientToScreen(event.GetPosition());
  wxPoint origin = GetPosition();
  int dx = pt.x - origin.x;
  int dy = pt.y - origin.y;
  m_delta = wxPoint(dx, dy);
  if (!is_fullscreen_shown_.load()) {
    prev_frame_tool_size_ = GetSize();
    prev_frame_work_size_ =
        dynamic_cast<wxFrame *>(
            wxDynamicCast(wxApp::GetInstance(), App)->FrameWorkGet())
            ->GetSize();
  }
}

void FrameTool::OnMouseLeftUp(wxMouseEvent &event) {
  if (HasCapture()) {
    ReleaseMouse();
  }
  Global::ffxShowWindow(!is_fullscreen_shown_.load());
  is_dragging_.store(false);
}
