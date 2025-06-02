#include "brwcfg.h"
#if ENABLE_WXUI
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

    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtDrawToolActivate, this,
                       wxAppThreadEvt_DrawToolActivate);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtBroadcastEvent, this,
                       wxAppThreadEvt_BroadcastEvent);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtFrameDestroy, this,
                       wxAppThreadEvt_FrameDestroy);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtScreenShotFinished, this,
                       wxAppThreadEvt_ScreenShotFinished);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtScreenShotFinalSuccess,
                       this, wxAppThreadEvt_ScreenShotFinalSuccess);
    wxEvtHandler::Bind(wxEVT_THREAD, &App::OnThreadEvtScreenShotClose, this,
                       wxAppThreadEvt_ScreenShotClose);
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
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtDrawToolActivate, this,
                         wxAppThreadEvt_DrawToolActivate);
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtFrameDestroy, this,
                         wxAppThreadEvt_FrameDestroy);
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtScreenShotFinished,
                         this, wxAppThreadEvt_ScreenShotFinished);
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtScreenShotFinalSuccess,
                         this, wxAppThreadEvt_ScreenShotFinalSuccess);
    wxEvtHandler::Unbind(wxEVT_THREAD, &App::OnThreadEvtScreenShotClose, this,
                         wxAppThreadEvt_ScreenShotClose);
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
// void App::SetParent(void *parent) {
//   parent_ = parent;
// }
void App::OnThreadEvtDrawToolActivate(wxThreadEvent &evt) {
  auto sss = 0;
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
    // frame_ = new Frame(nullptr);
    // static wxWindow *wxParent = nullptr;
    // if (parent_) {
    //   wxWindow *wxParent = new wxWindow();
    //   wxParent->SetHWND(reinterpret_cast<HWND>(parent_)); // 绑定 HWND
    //   wxParent->AdoptAttributesFromHWND();                // 继承窗口属性
    //   wxParent->Reparent(nullptr); // 解除 wxWidgets 父窗口绑定
    // }
    frame_ = wxDynamicCast(new IFrame(nullptr), wxFrame);
    frame_->Center();
    // if (parent_) {
    //   HWND hwnd = reinterpret_cast<HWND>(parent_);
    //   //::SetParent(frame_->GetHWND(), ::GetAncestor(hwnd, GA_ROOT));
    // }
    Wxui::Create()->GetReadySignal()->notify();
    frame_->Show();
  } while (0);
}
wxFrame *App::FrameGet() const {
  return frame_;
}
void App::OnThreadEvtScreenShotClose(wxThreadEvent &evt) {
  do {
#if 0
    wxRect screenshot_region;
    for (auto &node : frame_comps_) {
      switch (node.first) {
      case FrameComponentType::RECORDING: {
        // node.second->Center();
        node.second->Show(false);
        node.second->ShowBackground(true);
      } break;
      case FrameComponentType::SCREENSHOT: {
        node.second->Show(false);
      } break;
      default:
        break;
      }
    }
#endif
  } while (0);
}
void App::OnThreadEvtScreenShotFinalSuccess(wxThreadEvent &evt) {
  do {
#if 0
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

    if (Config::Get()->OnScreenShot(screenshot_image_stream)) {
      wxMessageBox(wxT("截图成功!"), wxT("提示"), wxOK | wxICON_INFORMATION);
    } else {
      wxMessageBox(wxT("截图失败!"), wxT("提示"), wxOK | wxICON_ERROR);
    }
#if 0
    screenshot_component->SetWorkSpace(screenshot_image_stream);
    // screenshot_component->Center();
    screenshot_component->SetPos(screenshot_region);
    screenshot_component->Show(true);
#endif
#endif
  } while (0);
}
void App::OnThreadEvtScreenShotFinished(wxThreadEvent &evt) {
  do {
#if 0
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
    // screenshot_component->Center();
    screenshot_component->SetPos(screenshot_region);
    screenshot_component->Show(true);
#endif
  } while (0);
}
void App::OnThreadEvtRecordingBoxSelectionFinished(wxThreadEvent &evt) {
  do {
#if 0
    wxCommandEvent *cmdevt =
        reinterpret_cast<wxCommandEvent *>(evt.GetEventObject());
    if (!cmdevt)
      break;
    MessageBoxA(NULL, "0", NULL, 0);
    wxString rectJson = cmdevt->GetString();
    if (rectJson.empty())
      break;
    MessageBoxA(NULL, "0", NULL, 0);
    std::string jsonStringU8 = rectJson.ToStdString();
    rapidjson::Document doc;
    if (doc.Parse(jsonStringU8.c_str()).HasParseError())
      break;
    if (!doc.IsObject())
      break;
    if (!doc.HasMember("x") || !doc.HasMember("y") || !doc.HasMember("width") ||
        !doc.HasMember("height"))
      break;
    MessageBoxA(NULL, "0", NULL, 0);
    wxRect pos;
    pos.x = doc["x"].GetInt();
    pos.y = doc["y"].GetInt();
    pos.width = doc["width"].GetInt();
    pos.height = doc["height"].GetInt();
    pos.SetLeft(pos.x);
    pos.SetTop(pos.y);
    pos.SetRight(pos.x + pos.width);
    pos.SetBottom(pos.y + pos.height);
    MessageBoxA(NULL, "1", NULL, 0);
    IFrameComponent *record_component = nullptr;
    auto found = frame_comps_.find(FrameComponentType::RECORDING);
    if (found == frame_comps_.end()) {
      MessageBoxA(NULL, "2", NULL, 0);
      break;
    }

    wxRect pos_prev(pos);
    if (pos.width < 0 || pos.height < 0) {
      pos.SetLeft(pos.x + pos.width);
      pos.SetTop(pos.y + pos.height);
      pos.SetRight(pos_prev.x);
      pos.SetBottom(pos_prev.y);
    }
    std::string msg =
        fmt::format("l({}),t({}),r({}),b({})", pos.GetLeft(), pos.GetTop(),
                    pos.GetRight(), pos.GetBottom());
    MessageBoxA(NULL, msg.c_str(), NULL, 0);
    record_component = found->second;
    record_component->SetPos(pos);
    record_component->Show(true);
#endif
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
const int wxAppThreadEvt_DrawToolActivate = wxNewId();
const int wxAppThreadEvt_FrameDestroy = wxNewId();
const int wxAppThreadEvt_BroadcastEvent = wxNewId();
const int wxAppThreadEvt_ScreenShotFinished = wxNewId();
const int wxAppThreadEvt_ScreenShotFinalSuccess = wxNewId();
const int wxAppThreadEvt_ScreenShotClose = wxNewId();
const int wxAppThreadEvt_RecordingBoxSelection = wxNewId();
const int wxAppThreadEvt_WorkSpaceModeChanged = wxNewId();
const int wxAppThreadEvt_RecordingBoxSelectionFinished = wxNewId();
#endif