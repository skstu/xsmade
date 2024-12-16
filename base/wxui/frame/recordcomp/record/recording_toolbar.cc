#include <wxui.h>
FrameRecording::Toolbar::Toolbar(wxWindow *parent, wxWindowID id,
                                 const wxString &title, const wxPoint &pos,
                                 const wxSize &size, long style,
                                 const wxString &name)
    : IToolbar(parent, id, title, wxDefaultPosition, wxDefaultSize,
               /*(wxDEFAULT_FRAME_STYLE & ~wxCLOSE_BOX & ~wxCAPTION)*/
               wxNO_BORDER | wxFRAME_NO_TASKBAR /*| wxRESIZE_BORDER*/, name) {
  SetBackgroundColour(wxColour(252, 252, 252));
  Init();

  // OnLayout();
  // Bind(wxEVT_BUTTON, &FrameRecording::Toolbar::OnToolEvent, this);
}
FrameRecording::Toolbar::~Toolbar() {
  // Unbind(wxEVT_BUTTON, &FrameRecording::Toolbar::OnToolEvent, this);
  UnInit();
}
void FrameRecording::Toolbar::Init() {
  // wxPanel *panel = new wxPanel(this);
  wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

  sizer->AddStretchSpacer();

  do {
    auto img = Config::Get()->GetResImage("btn_recording_screenshot.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new record::ActionScreenshot(this, CommandTool::TOOL_SCREENSHOT,
                                            wxBitmapBundle::FromImage(*img),
                                            wxDefaultPosition, btn_size_);
    sizer->Add(btn, 0, wxALL, 0);
  } while (0);

  do {
    auto img_start = Config::Get()->GetResImage("btn_recording_start.png");
    auto img_stop = Config::Get()->GetResImage("btn_recording_stop.png");
    if (!img_start || !img_stop)
      break;
    img_start->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    img_stop->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new record::ActionRecording(
        this, CommandTool::TOOL_RECORDING_START,
        wxBitmapBundle::FromImage(*img_start), wxDefaultPosition, btn_size_);
    btn->SetBitmapSelected(wxBitmap(*img_stop));
    sizer->Add(btn, 0, wxALL, 0);
  } while (0);

  do {
    auto img = Config::Get()->GetResImage("btn_recording_box_selection.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new record::ActionBoxSelection(this, CommandTool::TOOL_WINDOW,
                                              wxBitmapBundle::FromImage(*img),
                                              wxDefaultPosition, btn_size_);
    sizer->Add(btn, 0, wxALL, 0);
  } while (0);

  do {
    auto img = Config::Get()->GetResImage("btn_recording_close.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new record::ActionSystemClose(
        this, CommandTool::TOOL_SYSTEM_CLOSE, wxBitmapBundle::FromImage(*img),
        wxDefaultPosition, btn_size_);
    sizer->Add(btn, 0, wxALL, 0);
  } while (0);

  SetSizer(sizer);
  sizer->SetSizeHints(this);
  SetSize(sizer->GetSize());
}
void FrameRecording::Toolbar::UnInit() {
}
void FrameRecording::Toolbar::OnFullScreenShown() {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *workspace = app->FrameGet(ComponentFrameType::RECORDING_WORKSPACE);
    if (!workspace)
      break;
    if (is_fullscreen_shown_.load()) {
      SetPosition(wxPoint(0, 0));
      wxDisplay display;
      wxRect workArea = display.GetClientArea();
      wxSize current = GetSize();
      SetSize(workArea.GetSize().GetWidth(), current.GetHeight());
      workspace->SetSize(workArea.GetSize().GetWidth(),
                         workArea.GetSize().GetHeight() -
                             GetSize().GetHeight());
    } else {
      workspace->SetSize(prev_frame_work_rect_.GetWidth(),
                         prev_frame_work_rect_.GetHeight());
      SetSize(prev_frame_tool_rect_.GetWidth(), GetSize().GetHeight());
    }
  } while (0);
}
void FrameRecording::Toolbar::OnLayout() {
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
  OnToolbarSizeChanged(GetRect());
}
void FrameRecording::Toolbar::OnToolbarSizeChanged(const wxRect &rect) {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    auto workspace = app->FrameGet(ComponentFrameType::RECORDING_WORKSPACE);
    if (!workspace)
      break;
    workspace->SetSize(rect.GetLeft(), rect.GetTop() + rect.GetHeight(),
                       rect.GetWidth(), workspace->GetSize().GetHeight());
  } while (0);
}
void FrameRecording::Toolbar::OnToolEvent(wxCommandEvent &evt) {
#if 0
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
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    auto comp_recording = app->FrameComponentGet(FrameComponentType::RECORDING);
    auto comp_screenshot =
        app->FrameComponentGet(FrameComponentType::SCREENSHOT);
    comp_recording->Show(false);
    comp_screenshot->ShowBackground(true);
  } break;
  case CommandTool::TOOL_WINDOW: {
#if 0
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    app->SetCapturingHostType(CapturingHostType::CAPTUREING_RECORDING);
    Global::ffxShowBkg(true);
    Global::ffxShowWindow(false);
#endif
  } break;
  case CommandTool::TOOL_RECORDING_START: {
#if 0
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
#endif
    btn_recording_start_->SetBitmapLabel(wxBitmapBundle::FromImage(
        *Config::Get()->GetResImage("btn_recording_stop.png")));
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
#endif
  evt.Skip();
}
void FrameRecording::Toolbar::OnClose(wxCloseEvent &event) {
  int res = wxMessageBox(L"Are you sure you want to exit system?", L"Memade®",
                         wxYES_NO, this);
  if (res != wxYES) {
    event.Veto();
  } else {
    auto handle = wxApp::GetInstance();
    auto frame_component_recording =
        wxDynamicCast(handle, App)
            ->FrameComponentGet(FrameComponentType::RECORDING);
    frame_component_recording->Show(false);
    wxQueueEvent(handle,
                 new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_FrameDestroy));
    event.Skip();
  }
}
#if 0
void FrameRecording::Toolbar::InitButtons() {
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
    // btn_recording_start_->SetBitmapPressed(*btn_recording_stop_);
    btn_recording_start_->SetBitmapSelected(wxBitmap(*img));
  }
  img = Config::Get()->GetResImage("btn_window.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_window_ = new wxBitmapButton(this, CommandTool::TOOL_WINDOW,
                                     wxBitmapBundle::FromImage(*img));
    btn_window_->SetToolTip(gpCommandToolTipMap[CommandTool::TOOL_WINDOW]);
    btn_window_->SetSize(wxSize(btn_size, btn_size));
  }
#if 0
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
#endif
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
}
#endif