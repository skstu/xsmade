#include <wxui.h>

class wxFontComboBox : public wxOwnerDrawnComboBox {
public:
  virtual void OnDrawItem(wxDC &dc, const wxRect &rect, int item,
                          int flags) const override {
    if (item == wxNOT_FOUND)
      return;
    wxRect r(rect);
    r.Deflate(3);
    r.height -= 2;

    wxPenStyle penStyle = wxPENSTYLE_SOLID;
    wxPen pen(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT), 1,
              penStyle);
    if (item == 1) {
      pen.SetWidth(3);
    } else if (item == 2) {
      pen.SetWidth(5);
    } else if (item == 3) {
      pen.SetWidth(7);
    } else if (item == 4) {
      pen.SetWidth(10);
    }
    dc.SetPen(pen);

    if (!(flags & wxODCB_PAINTING_CONTROL)) {
      dc.DrawText(GetString(item), r.x + 3,
                  (r.y + 0) + ((r.height / 2) - dc.GetCharHeight()) / 2);
      /*dc.DrawLine(r.x + 5, r.y + ((r.height / 4) * 3), r.x + r.width - 5,
                  r.y + ((r.height / 4) * 3));*/
      /*dc.DrawLine(r.x + 5, r.y + (r.height / 2), r.x + r.width - 5,
                  r.y + (r.height / 2));*/
    } else {
      /*dc.DrawLine(r.x + 5, r.y + r.height / 2, r.x + r.width - 5,
                  r.y + r.height / 2);*/
      /*dc.DrawLine(r.x + 5, r.y + (r.height / 2), r.x + r.width - 5,
                  r.y + (r.height / 2));*/
      dc.DrawText(GetString(item) + wxT(" px"), r.x + 3,
                  (r.y + 0) + ((r.height / 2) - dc.GetCharHeight()) / 2);
    }
  }

  virtual void OnDrawBackground(wxDC &dc, const wxRect &rect, int item,
                                int flags) const override {

    // If item is selected or even, or we are painting the
    // combo control itself, use the default rendering.
    if ((flags & (wxODCB_PAINTING_CONTROL | wxODCB_PAINTING_SELECTED)) ||
        (item & 1) == 0) {
      wxOwnerDrawnComboBox::OnDrawBackground(dc, rect, item, flags);
      return;
    }

    // Otherwise, draw every other background with different colour.
    wxColour bgCol = wxSystemSettings::SelectLightDark(wxColour(240, 240, 250),
                                                       wxColour(48, 48, 64));

    dc.SetBrush(wxBrush(bgCol));
    dc.SetPen(wxPen(bgCol));
    dc.DrawRectangle(rect);
  }

  virtual wxCoord OnMeasureItem(size_t item) const override {
    // Simply demonstrate the ability to have variable-height items
    // return FromDIP(item & 1 ? 36 : 24);
    return FromDIP(20);
  }

  virtual wxCoord OnMeasureItemWidth(size_t WXUNUSED(item)) const override {
    return -1; // default - will be measured from text width
  }
};

class wxPixelComboBox : public wxOwnerDrawnComboBox {
public:
  virtual void OnDrawItem(wxDC &dc, const wxRect &rect, int item,
                          int flags) const override {
    if (item == wxNOT_FOUND)
      return;
    wxRect r(rect);
    r.Deflate(3);
    r.height -= 2;

    wxPenStyle penStyle = wxPENSTYLE_SOLID;
    wxPen pen(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT), 1,
              penStyle);
    if (item == 1) {
      pen.SetWidth(3);
    } else if (item == 2) {
      pen.SetWidth(5);
    } else if (item == 3) {
      pen.SetWidth(7);
    } else if (item == 4) {
      pen.SetWidth(10);
    }
    dc.SetPen(pen);

    if (!(flags & wxODCB_PAINTING_CONTROL)) {
      dc.DrawText(GetString(item), r.x + 3,
                  (r.y + 0) + ((r.height / 2) - dc.GetCharHeight()) / 2);
      /*dc.DrawLine(r.x + 5, r.y + ((r.height / 4) * 3), r.x + r.width - 5,
                  r.y + ((r.height / 4) * 3));*/
      /*dc.DrawLine(r.x + 5, r.y + (r.height / 2), r.x + r.width - 5,
                  r.y + (r.height / 2));*/
    } else {
      /*dc.DrawLine(r.x + 5, r.y + r.height / 2, r.x + r.width - 5,
                  r.y + r.height / 2);*/
      /*dc.DrawLine(r.x + 5, r.y + (r.height / 2), r.x + r.width - 5,
                  r.y + (r.height / 2));*/
      dc.DrawText(GetString(item) + wxT(" px"), r.x + 3,
                  (r.y + 0) + ((r.height / 2) - dc.GetCharHeight()) / 2);
    }
  }

  virtual void OnDrawBackground(wxDC &dc, const wxRect &rect, int item,
                                int flags) const override {

    // If item is selected or even, or we are painting the
    // combo control itself, use the default rendering.
    if ((flags & (wxODCB_PAINTING_CONTROL | wxODCB_PAINTING_SELECTED)) ||
        (item & 1) == 0) {
      wxOwnerDrawnComboBox::OnDrawBackground(dc, rect, item, flags);
      return;
    }

    // Otherwise, draw every other background with different colour.
    wxColour bgCol = wxSystemSettings::SelectLightDark(wxColour(240, 240, 250),
                                                       wxColour(48, 48, 64));

    dc.SetBrush(wxBrush(bgCol));
    dc.SetPen(wxPen(bgCol));
    dc.DrawRectangle(rect);
  }

  virtual wxCoord OnMeasureItem(size_t item) const override {
    // Simply demonstrate the ability to have variable-height items
    // return FromDIP(item & 1 ? 36 : 24);
    return FromDIP(20);
  }

  virtual wxCoord OnMeasureItemWidth(size_t WXUNUSED(item)) const override {
    return -1; // default - will be measured from text width
  }
};

class wxPenStyleComboBox : public wxOwnerDrawnComboBox {
public:
  virtual void OnDrawItem(wxDC &dc, const wxRect &rect, int item,
                          int flags) const override {
    if (item == wxNOT_FOUND)
      return;
    wxRect r(rect);
    r.Deflate(3);
    r.height -= 2;

    wxPenStyle penStyle = wxPENSTYLE_SOLID;
    wxPen pen(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT), 1,
              penStyle);
    if (item == 1) {
      pen.SetWidth(3);
    } else if (item == 2) {
      pen.SetWidth(5);
    } else if (item == 3) {
      pen.SetWidth(7);
    } else if (item == 4) {
      pen.SetWidth(10);
    }
    dc.SetPen(pen);

    if (!(flags & wxODCB_PAINTING_CONTROL)) {
      /*dc.DrawText(GetString(item), r.x + 3,
                  (r.y + 0) + ((r.height / 2) - dc.GetCharHeight()) / 2);*/
      /*dc.DrawLine(r.x + 5, r.y + ((r.height / 4) * 3), r.x + r.width - 5,
                  r.y + ((r.height / 4) * 3));*/
      dc.DrawLine(r.x + 5, r.y + (r.height / 2), r.x + r.width - 5,
                  r.y + (r.height / 2));
    } else {
      /*dc.DrawLine(r.x + 5, r.y + r.height / 2, r.x + r.width - 5,
                  r.y + r.height / 2);*/
      dc.DrawLine(r.x + 5, r.y + (r.height / 2), r.x + r.width - 5,
                  r.y + (r.height / 2));
    }
  }

  virtual void OnDrawBackground(wxDC &dc, const wxRect &rect, int item,
                                int flags) const override {

    // If item is selected or even, or we are painting the
    // combo control itself, use the default rendering.
    if ((flags & (wxODCB_PAINTING_CONTROL | wxODCB_PAINTING_SELECTED)) ||
        (item & 1) == 0) {
      wxOwnerDrawnComboBox::OnDrawBackground(dc, rect, item, flags);
      return;
    }

    // Otherwise, draw every other background with different colour.
    wxColour bgCol = wxSystemSettings::SelectLightDark(wxColour(240, 240, 250),
                                                       wxColour(48, 48, 64));

    dc.SetBrush(wxBrush(bgCol));
    dc.SetPen(wxPen(bgCol));
    dc.DrawRectangle(rect);
  }

  virtual wxCoord OnMeasureItem(size_t item) const override {
    // Simply demonstrate the ability to have variable-height items
    // return FromDIP(item & 1 ? 36 : 24);
    return FromDIP(20);
  }

  virtual wxCoord OnMeasureItemWidth(size_t WXUNUSED(item)) const override {
    return -1; // default - will be measured from text width
  }
};

FrameScreenShot::FontToolbar::FontToolbar(wxWindow *parent, wxWindowID id,
                                          const wxString &title,
                                          const wxPoint &pos,
                                          const wxSize &size, long style,
                                          const wxString &name)
    : IToolbar(parent, id, title, wxPoint(0, 0), wxSize(340, 40),
               /*(wxDEFAULT_FRAME_STYLE & ~wxCLOSE_BOX & ~wxCAPTION)*/
               wxNO_BORDER | wxFRAME_NO_TASKBAR /*| wxRESIZE_BORDER*/, name) {
  is_allow_move_.store(false);
  SetBackgroundColour(wxColour(252, 252, 252));

  m_arrItems_pixel.Add("1");
  m_arrItems_pixel.Add("3");
  m_arrItems_pixel.Add("5");
  m_arrItems_pixel.Add("7");
  m_arrItems_pixel.Add("10");
  // auto odc = new wxPenStyleComboBox();
  auto odc1 = new wxPixelComboBox();
  odc1->Create(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 30),
               m_arrItems_pixel,
               /*wxCB_READONLY*/ wxNO_BORDER | wxCB_READONLY);
  odc1->SetSelection(3);

  m_arrItems_font.Add("Arial");
  m_arrItems_font.Add("Sitka Subheading Semibold");
  m_arrItems_font.Add("Leelawadee UI");
  m_arrItems_font.Add("Marlett");
  m_arrItems_font.Add("Roman");
  m_arrItems_font.Add("Modern");
  // auto odc = new wxPenStyleComboBox();
  auto odc2 = new wxFontComboBox();
  odc2->Create(this, wxID_ANY, wxEmptyString, wxPoint(45, 0), wxSize(60, 30),
               m_arrItems_font,
               /*wxCB_READONLY*/ wxNO_BORDER | wxCB_READONLY);
  odc2->SetSelection(3);

  OnLayout();
  Bind(wxEVT_BUTTON, &FrameScreenShot::FontToolbar::OnToolEvent, this);
}
FrameScreenShot::FontToolbar::~FontToolbar() {
  Unbind(wxEVT_BUTTON, &FrameScreenShot::FontToolbar::OnToolEvent, this);
}
void FrameScreenShot::FontToolbar::OnLayout() {
}
void FrameScreenShot::FontToolbar::OnToolEvent(wxCommandEvent &event) {
}
void FrameScreenShot::FontToolbar::OnToolbarSizeChanged(const wxRect &rect) {
}