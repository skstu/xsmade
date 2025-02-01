#include "wxui.h"
void Global::SendEvent(wxCommandEvent &cmdevt) {
  do {
    wxThreadEvent *tevt =
        new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_BroadcastEvent);
    tevt->SetPayload(cmdevt);
    wxQueueEvent(wxApp::GetInstance(), tevt);
  } while (0);
}

///////////////////////////////////////////////////////////////////////////////////
// backup codes
///////////////////////////////////////////////////////////////////////////////////
bool Global::ffxScreenShot(const wxRect &region, std::string &stream) {
  bool result = false;
  stream.clear();
  do {
    xs_image_stream_t *imgStream = nullptr;
    xs_sys_capturescreen(xs_position_t{region.GetLeft(), region.GetTop(),
                                       region.GetWidth(), region.GetHeight()},
                         xs_image_stream_type_t::PNG, &imgStream);
    if (!imgStream)
      break;
    stream.append(imgStream->buffer, imgStream->len);
    xs_sys_image_stream_destroy(&imgStream);
    result = true;
  } while (0);
  return result;
}
void Global::ffxHideScreenShotToolbar() {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    auto toolbar = dynamic_cast<wxFrame *>(app->FrameScreenShotToolGet());
    if (!toolbar)
      break;
    if (!toolbar->IsShown())
      break;
    toolbar->Show(false);
  } while (0);
#endif
}
void Global::ffxShowBkg(const bool &flag) {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    FrameWorkImage *frame_work_image =
        dynamic_cast<FrameWorkImage *>(app->FrameWorkImageGet());
    auto frame_bkg = dynamic_cast<wxFrame *>(app->FrameBgkGet());
    if (!frame_bkg)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    wxFrame *frame_screenshot_toolbar_ =
        dynamic_cast<wxFrame *>(app->FrameScreenShotToolGet());
    frame_bkg->Show(flag);
    if (frame_work_image) {
      frame_work_image->Show(false);
    }
    if (frame_tool)
      frame_tool->Show(false);
    if (frame_work)
      frame_work->Show(false);
    if (frame_screenshot_toolbar_)
      frame_screenshot_toolbar_->Show(false);
  } while (0);
#endif
}
void Global::ffxShowScreenShotToolbar(const wxRect &select_rectangle) {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    auto toolbar = dynamic_cast<wxFrame *>(app->FrameScreenShotToolGet());
    if (!toolbar)
      break;
    toolbar->SetPosition(wxPoint(0, 0));
    if (!toolbar->IsShown())
      toolbar->Show(true);
  } while (0);
#endif
}
void Global::ffxLayout() {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    wxRect rtWindow = frame_tool->GetRect();
    frame_work->SetSize(rtWindow.GetLeft(),
                        rtWindow.GetTop() + rtWindow.GetHeight(),
                        rtWindow.GetWidth(), frame_work->GetSize().GetHeight());
#if 0  
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    auto frame = app->FrameWorkGet();
    if (!frame)
      break;
    wxRect rtWindow = GetRect();
#if 0
    frame->SetRegion(rtWindow.GetLeft(),
                     rtWindow.GetTop() + rtWindow.GetHeight(),
                     rtWindow.GetWidth(),
                     dynamic_cast<wxFrame *>(frame)->GetSize().GetHeight());
#else
    dynamic_cast<wxFrame *>(frame)->SetSize(
        rtWindow.GetLeft(), rtWindow.GetTop() + rtWindow.GetHeight(),
        rtWindow.GetWidth(),
        dynamic_cast<wxFrame *>(frame)->GetSize().GetHeight());
#endif
#endif
  } while (0);
#endif
}
void Global::ffxFullScreen(const bool &entry, const wxSize &prev_frame_tool,
                           const wxSize &perv_frame_shape) {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    if (entry) {
      frame_tool->SetPosition(wxPoint(0, 0));
      wxDisplay display;
      wxRect workArea = display.GetClientArea();
      wxSize current = frame_tool->GetSize();
      frame_tool->SetSize(workArea.GetSize().GetWidth(), current.GetHeight());
      frame_work->SetSize(workArea.GetSize().GetWidth(),
                          workArea.GetSize().GetHeight() -
                              frame_tool->GetSize().GetHeight());
    } else {
      frame_work->SetSize(prev_frame_tool.GetWidth(),
                          perv_frame_shape.GetHeight());
      frame_tool->SetSize(prev_frame_tool.GetWidth(),
                          frame_tool->GetSize().GetHeight());
    }
  } while (0);
#endif
}
void Global::ffxShowWindow(const bool &flag) {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    if (flag) {
      if (!frame_work->IsShown())
        frame_work->Show(flag);
    } else {
      if (frame_work->IsShown())
        frame_work->Show(flag);
    }
    if (flag) {
      if (!frame_tool->IsShown())
        frame_tool->Show(flag);
    } else {
      if (frame_tool->IsShown())
        frame_tool->Show(flag);
    }
    if (flag) {
#if defined(__OSWIN__)
      SetWindowPos(frame_tool->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0,
                   SWP_NOMOVE | SWP_NOSIZE /*| SWP_SHOWWINDOW*/);
      SetWindowPos(frame_work->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0,
                   SWP_NOMOVE | SWP_NOSIZE /*| SWP_SHOWWINDOW*/);
#endif
    } else {
      frame_tool->Show(false);
      frame_work->Show(false);
    }
#if 0
        else {
      // frame_work->Show(false);
      // frame_tool->Show(false);
      SetWindowPos(frame_tool->GetHWND(), NULL, 0, 0, 0, 0,
                   SWP_NOMOVE | SWP_NOSIZE /*| SWP_HIDEWINDOW*/);
      SetWindowPos(frame_work->GetHWND(), NULL, 0, 0, 0, 0,
                   SWP_NOMOVE | SWP_NOSIZE /*| SWP_HIDEWINDOW*/);
    }
#endif
  } while (0);
#endif
}
void Global::ffxScaling(const float &scaling) {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    wxSize sizeShape = frame_work->GetSize();
    wxSize sizeTool = frame_tool->GetSize();
    wxPoint ptTool = frame_tool->GetPosition();
    int tool_old_x = ptTool.x;
    int tool_old_y = ptTool.y;
    int tool_old_cx = sizeTool.GetWidth();
    int tool_old_cy = sizeTool.GetHeight();

    int final_tool_cx = sizeTool.GetWidth() * scaling;
    int final_tool_cy = sizeTool.GetHeight();
    int final_shape_cx = final_tool_cx;
    int final_shape_cy = sizeShape.GetHeight() * scaling;
    int final_pos_x =
        tool_old_x - static_cast<int>((final_tool_cx - tool_old_cx) / 2);
    int final_pos_y =
        tool_old_y - static_cast<int>((final_tool_cy - tool_old_cy) / 2);

    frame_work->SetSize(wxSize(final_shape_cx, final_shape_cy));
    frame_tool->SetPosition(wxPoint(final_pos_x, final_pos_y));
    frame_tool->SetSize(wxSize(final_tool_cx, final_tool_cy));
  } while (0);
#endif
}
void Global::ffxShowRecordingComponents() {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    FrameWorkImage *frame_work_image =
        dynamic_cast<FrameWorkImage *>(app->FrameWorkImageGet());
    wxFrame *frame_bkg = dynamic_cast<wxFrame *>(app->FrameBgkGet());
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    wxFrame *frame_screenshot_toolbar_ =
        dynamic_cast<wxFrame *>(app->FrameScreenShotToolGet());
    if (!frame_work || !frame_tool)
      break;
    frame_bkg->Show(false);
    frame_work_image->Show(false);
    frame_screenshot_toolbar_->Show(false);
    ffxShowWindow(true);
    ffxCenter();
  } while (0);
#endif
}
void Global::ffxTopmost() {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
#if defined(__OSWIN__)
    SetWindowPos(frame_tool->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE /*| SWP_SHOWWINDOW*/);
    SetWindowPos(frame_work->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE /*| SWP_SHOWWINDOW*/);
#endif
    frame_tool->Show(true);
    frame_work->Show(true);
  } while (0);
#endif
}
void Global::ffxCenter() {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    frame_work->Center();
    wxRect rect = frame_work->GetRect();
    frame_tool->SetSize(rect.GetLeft(),
                        rect.GetTop() - frame_tool->GetSize().GetHeight(),
                        rect.GetWidth(), frame_tool->GetSize().GetHeight());
  } while (0);
#endif
}
#if 0
void Global::ffxSetPos(const wxRect &rect,
                       const CapturingHostType &captureType) {

  do {
    if (rect.GetWidth() < 100 || rect.GetHeight() < 100)
      break;
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    wxFrame *frame_screenshot =
        dynamic_cast<wxFrame *>(app->FrameScreenShotToolGet());
    if (!frame_work || !frame_tool || !frame_screenshot)
      break;
    frame_work->SetSize(rect.GetLeft(), rect.GetTop(), rect.GetWidth(),
                        rect.GetHeight());
    switch (captureType) {
    case CapturingHostType::CAPTUREING_RECORDING: {
      frame_tool->SetSize(rect.GetLeft(),
                          rect.GetTop() - frame_tool->GetSize().GetHeight(),
                          rect.GetWidth(), frame_tool->GetSize().GetHeight());
    } break;
    case CapturingHostType::CAPTUREING_SCREENSHOT: {
      frame_tool->Show(false);
      frame_work->Show(true);

      wxRect size;
      size.SetLeft(rect.GetRight() - frame_screenshot->GetSize().GetWidth());
      size.SetTop(rect.GetBottom());
      size.SetWidth(frame_screenshot->GetSize().GetWidth());
      size.SetHeight(frame_screenshot->GetSize().GetHeight());

      frame_screenshot->SetSize(size);

      frame_screenshot->Show(true);
    } break;
    default:
      break;
    }

  } while (0);

}
#endif
void Global::ffxCaptureScreenShot(std::string &outImgStream) {
#if 0
  outImgStream.clear();
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    if (!frame_work)
      break;
    wxRect rect = frame_work->GetRect();
    xs_image_stream_t *imgStream = nullptr;
    frame_work->Show(false);
    xs_sys_capturescreen(xs_position_t{rect.GetLeft(), rect.GetTop(),
                                       rect.GetWidth(), rect.GetHeight()},
                         xs_image_stream_type_t::PNG, &imgStream);
    frame_work->Show(true);
    if (!imgStream)
      break;
    outImgStream.append(imgStream->buffer, imgStream->len);
    xs_sys_image_stream_destroy(&imgStream);
  } while (0);
#endif
}
void Global::ffxFrameWorkImageShow(const bool &flag,
                                   const std::string &imgPath) {
#if 0
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_work = dynamic_cast<wxFrame *>(app->FrameWorkGet());
    FrameWorkImage *frame_work_image =
        dynamic_cast<FrameWorkImage *>(app->FrameWorkImageGet());
    if (!frame_work_image || !frame_work)
      break;
    frame_work->Show(false);
    if (!frame_work_image->SetBackgroundBitmap(imgPath))
      break;
    frame_work_image->SetSize(frame_work->GetRect());
    frame_work_image->Show();
  } while (0);
#endif
}
Global::Global() {
  Init();
}
Global::~Global() {
  UnInit();
}
void Global::Init() {
  screenshot_draw_font_.SetFaceName("Arial");
  screenshot_draw_font_.SetPointSize(12);
  screenshot_draw_font_.SetFamily(wxFONTFAMILY_SWISS);
  screenshot_draw_font_.SetStyle(wxFONTSTYLE_NORMAL);
  screenshot_draw_font_.SetNumericWeight(wxFONTWEIGHT_NORMAL);
  screenshot_draw_font_.SetUnderlined(false);
  screenshot_draw_font_.SetStrikethrough(false);
  screenshot_draw_text_color_.Set(255, 0, 0);
}
void Global::UnInit() {
}
void Global::SetScreenShotDrawTextColor(const wxColour &color) {
  std::lock_guard<std::mutex> lock(*mtx_);
  screenshot_draw_text_color_ = color;
}
const wxColour &Global::GetScreenShotDrawTextColor() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return screenshot_draw_text_color_;
}
void Global::SetScreenShotDrawTextFont(const wxFont &font) {
  std::lock_guard<std::mutex> lock(*mtx_);
  screenshot_draw_font_ = font;
}
const wxFont &Global::GetScreenShotDrawTextFont() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return screenshot_draw_font_;
}
////////////////////////////////////////////////////////////////////////////////////
static Global *__gpsGlobal = nullptr;
Global *Global::Get() {
  if (!__gpsGlobal)
    __gpsGlobal = new Global();
  return __gpsGlobal;
}
