#include "wxui.h"
App::App() {
}
App::~App() {
}
bool App::OnInit() {
  xs_sys_startup();
  do {
    if (!wxApp::OnInit()) {
      break;
    }
    wxAppBase::SetExitOnFrameDelete(false);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtBroadcastEvent, this,
                       wxAppThreadEvt_BroadcastEvent);
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
    open_.store(true);
    threads_.emplace_back([this]() { EventProc(); });
  } while (0);
  return open_.load();
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
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtBroadcastEvent, this,
                         wxAppThreadEvt_BroadcastEvent);
    result = wxApp::OnExit();
  } while (0);
  open_.store(false);
  for (auto &t : threads_)
    t.join();
  threads_.clear();
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
  auto found = comp_frames_.find(frame_type);
  if (found != comp_frames_.end())
    comp_frames_.erase(found);
  comp_frames_.emplace(frame_type, frame);
  frames_.push(frame);
  return frame;
}
IFrameComponent *App::FrameComponentGet(const FrameComponentType &type) const {
  auto found = frame_comps_.find(type);
  if (found == frame_comps_.end())
    return nullptr;
  return found->second;
}
wxFrame *App::FrameGet(const ComponentFrameType &frame_type) const {
  auto found = comp_frames_.find(frame_type);
  if (found == comp_frames_.end())
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
void App::OnThreadEvtBroadcastEvent(wxThreadEvent &evt) {
  wxCommandEvent route = evt.GetPayload<wxCommandEvent>();
  evts_.push(new wxCommandEvent(route));
}
void App::EnumerateChildren(wxWindow *parent,
                            std::unordered_set<wxWindow *> &childs) const {
  if (!parent)
    return;
  childs.emplace(parent);
  wxWindowList &children = parent->GetChildren();
  for (wxWindowList::iterator it = children.begin(); it != children.end();
       ++it) {
    wxWindow *child = *it;
    childs.emplace(child);
    if (!child->GetChildren().IsEmpty()) {
      EnumerateChildren(child, childs);
    }
  }
}

void App::BroadcastEvent(wxWindow *target, wxCommandEvent &route,
                         std::unordered_set<wxWindowID> &processed) const {
  if (!target || processed.find(target->GetId()) != processed.end()) {
    return;
  }
  // target->GetEventHandler()->ProcessEvent(route);
  processed.emplace(target->GetId());
  wxPostEvent(target, route);
  for (wxWindow *child : target->GetChildren()) {
    processed.emplace(target->GetId());
    BroadcastEvent(child, route, processed);
  }
}
void App::EventProc() {
  do {
    do {
      if (evts_.empty())
        break;
      auto evts = evts_.pops();
      for (wxCommandEvent *evt : evts) {
        std::set<wxWindow *> cache;
        frames_.iterate([&](wxFrame *frame) {
          wxWindow *frame_window = wxDynamicCast(frame, wxWindow);
          if (cache.find(frame_window) == cache.end()) {
            evt->SetEventObject(frame);
            wxPostEvent(frame, *evt);
            cache.emplace(frame_window);
          }
          std::unordered_set<wxWindow *> childs;
          EnumerateChildren(frame, childs);
          for (wxWindow *child : childs) {
            auto exists = cache.find(child);
            if (exists != cache.end())
              continue;
            cache.emplace(child);
            evt->SetEventObject(child);
            wxPostEvent(child, *evt);
          }
        });
        delete evt;
      }
    } while (0);
    if (!open_.load())
      break;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  } while (1);
}
/////////////////////////////////////////////////////////////////////////////
wxIMPLEMENT_APP_NO_MAIN(App);

wxDEFINE_EVENT(wxEVT_NotifyType, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_NotifyRecordComp, wxCommandEvent);

const int wxAppThreadEvt_FrameDestroy = wxNewId();
const int wxAppThreadEvt_BroadcastEvent = wxNewId();
const int wxAppThreadEvt_ScreenShotFinished = wxNewId();
const int wxAppThreadEvt_ScreenShotClose = wxNewId();
const int wxAppThreadEvt_RecordingBoxSelection = wxNewId();
const int wxAppThreadEvt_WorkSpaceModeChanged = wxNewId();
const int wxAppThreadEvt_RecordingBoxSelectionFinished = wxNewId();
