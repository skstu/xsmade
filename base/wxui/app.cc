#include "wxui.h"
App::App() {
}
App::~App() {
}
bool App::OnInit() {
  xs_sys_startup();
  bool result = false;
  do {
    if (!wxApp::OnInit()) {
      break;
    }
    wxAppBase::SetExitOnFrameDelete(false);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtFrameDestroy, this,
                       wxAppThreadEvt_FrameDestroy);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtCaptureFinished, this,
                       wxAppThreadEvt_CaptureFinished);

    OnFrameCreate();
    result = true;
    open_.store(true);
    threads_.emplace_back([this]() { MainProc(); });
  } while (0);
  return result;
}
int App::OnExit() {
  int result = 0;
  do {
    OnFrameDestroy();
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtCaptureFinished, this,
                         wxAppThreadEvt_CaptureFinished);
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtFrameDestroy, this,
                         wxAppThreadEvt_FrameDestroy);
    result = wxApp::OnExit();
    open_.store(false);
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
  xs_sys_shutdown();
  return result;
}
void App::OnThreadEvtFrameDestroy(wxThreadEvent &event) {
  ExitMainLoop();
}
void App::SetCapturingHostType(const CapturingHostType &type) {
  who_is_capturing_.store(type);
}
CapturingHostType App::GetCapturingHostType() const {
  return who_is_capturing_.load();
}
void App::OnThreadEvtCaptureFinished(wxThreadEvent &event) {
  switch (who_is_capturing_.load()) {
  case CapturingHostType::CAPTUREING_RECORDING: {
    wxCommandEvent *evtObj = (wxCommandEvent *)event.GetEventObject();
    wxRect *rect = (wxRect *)evtObj->GetClientData();
    Global::ffxSetPos(*rect);
    Global::ffxShowWindow(true);
  } break;
  case CapturingHostType::CAPTUREING_SCREENSHOT: {
    wxCommandEvent *evtObj = (wxCommandEvent *)event.GetEventObject();
    wxRect *rect = (wxRect *)evtObj->GetClientData();
    Global::ffxShowScreenShotToolbar(*rect);
    Global::ffxSetPos(*rect, CapturingHostType::CAPTUREING_SCREENSHOT);
  } break;
  default:
    break;
  }
}
void App::OnFrameDestroy() {
  do {
    auto frame_tool = dynamic_cast<wxFrame *>(frame_tool_);
    auto frame_work = dynamic_cast<wxFrame *>(frame_work_);
    frame_work->Show(false);
  } while (0);
}
void App::OnFrameCreate() {
  do {
    wxFrame *frame = nullptr;
    switch (Config::Get()->GetFrameType()) {
    case FrameType::FRAME: {
      frame_ = new Frame(nullptr);
      frame = dynamic_cast<wxFrame *>(frame_);
      frame->Center();
      frame->Show();
    } break;
    case FrameType::SHAPEFRAME: {
      frame_bgk_ = new FrameBgk(nullptr);
      frame_work_ = new FrameWork(nullptr);
      frame_tool_ = new FrameTool(nullptr);
      frame_work_image_ = new FrameWorkImage(nullptr);
      frame_screenshot_tool_ = new FrameToolScreenShot(nullptr);
      Global::ffxCenter();
      Global::ffxTopmost();
    } break;
    default:
      break;
    }

  } while (0);
}
IFrame *App::FrameScreenShotToolGet() const {
  return frame_screenshot_tool_;
}
IFrame *App::FrameWorkImageGet() const {
  return frame_work_image_;
}
IFrame *App::FrameGet() const {
  return frame_;
}
IFrame *App::FrameToolGet() const {
  return frame_tool_;
}
IFrame *App::FrameBgkGet() const {
  return frame_bgk_;
}
IFrame *App::FrameWorkGet() const {
  return frame_work_;
}
void App::MainProc() {
  do {
    do {
      if (FrameType::SHAPEFRAME != Config::Get()->GetFrameType())
        break;
      if (!frame_tool_ || !frame_work_)
        break;
      int x(0), y(0);
      wxGetMousePosition(&x, &y);
      if (y > 0) {
        auto wxframe_ = dynamic_cast<wxFrame *>(frame_tool_);
        if (y > wxframe_->GetSize().GetHeight() && !frame_tool_->IsDragging()) {
          if (frame_tool_->IsFullScreenShown())
            Global::ffxShowWindow(false);
        }
        break;
      }
      Global::ffxShowWindow(true);
    } while (0);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if (!open_.load())
      break;
  } while (1);
}
/////////////////////////////////////////////////////////////////////////////
wxIMPLEMENT_APP_NO_MAIN(App);
const int wxAppThreadEvt_FrameDestroy = wxNewId();
const int wxAppThreadEvt_BroadcastEvent = wxNewId();
const int wxAppThreadEvt_CaptureFinished = wxNewId();
