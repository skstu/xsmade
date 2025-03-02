#if !defined(__25F4F375_165B_4BD0_A893_E842319709EB__)
#define __25F4F375_165B_4BD0_A893_E842319709EB__

class TransparentFrame : public wxFrame {
public:
  TransparentFrame()
      : wxFrame(nullptr, wxID_ANY, "Transparent Frame", wxPoint(0, 0),
                wxSize(800, 600),
                wxFRAME_SHAPED | wxSTAY_ON_TOP) // 设置为透明框架
  {
    // 设置框架透明度
    SetTransparent(150); // 半透明效果
    Show(true);

    // 在透明框架内创建一个面板或控件
    auto panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0),
                             wxSize(GetSize().GetWidth(), 30));
    panel->SetBackgroundColour(wxColour(255, 255, 255)); // 面板的背景颜色
    panel->Show(true);
  }
};

class ToolbarFrame : public wxFrame {
public:
  ToolbarFrame()
      : wxFrame(nullptr, wxID_ANY, "Toolbar Frame", wxPoint(0, 0),
                wxSize(800, 50),
                wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX) // 不允许最大化框架
  {
    // 设置工具栏框架的背景颜色（不透明）
    SetBackgroundColour(wxColour(0, 0, 255)); // 设置背景为蓝色

    // 在工具栏框架内添加控件（例如按钮）
    auto button =
        new wxButton(this, wxID_ANY, "Toolbar Button", wxPoint(10, 10));
    button->Show(true);
    Show(true);
  }
};

#if 0
class Frame : public wxFrame {
public:
  Frame(wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE /* wxNO_BORDER | wxFRAME_SHAPED*/,
        const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~Frame();

private:
  wxToolBar *m_pToolbarMain = nullptr;
  wxMenuBar *m_pMenuMain = nullptr;
  wxStatusBar *m_pStatusbarMain = nullptr;

  wxAuiNotebook *CreateNotebook() const;
  wxAuiManager auimnager_;

private:
  void OnSize(wxSizeEvent &);
  void OnClose(wxCloseEvent &);
  void OnPageDrag(wxAuiNotebookEvent &);
  /*WXLRESULT
  MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) override final;*/
  wxDECLARE_EVENT_TABLE();
};
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 27 Nov 2024 05:13:21 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__25F4F375_165B_4BD0_A893_E842319709EB__