#include <wxui.h>
FrameRecording::FrameRecording()
    : IFrameComponent(FrameComponentType::RECORDING) {
  Init();
}
FrameRecording::~FrameRecording() {
  UnInit();
}
void FrameRecording::Init() {
  auto app = wxDynamicCast(wxApp::GetInstance(), App);
  frame_background_ = new Background(nullptr);
  app->FrameAppend(ComponentFrameType::RECORDING_BACKGROUND,
                   dynamic_cast<wxFrame *>(frame_background_));
  frame_toolbar_ = new Toolbar(nullptr);
  app->FrameAppend(ComponentFrameType::RECORDING_TOOLBAR,
                   dynamic_cast<wxFrame *>(frame_toolbar_));
  frame_workspace_ = new WorkSpace(nullptr);
  app->FrameAppend(ComponentFrameType::RECORDING_WORKSPACE,
                   dynamic_cast<wxFrame *>(frame_workspace_));
}
void FrameRecording::UnInit() {
  frame_toolbar_->Show(false);
  frame_workspace_->Show(false);
  frame_background_->Show(false);
}
void FrameRecording::ShowBackground(const bool &flag) {
  frame_background_->Show(flag);
}
void FrameRecording::Show(const bool &flag) {
  if (!frame_toolbar_ || !frame_workspace_ || !frame_background_)
    return;
  show_status_.store(flag);
  if (flag) {
    if (!frame_toolbar_->IsShown())
      frame_toolbar_->Show(true);
    if (!frame_workspace_->IsShown())
      frame_workspace_->Show(true);
    // if (!frame_background_->IsShown())
    //   frame_background_->Show(true);
  } else {
    if (frame_toolbar_->IsShown())
      frame_toolbar_->Show(false);
    if (frame_workspace_->IsShown())
      frame_workspace_->Show(false);
    if (frame_background_->IsShown())
      frame_background_->Show(false);
  }
}
void FrameRecording::Center() const {
  do {
    if (!frame_toolbar_ || !frame_workspace_ || !frame_background_)
      break;
    frame_workspace_->Center();
    wxRect rect = frame_workspace_->GetRect();
    frame_toolbar_->SetSize(
        rect.GetLeft(), rect.GetTop() - frame_toolbar_->GetSize().GetHeight(),
        rect.GetWidth(), frame_toolbar_->GetSize().GetHeight());
  } while (0);
}
void FrameRecording::OnPosChanged() const {
}
void FrameRecording::OnFullScreenShown() {
}
