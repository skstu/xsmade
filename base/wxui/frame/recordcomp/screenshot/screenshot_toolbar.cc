#include <wxui.h>
FrameScreenShot::Toolbar::Toolbar(wxWindow *parent, wxWindowID id,
                                  const wxString &title, const wxPoint &pos,
                                  const wxSize &size, long style,
                                  const wxString &name)
    : IToolbar(parent, id, title, wxDefaultPosition, wxDefaultSize,
               /*(wxDEFAULT_FRAME_STYLE & ~wxCLOSE_BOX & ~wxCAPTION)*/
               wxNO_BORDER | wxFRAME_NO_TASKBAR /*| wxRESIZE_BORDER*/, name) {
  is_allow_move_.store(false);
  SetBackgroundColour(wxColour(252, 252, 252));
  Init();
#if 0
  wxImage *img = Config::Get()->GetResImage("btn_screenshot_toolbar_close.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_screenshot_toolbar_close_ =
        new wxBitmapButton(this, CommandTool::TOOL_SCREENSHOT_CLOSE,
                           wxBitmapBundle::FromImage(*img));
    btn_screenshot_toolbar_close_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCREENSHOT_CLOSE]);
    btn_screenshot_toolbar_close_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_screenshot_toolbar_edit.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_screenshot_toolbar_edit_ =
        new wxBitmapButton(this, CommandTool::TOOL_SCREENSHOT_EIDT,
                           wxBitmapBundle::FromImage(*img));
    btn_screenshot_toolbar_edit_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCREENSHOT_EIDT]);
    btn_screenshot_toolbar_edit_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_screenshot_toolbar_ok.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_screenshot_toolbar_ok_ = new wxBitmapButton(
        this, CommandTool::TOOL_SCREENSHOT_OK, wxBitmapBundle::FromImage(*img));
    btn_screenshot_toolbar_ok_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCREENSHOT_OK]);
    btn_screenshot_toolbar_ok_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_screenshot_toolbar_rectangle.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_screenshot_toolbar_rectangle_ =
        new wxBitmapButton(this, CommandTool::TOOL_SCREENSHOT_RECTANGLE,
                           wxBitmapBundle::FromImage(*img));
    btn_screenshot_toolbar_rectangle_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCREENSHOT_RECTANGLE]);
    btn_screenshot_toolbar_rectangle_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_screenshot_toolbar_revocation.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_screenshot_toolbar_revocation_ =
        new wxBitmapButton(this, CommandTool::TOOL_SCREENSHOT_REVOCATION,
                           wxBitmapBundle::FromImage(*img));
    btn_screenshot_toolbar_revocation_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCREENSHOT_REVOCATION]);
    btn_screenshot_toolbar_revocation_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_screenshot_toolbar_round.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_screenshot_toolbar_round_ =
        new wxBitmapButton(this, CommandTool::TOOL_SCREENSHOT_ROUND,
                           wxBitmapBundle::FromImage(*img));
    btn_screenshot_toolbar_round_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCREENSHOT_ROUND]);
    btn_screenshot_toolbar_round_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_screenshot_toolbar_mosaic.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_screenshot_toolbar_mosaic_ =
        new wxBitmapButton(this, CommandTool::TOOL_SCREENSHOT_MOSAIC,
                           wxBitmapBundle::FromImage(*img));
    btn_screenshot_toolbar_mosaic_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCREENSHOT_MOSAIC]);
    btn_screenshot_toolbar_mosaic_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_screenshot_toolbar_text.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_screenshot_toolbar_text_ =
        new wxBitmapButton(this, CommandTool::TOOL_SCREENSHOT_TEXT,
                           wxBitmapBundle::FromImage(*img));
    btn_screenshot_toolbar_text_->SetSize(wxSize(btn_size, btn_size));
    btn_screenshot_toolbar_text_->SetToolTip(
        gpCommandToolTipMap[CommandTool::TOOL_SCREENSHOT_TEXT]);
  }
#endif
  OnLayout();
  Bind(wxEVT_BUTTON, &FrameScreenShot::Toolbar::OnToolEvent, this);
}
FrameScreenShot::Toolbar::~Toolbar() {
  Unbind(wxEVT_BUTTON, &FrameScreenShot::Toolbar::OnToolEvent, this);
  UnInit();
}
void FrameScreenShot::Toolbar::GetExpandToolbar(wxPanel **outPanel,
                                                wxBoxSizer **outSizer) {
  *outPanel = panel;
  *outSizer = sizer_expand;
}
void FrameScreenShot::Toolbar::RefreshToolbar() {
  sizer->Layout();
  panel->SetSizer(sizer);
  sizer->SetSizeHints(panel);
  panel->Layout();
  SetSize(sizer->GetSize());
}
void FrameScreenShot::Toolbar::Init() {
  panel = new wxPanel(this);
  sizer = new wxBoxSizer(wxVERTICAL);
  sizer_top = new wxBoxSizer(wxHORIZONTAL);
  sizer_expand = new wxBoxSizer(wxHORIZONTAL);

  do {
    auto img =
        Config::Get()->GetResImage("btn_screenshot_toolbar_rectangle.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new screenshot::DrawRectangleTool(
        panel, CommandTool::TOOL_SCREENSHOT_RECTANGLE,
        wxBitmapBundle::FromImage(*img), wxDefaultPosition, btn_size_);
    sizer_top->Add(btn, 0, wxALL, 0);
  } while (0);
  do {
    auto img = Config::Get()->GetResImage("btn_screenshot_toolbar_round.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new screenshot::DrawCircleTool(
        panel, CommandTool::TOOL_SCREENSHOT_ROUND,
        wxBitmapBundle::FromImage(*img), wxDefaultPosition, btn_size_);
    sizer_top->Add(btn, 0, wxALL, 0);
  } while (0);
  do {
    auto img = Config::Get()->GetResImage("btn_screenshot_toolbar_arrow.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new screenshot::DrawArrowTool(
        panel, CommandTool::TOOL_SCREENSHOT_ARROW,
        wxBitmapBundle::FromImage(*img), wxDefaultPosition, btn_size_);
    sizer_top->Add(btn, 0, wxALL, 0);
  } while (0);
  do {
    auto img = Config::Get()->GetResImage("btn_screenshot_toolbar_brush.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new screenshot::DrawBrushTool(
        panel, CommandTool::TOOL_SCREENSHOT_EIDT,
        wxBitmapBundle::FromImage(*img), wxDefaultPosition, btn_size_);
    sizer_top->Add(btn, 0, wxALL, 0);
  } while (0);
  do {
    auto img = Config::Get()->GetResImage("btn_screenshot_toolbar_text.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new screenshot::DrawTextTool(
        panel, CommandTool::TOOL_SCREENSHOT_TEXT,
        wxBitmapBundle::FromImage(*img), wxDefaultPosition, btn_size_);
    sizer_top->Add(btn, 0, wxALL, 0);
  } while (0);
  do {
    auto img = Config::Get()->GetResImage("btn_screenshot_toolbar_mosaic.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new screenshot::DrawMosaicTool(
        panel, CommandTool::TOOL_SCREENSHOT_MOSAIC,
        wxBitmapBundle::FromImage(*img), wxDefaultPosition, btn_size_);
    sizer_top->Add(btn, 0, wxALL, 0);
  } while (0);
  do {
    auto img =
        Config::Get()->GetResImage("btn_screenshot_toolbar_revocation.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new screenshot::DrawNoTool(
        panel, CommandTool::TOOL_SCREENSHOT_REVOCATION,
        wxBitmapBundle::FromImage(*img), wxDefaultPosition, btn_size_);
    sizer_top->Add(btn, 0, wxALL, 0);
  } while (0);
  do {
    auto img = Config::Get()->GetResImage("btn_screenshot_toolbar_close.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new screenshot::DrawCloseTool(
        panel, CommandTool::TOOL_SCREENSHOT_CLOSE,
        wxBitmapBundle::FromImage(*img), wxDefaultPosition, btn_size_);
    sizer_top->Add(btn, 0, wxALL, 0);
  } while (0);
  do {
    auto img = Config::Get()->GetResImage("btn_screenshot_toolbar_ok.png");
    if (!img)
      break;
    img->Rescale(btn_scale_size_.GetWidth(), btn_scale_size_.GetHeight());
    auto btn = new screenshot::DrawOkTool(
        panel, CommandTool::TOOL_SCREENSHOT_OK, wxBitmapBundle::FromImage(*img),
        wxDefaultPosition, btn_size_);
    sizer_top->Add(btn, 0, wxALL, 0);
  } while (0);

  sizer->Add(sizer_top, 0, wxALL, 0);
  sizer->Add(sizer_expand, 0, wxALL, 0);
  panel->SetSizer(sizer);
  sizer->SetSizeHints(panel);
  SetSize(sizer->GetSize());
}
void FrameScreenShot::Toolbar::UnInit() {
}
void FrameScreenShot::Toolbar::OnLayout() {
#if 0
  wxSize cursize = GetSize();
  wxPoint curpt = GetPosition();
  if (btn_screenshot_toolbar_rectangle_) {
    btn_screenshot_toolbar_rectangle_->SetPosition(
        wxPoint(0 + btn_offset_x_ * 1, btn_offset_y_));
  }
  int offset_r = 0;
  int offset_l = 1;

  if (btn_screenshot_toolbar_round_) {
    btn_screenshot_toolbar_round_->SetPosition(wxPoint(
        btn_size * (++offset_r) + btn_offset_x_ * (++offset_l), btn_offset_y_));
  }
  if (btn_screenshot_toolbar_edit_) {
    btn_screenshot_toolbar_edit_->SetPosition(wxPoint(
        btn_size * (++offset_r) + btn_offset_x_ * (++offset_l), btn_offset_y_));
  }
  if (btn_screenshot_toolbar_mosaic_) {
    btn_screenshot_toolbar_mosaic_->SetPosition(wxPoint(
        btn_size * (++offset_r) + btn_offset_x_ * (++offset_l), btn_offset_y_));
  }
  if (btn_screenshot_toolbar_text_) {
    btn_screenshot_toolbar_text_->SetPosition(wxPoint(
        btn_size * (++offset_r) + btn_offset_x_ * (++offset_l), btn_offset_y_));
  }
  if (btn_screenshot_toolbar_revocation_) {
    btn_screenshot_toolbar_revocation_->SetPosition(wxPoint(
        btn_size * (++offset_r) + btn_offset_x_ * (++offset_l), btn_offset_y_));
  }
  if (btn_screenshot_toolbar_close_) {
    btn_screenshot_toolbar_close_->SetPosition(wxPoint(
        btn_size * (++offset_r) + btn_offset_x_ * (++offset_l), btn_offset_y_));
  }
  if (btn_screenshot_toolbar_ok_) {
    btn_screenshot_toolbar_ok_->SetPosition(wxPoint(
        btn_size * (++offset_r) + btn_offset_x_ * (++offset_l), btn_offset_y_));
  }
#endif
}
void FrameScreenShot::Toolbar::OnToolEvent(wxCommandEvent &evt) {
#if 0
  auto app = wxDynamicCast(wxApp::GetInstance(), App);
  switch (evt.GetId()) {
  case CommandTool::TOOL_SCREENSHOT_EIDT: {

  } break;
  case CommandTool::TOOL_SCREENSHOT_CLOSE: {
    // Global::ffxShowRecordingComponents();
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    auto comp_recording = app->FrameComponentGet(FrameComponentType::RECORDING);
    auto comp_screenshot =
        app->FrameComponentGet(FrameComponentType::SCREENSHOT);
    comp_screenshot->Show(false);
    comp_recording->Show(true);
    comp_recording->Center();
  } break;
  case CommandTool::TOOL_SCREENSHOT_OK: {
    std::string imgStream;
    Global::ffxCaptureScreenShot(imgStream);
    if (imgStream.empty())
      break;
    std::string save_path = stl::Path::Mormalize(
        System::GetCurrentProcessPath() + "/userdata/screenshot/");
    stl::Directory::Create(save_path);
    save_path.append("/")
        .append(
            std::to_string(stl::Time::TimeStamp<std::chrono::microseconds>()))
        .append(".png");
    stl::File::WriteFile(save_path, imgStream);
    Global::ffxFrameWorkImageShow(true, save_path);
    wxString msg = wxString::Format(
        wxT("图片资源保存在[%s]\n已加载到工作区!\n"), save_path);
    wxMessageBox(msg, wxT("截屏完成"));

  } break;
  case CommandTool::TOOL_SCREENSHOT_RECTANGLE: {
  } break;
  case CommandTool::TOOL_SCREENSHOT_ROUND: {

  } break;
  case CommandTool::TOOL_SCREENSHOT_TEXT: {
    auto font_toolbar =
        app->FrameGet(ComponentFrameType::SCREENSHOT_TOOLBAR_FONT);
    if (!font_toolbar)
      break;
    if (font_toolbar->IsShown()) {
      font_toolbar->Show(false);
      break;
    }
    auto toolbar = app->FrameGet(ComponentFrameType::SCREENSHOT_TOOLBAR);
    if (!toolbar)
      break;
    wxRect rtToolbar = toolbar->GetRect();
    font_toolbar->SetPosition(
        wxPoint(rtToolbar.GetRight() - font_toolbar->GetRect().GetWidth() + 1,
                rtToolbar.GetBottom() + 2));
    font_toolbar->Show(true);
  } break;
  case CommandTool::TOOL_SCREENSHOT_REVOCATION: {
#if 0
    Show(false);
    Global::ffxShowWindow(false);
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    app->SetCapturingHostType(CapturingHostType::CAPTUREING_SCREENSHOT);
    Global::ffxShowBkg(true);
#endif
    app->FrameComponentGet(FrameComponentType::SCREENSHOT)
        ->ShowBackground(true);
  } break;
  default:
    break;
  }
#endif
  evt.Skip();
}
void FrameScreenShot::Toolbar::OnToolbarSizeChanged(const wxRect &) {
  auto font_toolbar =
      wxDynamicCast(wxApp::GetInstance(), App)
          ->FrameGet(ComponentFrameType::SCREENSHOT_TOOLBAR_FONT);
  if (font_toolbar->IsShown()) {
    font_toolbar->Show(false);
  }
}
