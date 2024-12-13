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
  xs_sys_shutdown();
  return result;
}
void App::OnThreadEvtFrameDestroy(wxThreadEvent &event) {
  ExitMainLoop();
}
void App::OnFrameDestroy() {
  do {
#if 0
    auto frame_tool = dynamic_cast<wxFrame *>(frame_tool_);
    auto frame_work = dynamic_cast<wxFrame *>(frame_work_);
    frame_work->Show(false);
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
      frame->Center();
      frame->Show();
    } break;
    case FrameType::SHAPEFRAME: {
#if 0
      frame_bgk_ = new FrameBgk(nullptr);
      frame_work_ = new FrameWork(nullptr);
      frame_tool_ = new FrameTool(nullptr);
      frame_work_image_ = new FrameWorkImage(nullptr);
      frame_screenshot_tool_ = new FrameToolScreenShot(nullptr);
      Global::ffxCenter();
      Global::ffxTopmost();
#endif
      IFrameComponent *frame_screenshot = new FrameScreenShot();
      IFrameComponent *frame_recording = new FrameRecording();
      frame_comps_.emplace(frame_recording->Type(), frame_recording);
      frame_comps_.emplace(frame_screenshot->Type(), frame_screenshot);
      frame_recording->Center();
      frame_recording->Show(true);
    } break;
    default:
      break;
    }

  } while (0);
}
wxFrame *App::FrameAppend(const ComponentFrameType &frame_type,
                          wxFrame *frame) {
  auto found = frames_.find(frame_type);
  if (found != frames_.end())
    frames_.erase(found);
  frames_.emplace(frame_type, frame);
  return frame;
}
IFrameComponent *App::FrameComponentGet(const FrameComponentType &type) const {
  auto found = frame_comps_.find(type);
  if (found == frame_comps_.end())
    return nullptr;
  return found->second;
}
wxFrame *App::FrameGet(const ComponentFrameType &frame_type) const {
  auto found = frames_.find(frame_type);
  if (found == frames_.end())
    return nullptr;
  return found->second;
}
IFrame *App::FrameGet() const {
  return frame_;
}
/////////////////////////////////////////////////////////////////////////////
wxIMPLEMENT_APP_NO_MAIN(App);
const int wxAppThreadEvt_FrameDestroy = wxNewId();
const int wxAppThreadEvt_BroadcastEvent = wxNewId();
