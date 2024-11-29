#if !defined(__C431D9C4_3CA8_4270_8548_883BCF6F8E32__)
#define __C431D9C4_3CA8_4270_8548_883BCF6F8E32__

class ShapeFrame final : public FrameBase {
public:
  ShapeFrame(wxWindow *parent, wxWindowID id = wxID_ANY,
             const wxString &title = wxEmptyString,
             const wxPoint &pos = wxDefaultPosition,
             const wxSize &size = wxDefaultSize,
             long style = wxDEFAULT_FRAME_STYLE,
             const wxString &name = wxASCII_STR(wxFrameNameStr));
  virtual ~ShapeFrame();

public:
  bool SetTheme(const wxui::tfThemeIdentify &theme_identify);

private:
  void OnErase(wxEraseEvent &);
  void OnPaint(wxPaintEvent &);
  void OnSize(wxSizeEvent &);
  void OnClose(wxCloseEvent &);
  void OnMotion(wxMouseEvent &);
  void OnLeftDown(wxMouseEvent &);
  void OnLeftUp(wxMouseEvent &);
  void OnRightDown(wxMouseEvent &);
  void OnRightUp(wxMouseEvent &);
  void OnMouseLost(wxMouseCaptureLostEvent &);
  void OnEnterWindow(wxMouseEvent &);
  void OnLeaveWindow(wxMouseEvent &);
  void OnContextMenu(wxContextMenuEvent &);
  void OnToolbarEvent(wxCommandEvent&);
protected:
  bool SetShape(const wxImage &img);

public:
  void SetRegion(long x, long y, long cx, long cy) override;

protected:
  wxMenu m_MouseRightPopupMenu;
  wxPoint m_offset{-1, -1};
  wxRect m_rect{0, 0, 0, 0};
  Theme *theme_ = nullptr;

private:
#if _WIN32
  const int region_offset_x_ = -1; //!@ px
  const int region_offset_y_ = -1; //!@ px
#else
  const int region_offset_x_ = 0; //!@ px
  const int region_offset_y_ = 0; //!@ px
#endif
  DECLARE_EVENT_TABLE()
};

/// /*_ Memade®（新生™） _**/
/// /*_ Thu, 28 Nov 2024 05:23:27 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__C431D9C4_3CA8_4270_8548_883BCF6F8E32__