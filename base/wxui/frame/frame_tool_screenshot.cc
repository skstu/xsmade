#include "wxui.h"

wxBEGIN_EVENT_TABLE(FrameToolScreenShot, wxFrame)
    EVT_SIZE(FrameToolScreenShot::OnSize) EVT_MOVE(FrameToolScreenShot::OnMove)
        EVT_CLOSE(FrameToolScreenShot::OnClose)
            EVT_MOTION(FrameToolScreenShot::OnMouseMove)
                EVT_LEFT_DOWN(FrameToolScreenShot::OnMouseLeftDown)
                    EVT_LEFT_DCLICK(FrameToolScreenShot::OnMouseLeftDClick)
                        EVT_LEFT_UP(FrameToolScreenShot::OnMouseLeftUp)
                            wxEND_EVENT_TABLE();

FrameToolScreenShot::FrameToolScreenShot(wxWindow *parent, wxWindowID id,
                                         const wxString &title,
                                         const wxPoint &pos, const wxSize &size,
                                         long style, const wxString &name)
    : FrameBase(parent, id, title, wxPoint(0, 0), wxSize(300, 40),
                /*(wxDEFAULT_FRAME_STYLE & ~wxCLOSE_BOX & ~wxCAPTION)*/
                wxNO_BORDER | wxFRAME_NO_TASKBAR /*| wxRESIZE_BORDER*/, name) {

  SetBackgroundColour(wxColour(252, 252, 252));

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
  LayoutEx();
  Bind(wxEVT_BUTTON, &FrameToolScreenShot::OnToolEvent, this);
}
FrameToolScreenShot::~FrameToolScreenShot() {
  Unbind(wxEVT_BUTTON, &FrameToolScreenShot::OnToolEvent, this);
}
void FrameToolScreenShot::LayoutEx() {
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
}
void FrameToolScreenShot::OnToolEvent(wxCommandEvent &evt) {
  switch (evt.GetId()) {
  case CommandTool::TOOL_SCREENSHOT_EIDT: {

  } break;
  case CommandTool::TOOL_SCREENSHOT_CLOSE: {
    Global::ffxShowRecordingComponents();
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

  } break;
  case CommandTool::TOOL_SCREENSHOT_REVOCATION: {
    Show(false);
    Global::ffxShowWindow(false);
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    app->SetCapturingHostType(CapturingHostType::CAPTUREING_SCREENSHOT);
    Global::ffxShowBkg(true);
  } break;
  default:
    break;
  }
  evt.Skip();
}
void FrameToolScreenShot::OnSize(wxSizeEvent &event) {
  LayoutEx();
  Refresh();
  event.Skip();
}
void FrameToolScreenShot::OnMove(wxMoveEvent &event) {
  LayoutEx();
  event.Skip();
}
void FrameToolScreenShot::OnClose(wxCloseEvent &event) {
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
void FrameToolScreenShot::OnMouseMove(wxMouseEvent &event) {
  wxPoint pt = event.GetPosition();
  if (event.Dragging() && event.LeftIsDown()) {
    is_dragging_.store(true);
    wxPoint pos = ClientToScreen(pt); // pos为点击位置

    Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));
  }
}
void FrameToolScreenShot::OnMouseLeftDClick(wxMouseEvent &event) {
  event.Skip();
}
void FrameToolScreenShot::OnMouseLeftDown(wxMouseEvent &event) {
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

void FrameToolScreenShot::OnMouseLeftUp(wxMouseEvent &event) {
  if (HasCapture()) {
    ReleaseMouse();
  }
  is_dragging_.store(false);
}
