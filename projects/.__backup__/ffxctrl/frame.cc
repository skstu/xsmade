#include "config.h"

#if 0
wxBEGIN_EVENT_TABLE(Frame, wxFrame) EVT_SIZE(Frame::OnSize)
    EVT_CLOSE(Frame::OnClose)
        EVT_AUINOTEBOOK_BEGIN_DRAG(wxID_ANY, Frame::OnPageDrag)
            wxEND_EVENT_TABLE();

Frame::Frame(wxWindow *parent, wxWindowID id, const wxString &title,
             const wxPoint &pos /*= wxDefaultPosition*/,
             const wxSize &size /*= wxDefaultSize*/,
             long style /*= wxDEFAULT_FRAME_STYLE*/,
             const wxString &name /*= wxASCII_STR(wxFrameNameStr)*/)
    : wxFrame(parent, id, title, pos, size, style, name) {
  auimnager_.SetManagedWindow(this);

  auto nb = CreateNotebook();
  auimnager_.AddPane(
      nb,
      wxAuiPaneInfo().Name("notebook_content").CenterPane().PaneBorder(false));

  auimnager_.Update();
}

Frame::~Frame() {
}
void Frame::OnPageDrag(wxAuiNotebookEvent &wxEvent) {
  if (wxEvent.GetSelection() == 0) {
    wxEvent.Veto(); // 阻止拖动
  }
}
void Frame::OnSize(wxSizeEvent &wxEvent) {

  wxEvent.Skip();
}
void Frame::OnClose(wxCloseEvent &wxEvent) {
  int res = wxMessageBox(L"Are you sure you want to exit system?", L"Memade®",
                         wxYES_NO, this);
  if (res != wxYES) {
    wxEvent.Veto();
  } else {
    auto handle = wxApp::GetInstance();
    if (handle) {
      wxQueueEvent(
          handle, new wxThreadEvent(wxEVT_THREAD, wxAppThreadEvt_FrameDestroy));
    }
    wxEvent.Skip();
  }
}

wxAuiNotebook *Frame::CreateNotebook() const {
  const wxSize client_size = GetClientSize();
  auto nodebook =
      new wxAuiNotebook(wxDynamicCast(this, wxWindow), wxID_ANY,
                        wxDefaultPosition, wxSize(client_size.x, client_size.y),
                        wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_DEFAULT_STYLE);
  nodebook->Freeze();
  nodebook->SetArtProvider(new wxAuiSimpleTabArt);
  // wxBitmapBundle page_bmp = wxArtProvider::GetBitmapBundle(wxART_NORMAL_FILE,
  // wxART_OTHER, wxSize(16, 16));

  for (int i = 0; i < 100; ++i) {
    nodebook->AddPage(new wxWindow(wxDynamicCast(nodebook, wxWindow), wxID_ANY),
                      wxString::Format(wxT("%d"), i), false);
    nodebook->SetPageToolTip(i, wxString::Format(wxT("%d"), i));
  }

  wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
  // sizer->Add(new wxWindow(nullptr, 0), wxSizerFlags::)
  nodebook->Thaw();
  return nodebook;
}
/*
WXLRESULT
UIWxFrame::MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) {
                switch (nMsg) {
                case WM_CLOSE: {
                } break;
                case WM_SHOWWINDOW: {
                } break;
                default:
                                break;
                }
                return UIWxFrame::MSWWindowProc(nMsg, wParam, lParam);
}*/

#endif