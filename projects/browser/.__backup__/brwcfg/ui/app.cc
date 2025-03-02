#include "ui.h"
using namespace ui;
IApp::IApp() {
}
IApp::~IApp() {
}
bool IApp::OnInit() {
  bool result = false;
  do {
    if (!wxApp::OnInit())
      break;
    auto global = Global::Create();
    wxEvtHandler::Bind(wxEVT_THREAD, &IApp::OnDestroy, this,
                       wxAppEvent_Destroy);

    result = OnCreate();
  } while (0);
  return result;
}
int IApp::OnExit() {
  int result = 0;
  do {
    wxEvtHandler::Unbind(wxEVT_THREAD, &IApp::OnDestroy, this,
                         wxAppEvent_Destroy);
    result = wxApp::OnExit();
  } while (0);
  Global::Destroy();
  return result;
}
void IApp::NotifyAppDestroy() {
  auto app = wxApp::GetInstance();
  do {
    if (!app)
      break;
    wxQueueEvent(app, new wxThreadEvent(wxEVT_THREAD, wxAppEvent_Destroy));
  } while (0);
}
void IApp::OnDestroy(wxThreadEvent &evt) {
  ExitMainLoop();
}
bool IApp::OnCreate() {
  bool result = false;
  do {
#if 0
    frame_ = new IFrame(nullptr, wxID_ANY);
#endif
    frame_ = new FrameActivate(nullptr, wxID_ANY);
    frame_->Center();
    frame_->Show();
    result = true;
  } while (0);
  return result;
}
/////////////////////////////////////////////////////////////////////////////////////
wxIMPLEMENT_APP_NO_MAIN(IApp);
const int wxAppEvent_Destroy = wxNewId();