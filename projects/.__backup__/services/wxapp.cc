#include "config.h"

App::App() {
}
App::~App() {
}

bool App::OnInit() {
  bool result = false;
  do {
    if (!wxApp::OnInit())
      break;
#ifdef _WIN32
    SetProcessDPIAware();
#endif
    //wxAppBase::SetExitOnFrameDelete(false);
    frame_ =
        dynamic_cast<Frame *>(new Frame(nullptr, wxID_ANY, wxString(L"")));
    frame_->Show(true);

    result = true;
  } while (0);
  return result;
}
int App::OnExit() {
  int result = 0;
  do {

    result = wxApp::OnExit();
  } while (0);
  return result;
}

/////////////////////////////////////////////////////////////////////////////
wxDECLARE_APP(App);
wxIMPLEMENT_APP(App);