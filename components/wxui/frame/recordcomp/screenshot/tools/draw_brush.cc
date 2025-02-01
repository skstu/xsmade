#include <wxui.h>
namespace screenshot {
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
    } else {
      dc.DrawText(GetString(item) + wxT(" px"), r.x + 3,
                  (r.y + 0) + ((r.height / 2) - dc.GetCharHeight()) / 2 + 3);
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

class wxColorComboBox : public wxOwnerDrawnComboBox {
public:
  virtual void OnDrawItem(wxDC &dc, const wxRect &rect, int item,
                          int flags) const override {
    if (item == wxNOT_FOUND)
      return;
    wxRect r(rect);
    r.Deflate(3);
    r.height -= 2;

    wxPenStyle penStyle = wxPENSTYLE_SOLID;
    // wxPen pen(wxColour(255, 255, 0, 0), 1, penStyle);
    wxBrush brush(*wxRED);
    /*
    arrItems_color_.Add("red");
    arrItems_color_.Add("yellow");
    arrItems_color_.Add("blue");
    arrItems_color_.Add("green");
    arrItems_color_.Add("black");
    arrItems_color_.Add("white");
*/
    if (item == 1) {
      brush.SetColour(*wxYELLOW);
    } else if (item == 2) {
      brush.SetColour(*wxBLUE);
    } else if (item == 3) {
      brush.SetColour(*wxGREEN);
    } else if (item == 4) {
      brush.SetColour(*wxBLACK);
    } else if (item == 5) {
      brush.SetColour(*wxWHITE);
    }
    // dc.SetPen(pen);
    dc.SetBrush(brush);
    if (!(flags & wxODCB_PAINTING_CONTROL)) {
#if 1
      wxPoint topLeft(r.x, r.y);
      wxSize size(r.width, r.height);
      dc.DrawRectangle(topLeft, size);
#else
      wxPoint centre(r.x + r.width / 2, r.y + r.height / 2);
      int radius = 10;
      dc.DrawCircle(centre, radius);
#endif
    } else {
      wxPoint topLeft(r.x, r.y);
      wxSize size(r.width, r.height);
      dc.DrawRectangle(topLeft, size);
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

DrawBrushTool::DrawBrushTool(wxWindow *parent, wxWindowID id,
                             const wxBitmapBundle &bitmap, const wxPoint &pos,
                             const wxSize &size, long style,
                             const wxValidator &validator, const wxString &name)
    : IDrawTool(parent, id, bitmap, pos, size, style, validator, name) {
  SetToolTip(gpCommandToolTipMap[CommandTool(id)]);
}
DrawBrushTool::~DrawBrushTool() {
}
void DrawBrushTool::OnClicked(wxCommandEvent &evt) {
  evt.Skip();
  IToolbar *parent = dynamic_cast<IToolbar *>(GetParent()->GetParent());
  if (!parent)
    return;
  wxBoxSizer *sizer = nullptr;
  wxPanel *panel = nullptr;
  parent->GetExpandToolbar(&panel, &sizer);
  if (!sizer || !panel)
    return;
  sizer->Clear(true);
  pressed_.store(!pressed_.load());
  if (pressed_.load()) {
    do {
      wxArrayString arrItems_pixel_;
      arrItems_pixel_.Add("1");
      arrItems_pixel_.Add("3");
      arrItems_pixel_.Add("5");
      arrItems_pixel_.Add("7");
      arrItems_pixel_.Add("10");
      auto combo_pixel_ = new wxPixelComboBox();

      combo_pixel_->Create(panel, wxID_ANY, wxEmptyString, wxDefaultPosition,
                           wxSize(80, 30), arrItems_pixel_,
                           /*wxCB_READONLY*/ wxNO_BORDER | wxCB_READONLY);
      combo_pixel_->SetSelection(3);

      sizer->Add(combo_pixel_, 0, wxALL, 0);
    } while (0);

    do {
      wxArrayString arrItems_color_;
      arrItems_color_.Add("red");
      arrItems_color_.Add("yellow");
      arrItems_color_.Add("blue");
      arrItems_color_.Add("green");
      arrItems_color_.Add("black");
      arrItems_color_.Add("white");
      auto combo_color_ = new wxColorComboBox();
      combo_color_->Create(panel, wxID_ANY, wxEmptyString, wxDefaultPosition,
                           wxSize(50, 30), arrItems_color_,
                           /*wxCB_READONLY*/ wxNO_BORDER | wxCB_READONLY);
      combo_color_->SetSelection(0);

      sizer->Add(combo_color_, 0, wxALL, 0);
    } while (0);
  }

  parent->RefreshToolbar();

  wxCommandEvent notify(wxEVT_NotifyType,
                        NotifyEventID::EVT_NOTIFY_DRAWTOOL_ACTIVATE);
  notify.SetInt(pressed_.load() ? GetId() : CommandTool::TOOL_SCREENSHOT_NULL);
  Global::SendEvent(notify);
}
} // namespace screenshot