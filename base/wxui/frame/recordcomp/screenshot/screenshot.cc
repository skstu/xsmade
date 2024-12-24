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
  font_toolbar_ = new FontToolbar(nullptr);
  app->FrameAppend(ComponentFrameType::SCREENSHOT_TOOLBAR_FONT,
                   dynamic_cast<wxFrame *>(font_toolbar_));
  frame_workspace_ = new WorkSpace(nullptr);
  app->FrameAppend(ComponentFrameType::SCREENSHOT_WORKSPACE,
                   dynamic_cast<wxFrame *>(frame_workspace_));
}
void FrameScreenShot::UnInit() {
  font_toolbar_->Show(false);
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
wxRect FrameScreenShot::GetRegion() const {
  wxRect result;
  do {
    if (!frame_toolbar_ || !frame_workspace_)
      break;
    wxRect rt_toolbar = frame_toolbar_->GetRect();
    wxRect rt_workspace = frame_workspace_->GetRect();

    result.SetLeft(rt_toolbar.GetLeft());
    result.SetTop(rt_toolbar.GetTop());
    result.SetRight(rt_toolbar.GetRight());
    result.SetBottom(rt_workspace.GetBottom());
  } while (0);
  return result;
}
void FrameScreenShot::SetWorkSpace(const std::string &imageStream) {
  do {
    if (imageStream.empty())
      break;
    wxImage *img = nullptr;
    if (!wxComm::LoadImgFormStream(imageStream, &img) || !img)
      break;
    if (!frame_workspace_)
      break;
    frame_workspace_->SetImage(img);
    // SK_DELETE_PTR(img);
  } while (0);
}
void FrameScreenShot::Show(const bool &flag) {
  frame_toolbar_->Show(flag);
  frame_workspace_->Show(flag);
}
void FrameScreenShot::Center() const {
  do {
    if (!frame_workspace_)
      break;
    frame_workspace_->Center();

  } while (0);
}
void FrameScreenShot::SetPos(const wxRect &pos) {
  do {
    if (!frame_workspace_ || !frame_toolbar_)
      break;
    frame_workspace_->SetSize(pos);

    wxRect frame_toolbar_rect;
    frame_toolbar_rect.SetLeft(pos.GetRight() -
                               frame_toolbar_->GetSize().GetWidth());
    frame_toolbar_rect.SetTop(pos.GetBottom() + 2);
    frame_toolbar_rect.SetRight(pos.GetRight());
    frame_toolbar_rect.SetBottom(frame_toolbar_rect.GetTop() +
                                 frame_toolbar_->GetSize().GetHeight());
    frame_toolbar_->SetSize(frame_toolbar_rect);
    if (!frame_toolbar_->IsShown())
      frame_toolbar_->Show();
  } while (0);
}
void FrameScreenShot::OnWorkspacePosUpdate(const wxRect &rect) {
  do {
    if (!frame_toolbar_)
      break;
    frame_toolbar_->SetSize(
        rect.GetRight() - frame_toolbar_->GetSize().GetWidth(),
        rect.GetBottom(), frame_toolbar_->GetSize().GetWidth(),
        frame_toolbar_->GetSize().GetHeight());
    if (!frame_toolbar_->IsShown())
      frame_toolbar_->Show();
  } while (0);
}