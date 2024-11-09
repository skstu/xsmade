#include "config.h"
wxBEGIN_EVENT_TABLE(Frame, wxFrame) EVT_SIZE(Frame::OnSize)
    EVT_CLOSE(Frame::OnClose) wxEND_EVENT_TABLE();

Frame::Frame(wxWindow *parent, wxWindowID id, const wxString &title,
             const wxPoint &pos, const wxSize &size, long style,
             const wxString &name)
    : wxFrame(parent, id, title, pos, size, style, name) {
  gauge_ = new wxGauge(this, wxID_ANY, 10000);
  gauge_->Show(false);
  gauge_->SetValue(0);
}
Frame::~Frame() {
}

void Frame::OnSize(wxSizeEvent &evt) {

  evt.Skip();
}
void Frame::OnClose(wxCloseEvent &evt) {
  evt.Skip();
}
