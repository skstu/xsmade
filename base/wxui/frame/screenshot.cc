#include <wxui.h>
FrameScreenShot::FrameScreenShot()
    : IFrameComponent(FrameComponentType::SCREENSHOT) {
  Init();
}
FrameScreenShot::~FrameScreenShot() {
  UnInit();
}
void FrameScreenShot::Init() {
  auto app = wxDynamicCast(wxApp::GetInstance(), App);
  frame_background_ = new Background(nullptr);
  app->FrameAppend(ComponentFrameType::SCREENSHOT_BACKGROUND,
                   dynamic_cast<wxFrame *>(frame_background_));
  frame_toolbar_ = new Toolbar(nullptr);
  app->FrameAppend(ComponentFrameType::SCREENSHOT_TOOLBAR,
                   dynamic_cast<wxFrame *>(frame_toolbar_));
  frame_workspace_ = new WorkSpace(nullptr);
  app->FrameAppend(ComponentFrameType::SCREENSHOT_WORKSPACE,
                   dynamic_cast<wxFrame *>(frame_workspace_));
}
void FrameScreenShot::UnInit() {
  frame_toolbar_->Show(false);
  frame_workspace_->Show(false);
  frame_background_->Show(false);
}
void FrameScreenShot::ShowBackground(const bool &flag) {
  if (flag) {
    frame_toolbar_->Show(false);
    frame_workspace_->Show(false);
  }
  frame_background_->Show(flag);
}
void FrameScreenShot::Show(const bool &flag) {
  frame_toolbar_->Show(flag);
  frame_workspace_->Show(flag);
}
void FrameScreenShot::Center() const {
}
void FrameScreenShot::SetPos(const wxRect &pos) {
  do {
    if (!frame_workspace_ || !frame_toolbar_)
      break;
    frame_workspace_->SetSize(pos);

    wxRect frame_toolbar_rect;
    frame_toolbar_rect.SetLeft(pos.GetRight() -
                               frame_toolbar_->GetSize().GetWidth());
    frame_toolbar_rect.SetTop(pos.GetBottom());
    frame_toolbar_rect.SetRight(pos.GetRight());
    frame_toolbar_rect.SetBottom(pos.GetBottom() +
                                 frame_toolbar_->GetSize().GetHeight());
    frame_toolbar_->SetSize(frame_toolbar_rect);
    if (!frame_toolbar_->IsShown())
      frame_toolbar_->Show();
  } while (0);
}
