#include "wxui.h"

wxBEGIN_EVENT_TABLE(FrameToolbar, wxFrame) EVT_SIZE(FrameToolbar::OnSize)
    EVT_MOVE(FrameToolbar::OnMove) EVT_CLOSE(FrameToolbar::OnClose)
        EVT_MOTION(FrameToolbar::OnMouseMove)
            EVT_LEFT_DOWN(FrameToolbar::OnMouseLeftDown)
                EVT_LEFT_UP(FrameToolbar::OnMouseLeftUp) wxEND_EVENT_TABLE();

FrameToolbar::FrameToolbar(wxWindow *parent, wxWindowID id,
                           const wxString &title, const wxPoint &pos,
                           const wxSize &size, long style, const wxString &name)
    : FrameBase(parent, id, title, wxPoint(0, 0), wxSize(640, 40),
                /*(wxDEFAULT_FRAME_STYLE & ~wxCLOSE_BOX & ~wxCAPTION)*/
                wxNO_BORDER | wxFRAME_NO_TASKBAR /*| wxRESIZE_BORDER*/, name) {

  SetBackgroundColour(wxColour(0xFF, 0xFF, 0xFF));

  wxImage *img = Config::Get()->GetResImage("btn_close.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_close_ =
        new wxBitmapButton(this, wxID_ANY, wxBitmapBundle::FromImage(*img));
    btn_close_->SetSize(wxSize(btn_size, btn_size));
  }
  // img = Config::Get()->GetResImage("btn_edit.png");
  // if (img) {
  //   img->Rescale(btn_size, btn_size);
  //   btn_edit_ =
  //       new wxBitmapButton(this, wxID_ANY, wxBitmapBundle::FromImage(*img));
  //   btn_edit_->SetSize(wxSize(btn_size, btn_size));
  // }
  img = Config::Get()->GetResImage("btn_recording_start.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_recording_start_ =
        new wxBitmapButton(this, wxID_ANY, wxBitmapBundle::FromImage(*img));
    btn_recording_start_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_recording_stop.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_recording_stop_ =
        new wxBitmapButton(this, wxID_ANY, wxBitmapBundle::FromImage(*img));
    btn_recording_stop_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_scaling_down.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_scaling_down_ = new wxBitmapButton(this, BTN_SCALING_DOWN,
                                           wxBitmapBundle::FromImage(*img));
    btn_scaling_down_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_scaling_up.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_scaling_up_ = new wxBitmapButton(this, BTN_SCALING_UP,
                                         wxBitmapBundle::FromImage(*img));
    btn_scaling_up_->SetSize(wxSize(btn_size, btn_size));
  }
  img = Config::Get()->GetResImage("btn_settings.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_settings_ =
        new wxBitmapButton(this, wxID_ANY, wxBitmapBundle::FromImage(*img));
    btn_settings_->SetSize(wxSize(btn_size, btn_size));
  }
  // img = Config::Get()->GetResImage("btn_window.png");
  // if (img) {
  //   img->Rescale(btn_size, btn_size);
  //   btn_window_ =
  //       new wxBitmapButton(this, wxID_ANY, wxBitmapBundle::FromImage(*img));
  //   btn_window_->SetSize(wxSize(btn_size, btn_size));
  // }
  img = Config::Get()->GetResImage("btn_screenshot.png");
  if (img) {
    img->Rescale(btn_size, btn_size);
    btn_screenshot_ =
        new wxBitmapButton(this, wxID_ANY, wxBitmapBundle::FromImage(*img));
    btn_screenshot_->SetSize(wxSize(btn_size, btn_size));
  }
  Loyout();
  SetWindowPos(GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  Bind(wxEVT_BUTTON, &FrameToolbar::OnToolbarEvent, this);
}
FrameToolbar::~FrameToolbar() {
  Unbind(wxEVT_BUTTON, &FrameToolbar::OnToolbarEvent, this);
}
void FrameToolbar::Loyout() {
  wxSize cursize = GetSize();
  wxPoint curpt = GetPosition();
  if (btn_close_) {
    btn_close_->SetPosition(wxPoint(
        cursize.GetWidth() - btn_size - btn_offset_x_ * 1, btn_offset_y_));
  }
  if (btn_screenshot_) {
    btn_screenshot_->SetPosition(wxPoint(
        cursize.GetWidth() - btn_size * 2 - btn_offset_x_ * 2, btn_offset_y_));
  }

  if (btn_recording_start_) {
    btn_recording_start_->SetPosition(wxPoint(
        cursize.GetWidth() - btn_size * 3 - btn_offset_x_ * 3, btn_offset_y_));
  }

  if (btn_settings_) {
    btn_settings_->SetPosition(wxPoint(0 + btn_offset_x_ * 1, btn_offset_y_));
  }

  if (btn_scaling_up_) {
    btn_scaling_up_->SetPosition(
        wxPoint(btn_size * 1 + btn_offset_x_ * 2, btn_offset_y_));
  }
  if (btn_scaling_down_) {
    btn_scaling_down_->SetPosition(
        wxPoint(btn_size * 2 + btn_offset_x_ * 3, btn_offset_y_));
  }

  do { //!@ shape
    auto app = wxDynamicCast(wxApp::GetInstance(), App);
    if (!app)
      break;
    auto frame = app->FrameShapeGet();
    if (!frame)
      break;
    wxRect rtWindow = GetRect();
    frame->SetRegion(rtWindow.GetLeft(),
                     rtWindow.GetTop() + rtWindow.GetHeight(),
                     rtWindow.GetWidth(),
                     dynamic_cast<wxFrame *>(frame)->GetSize().GetHeight());
    dynamic_cast<wxFrame *>(frame)->Show();

  } while (0);
}
void FrameToolbar::OnToolbarEvent(wxCommandEvent &evt) {
  switch (evt.GetId()) {
  case CommandTool::BTN_SCALING_UP: {
    wxFrame *frame_shape = dynamic_cast<wxFrame *>(
        wxDynamicCast(wxApp::GetInstance(), App)->FrameShapeGet());
    if (!frame_shape)
      break;
    wxSize sizeShape = frame_shape->GetSize();
    wxSize sizeTool = GetSize();
    wxPoint ptTool = GetPosition();
    int tool_old_x = ptTool.x;
    int tool_old_y = ptTool.y;
    int tool_old_cx = sizeTool.GetWidth();
    int tool_old_cy = sizeTool.GetHeight();

    int final_tool_cx = sizeTool.GetWidth() * 1.2;
    int final_tool_cy = sizeTool.GetHeight();
    int final_shape_cx = final_tool_cx;
    int final_shape_cy = sizeShape.GetHeight() * 1.2;
    int final_pos_x =
        tool_old_x - static_cast<int>((final_tool_cx - tool_old_cx) / 2);
    int final_pos_y =
        tool_old_y - static_cast<int>((final_tool_cy - tool_old_cy) / 2);

    frame_shape->SetSize(wxSize(final_shape_cx, final_shape_cy));
    SetPosition(wxPoint(final_pos_x, final_pos_y));
    SetSize(wxSize(final_tool_cx, final_tool_cy));
  } break;
  case CommandTool::BTN_SCALING_DOWN: {
    wxFrame *frame_shape = dynamic_cast<wxFrame *>(
        wxDynamicCast(wxApp::GetInstance(), App)->FrameShapeGet());
    if (!frame_shape)
      break;
    wxSize sizeShape = frame_shape->GetSize();
    wxSize sizeTool = GetSize();
    wxPoint ptTool = GetPosition();
    int tool_old_x = ptTool.x;
    int tool_old_y = ptTool.y;
    int tool_old_cx = sizeTool.GetWidth();
    int tool_old_cy = sizeTool.GetHeight();

    int final_tool_cx = sizeTool.GetWidth() * 0.8;
    int final_tool_cy = sizeTool.GetHeight();
    int final_shape_cx = final_tool_cx;
    int final_shape_cy = sizeShape.GetHeight() * 0.8;
    int final_pos_x =
        tool_old_x - static_cast<int>((final_tool_cx - tool_old_cx) / 2);
    int final_pos_y =
        tool_old_y - static_cast<int>((final_tool_cy - tool_old_cy) / 2);

    frame_shape->SetSize(wxSize(final_shape_cx, final_shape_cy));
    SetPosition(wxPoint(final_pos_x, final_pos_y));
    SetSize(wxSize(final_tool_cx, final_tool_cy));
  } break;
  default:
    break;
  }
  evt.Skip();
}
void FrameToolbar::OnSize(wxSizeEvent &event) {
  Loyout();
  event.Skip();
}
void FrameToolbar::OnMove(wxMoveEvent &event) {
  Loyout();
  event.Skip();
}
void FrameToolbar::OnClose(wxCloseEvent &wxEvt) {
  int res = wxMessageBox(L"Are you sure you want to exit system?", L"Memade®",
                         wxYES_NO, this);
  if (res != wxYES) {
    wxEvt.Veto();
  } else {
    auto handle = wxApp::GetInstance();
    if (handle) {
      wxQueueEvent(
          handle, new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_FrameDestroy));
    }
    wxEvt.Skip();
  }
}
void FrameToolbar::OnMouseMove(wxMouseEvent &event) {
  wxPoint pt = event.GetPosition();
  if (event.Dragging() && event.LeftIsDown()) {
    wxPoint pos = ClientToScreen(pt); // pos为点击位置

    Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));
    if (pos.y - m_delta.y <= 0) {
      SetPosition(wxPoint(0, 0));
      wxDisplay display;
      wxRect workArea = display.GetClientArea();
      wxSize current = GetSize();
      SetSize(workArea.GetSize().GetWidth(), current.GetHeight());
    } else {
      SetSize(prev_dragging_size_);
    }
  }
}

void FrameToolbar::OnMouseLeftDown(wxMouseEvent &event) {
  CaptureMouse();
  wxPoint pt = ClientToScreen(event.GetPosition());
  wxPoint origin = GetPosition();
  int dx = pt.x - origin.x;
  int dy = pt.y - origin.y;
  m_delta = wxPoint(dx, dy);
  prev_dragging_size_ = GetSize();
}

void FrameToolbar::OnMouseLeftUp(wxMouseEvent &event) {
  if (HasCapture()) {
    ReleaseMouse();
  }
}
