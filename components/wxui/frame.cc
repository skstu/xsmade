#include "wxui.h"

wxBEGIN_EVENT_TABLE(Frame, wxFrame) EVT_SIZE(Frame::OnSize)
    EVT_CLOSE(Frame::OnClose) wxEND_EVENT_TABLE();

Frame::Frame(wxWindow *parent, wxWindowID id, const wxString &title,
             const wxPoint &pos, const wxSize &size, long style,
             const wxString &name)
    : FrameBase(parent, id, title, pos, size, style, name) {
}

Frame::~Frame() {
}
void Frame::OnSize(wxSizeEvent &) {
}
void Frame::OnClose(wxCloseEvent &wxEvt) {
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
