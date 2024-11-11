#include "config.h"
wxBEGIN_EVENT_TABLE(Frame, wxFrame) EVT_SIZE(Frame::OnSize)
    EVT_CLOSE(Frame::OnClose) wxEND_EVENT_TABLE();

Frame::Frame(wxWindow *parent, wxWindowID id, const wxString &title,
             const wxPoint &pos, const wxSize &size, long style,
             const wxString &name)
    : wxFrame(parent, id, title, pos, size, style, name) {
  wxPanel *panel = new wxPanel(this, wxID_ANY);
  // 创建一个垂直 sizer
  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
  gauge_ = new wxGauge(panel, wxID_ANY, 10000, wxDefaultPosition);
  gauge_->Show(true);
  gauge_->SetValue(500);

  sizer->Add(new wxWindow(panel, wxID_ANY), 1, wxALL | wxEXPAND, 5);
  sizer->Add(gauge_, 1, wxALL | wxEXPAND, 5);

  // 应用 sizer 到 panel 上
  panel->SetSizer(sizer);
  sizer->Fit(panel);
}
Frame::~Frame() {
}

void Frame::OnSize(wxSizeEvent &evt) {

  evt.Skip();
}
void Frame::OnClose(wxCloseEvent &evt) {
  evt.Skip();
}
