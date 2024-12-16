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
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtScreenShotFinished, this,
                       wxAppThreadEvt_ScreenShotFinished);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtScreenShotClose, this,
                       wxAppThreadEvt_ScreenShotClose);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtRecordingBoxSelection,
                       this, wxAppThreadEvt_RecordingBoxSelection);
    wxEvtHandler::Bind(wxEVT_THREAD,
                       &App::OnThreadEvtRecordingBoxSelectionFinished, this,
                       wxAppThreadEvt_RecordingBoxSelectionFinished);

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
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtScreenShotFinished,
                         this, wxAppThreadEvt_ScreenShotFinished);
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtScreenShotClose, this,
                         wxAppThreadEvt_ScreenShotClose);
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtRecordingBoxSelection,
                         this, wxAppThreadEvt_RecordingBoxSelection);
    wxEvtHandler::Unbind(wxEVT_THREAD,
                         &App::OnThreadEvtRecordingBoxSelectionFinished, this,
                         wxAppThreadEvt_RecordingBoxSelectionFinished);
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
void App::OnThreadEvtRecordingBoxSelection(wxThreadEvent &evt) {
  do {
    IFrameComponent *recording_component = nullptr;
    wxRect screenshot_region;
    for (auto &node : frame_comps_) {
      switch (node.first) {
      case FrameComponentType::RECORDING: {
        recording_component = node.second;
      } break;
      case FrameComponentType::SCREENSHOT: {

      } break;
      default:
        break;
      }
      node.second->Show(false);
    }
    recording_component->ShowBackground(true);
  } while (0);
}
void App::OnThreadEvtScreenShotClose(wxThreadEvent &evt) {
  do {
    wxRect screenshot_region;
    for (auto &node : frame_comps_) {
      switch (node.first) {
      case FrameComponentType::RECORDING: {
        node.second->Center();
        node.second->Show(true);
      } break;
      case FrameComponentType::SCREENSHOT: {
        node.second->Show(false);
      } break;
      default:
        break;
      }
    }
  } while (0);
}
void App::OnThreadEvtScreenShotFinished(wxThreadEvent &evt) {
  do {
    IFrameComponent *screenshot_component = nullptr;
    wxRect screenshot_region;
    for (auto &node : frame_comps_) {
      switch (node.first) {
      case FrameComponentType::RECORDING: {
        screenshot_region = node.second->GetRegion();
      } break;
      case FrameComponentType::SCREENSHOT: {
        screenshot_component = node.second;
      } break;
      default:
        break;
      }
      node.second->Show(false);
    }
    std::string screenshot_image_stream;
    Global::ffxScreenShot(screenshot_region, screenshot_image_stream);
    screenshot_component->SetWorkSpace(screenshot_image_stream);
    screenshot_component->Center();
    screenshot_component->Show(true);
  } while (0);
}
void App::OnThreadEvtRecordingBoxSelectionFinished(wxThreadEvent &evt) {
  do {
    wxCommandEvent *cmdevt =
        reinterpret_cast<wxCommandEvent *>(evt.GetEventObject());
    if (!cmdevt)
      break;
    wxRect *rect = (wxRect *)cmdevt->GetClientData();
    if (!rect)
      break;
    wxRect pos(*rect);
    SK_DELETE_PTR(rect);
    IFrameComponent *screenshot_component = nullptr;
    auto found = frame_comps_.find(FrameComponentType::RECORDING);
    if (found == frame_comps_.end())
      break;
    screenshot_component = found->second;
    screenshot_component->SetPos(pos);
    screenshot_component->Show(true);
  } while (0);
}
/////////////////////////////////////////////////////////////////////////////
wxIMPLEMENT_APP_NO_MAIN(App);
const int wxAppThreadEvt_FrameDestroy = wxNewId();
const int wxAppThreadEvt_BroadcastEvent = wxNewId();
const int wxAppThreadEvt_ScreenShotFinished = wxNewId();
const int wxAppThreadEvt_ScreenShotClose = wxNewId();
const int wxAppThreadEvt_RecordingBoxSelection = wxNewId();
const int wxAppThreadEvt_RecordingBoxSelectionFinished = wxNewId();
