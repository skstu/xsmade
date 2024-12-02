#include "wxui.h"
void Global::ffxLayout() {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(
        wxDynamicCast(wxApp::GetInstance(), App)->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    wxRect rtWindow = frame_tool->GetRect();
    frame_work->SetSize(rtWindow.GetLeft(),
                        rtWindow.GetTop() + rtWindow.GetHeight(),
                        rtWindow.GetWidth(), frame_work->GetSize().GetHeight());
#if 0  
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    auto frame = app->FrameWorkGet();
    if (!frame)
      break;
    wxRect rtWindow = GetRect();
#if 0
    frame->SetRegion(rtWindow.GetLeft(),
                     rtWindow.GetTop() + rtWindow.GetHeight(),
                     rtWindow.GetWidth(),
                     dynamic_cast<wxFrame *>(frame)->GetSize().GetHeight());
#else
    dynamic_cast<wxFrame *>(frame)->SetSize(
        rtWindow.GetLeft(), rtWindow.GetTop() + rtWindow.GetHeight(),
        rtWindow.GetWidth(),
        dynamic_cast<wxFrame *>(frame)->GetSize().GetHeight());
#endif
#endif
  } while (0);
}
void Global::ffxFullScreen(const bool &entry, const wxSize &prev_frame_tool,
                           const wxSize &perv_frame_shape) {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(
        wxDynamicCast(wxApp::GetInstance(), App)->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    if (entry) {
      frame_tool->SetPosition(wxPoint(0, 0));
      wxDisplay display;
      wxRect workArea = display.GetClientArea();
      wxSize current = frame_tool->GetSize();
      frame_tool->SetSize(workArea.GetSize().GetWidth(), current.GetHeight());
      frame_work->SetSize(workArea.GetSize().GetWidth(),
                          workArea.GetSize().GetHeight() -
                              frame_tool->GetSize().GetHeight());
    } else {
      frame_work->SetSize(prev_frame_tool.GetWidth(),
                          perv_frame_shape.GetHeight());
      frame_tool->SetSize(prev_frame_tool.GetWidth(),
                          frame_tool->GetSize().GetHeight());
    }
  } while (0);
}
void Global::ffxShowWindow(const bool &flag) {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(
        wxDynamicCast(wxApp::GetInstance(), App)->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    if (flag) {
      if (!frame_work->IsShown())
        frame_work->Show(flag);
    } else {
      if (frame_work->IsShown())
        frame_work->Show(flag);
    }
    if (flag) {
      if (!frame_tool->IsShown())
        frame_tool->Show(flag);
    } else {
      if (frame_tool->IsShown())
        frame_tool->Show(flag);
    }
    if (flag) {
#if defined(__OSWIN__)
      SetWindowPos(frame_tool->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0,
                   SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
      SetWindowPos(frame_work->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0,
                   SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#endif
    }
  } while (0);
}
void Global::ffxScaling(const float &scaling) {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(
        wxDynamicCast(wxApp::GetInstance(), App)->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    wxSize sizeShape = frame_work->GetSize();
    wxSize sizeTool = frame_tool->GetSize();
    wxPoint ptTool = frame_tool->GetPosition();
    int tool_old_x = ptTool.x;
    int tool_old_y = ptTool.y;
    int tool_old_cx = sizeTool.GetWidth();
    int tool_old_cy = sizeTool.GetHeight();

    int final_tool_cx = sizeTool.GetWidth() * scaling;
    int final_tool_cy = sizeTool.GetHeight();
    int final_shape_cx = final_tool_cx;
    int final_shape_cy = sizeShape.GetHeight() * scaling;
    int final_pos_x =
        tool_old_x - static_cast<int>((final_tool_cx - tool_old_cx) / 2);
    int final_pos_y =
        tool_old_y - static_cast<int>((final_tool_cy - tool_old_cy) / 2);

    frame_work->SetSize(wxSize(final_shape_cx, final_shape_cy));
    frame_tool->SetPosition(wxPoint(final_pos_x, final_pos_y));
    frame_tool->SetSize(wxSize(final_tool_cx, final_tool_cy));
  } while (0);
}
void Global::ffxTopmost() {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(
        wxDynamicCast(wxApp::GetInstance(), App)->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
#if defined(__OSWIN__)
    SetWindowPos(frame_tool->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    SetWindowPos(frame_work->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#endif
  } while (0);
}
void Global::ffxCenter() {
  do {
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(
        wxDynamicCast(wxApp::GetInstance(), App)->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    frame_work->Center();
    wxRect rect = frame_work->GetRect();
    frame_tool->SetSize(rect.GetLeft(),
                        rect.GetTop() - frame_tool->GetSize().GetHeight(),
                        rect.GetWidth(), frame_tool->GetSize().GetHeight());
  } while (0);
}
void Global::ffxSetPos(const wxRect &rect) {
  do {
    if (rect.GetWidth() < 100 || rect.GetHeight() < 100)
      break;
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    wxFrame *frame_tool = dynamic_cast<wxFrame *>(app->FrameToolGet());
    wxFrame *frame_work = dynamic_cast<wxFrame *>(
        wxDynamicCast(wxApp::GetInstance(), App)->FrameWorkGet());
    if (!frame_work || !frame_tool)
      break;
    frame_work->SetSize(frame_work->GetPosition().x,
                        frame_work->GetPosition().y, rect.GetWidth(),
                        rect.GetHeight());
    frame_tool->SetSize(rect.GetLeft(),
                        rect.GetTop() - frame_tool->GetSize().GetHeight(),
                        rect.GetWidth(), frame_tool->GetSize().GetHeight());

  } while (0);
}