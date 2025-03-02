#include "ui/ui.h"
using namespace ui;
FrameActivate::FrameActivate(wxWindow *parent, wxWindowID id,
                             const wxString &title, const wxPoint &pos,
                             const wxSize &size, long style,
                             const wxString &name)
    : IFrame(parent, id, title, pos, size,
             wxFRAME_SHAPED | wxNO_BORDER | wxFRAME_NO_TASKBAR, name) {
  // SetBackgroundColour(wxColour(183, 110, 121));
  SetBackgroundColour(wxColour(250, 250, 250));
  SetTransparent(200);
  // SetBackgroundStyle(wxBG_STYLE_CUSTOM);
  // wxString privfont;
  // privfont
  //     << R"(C:\Users\k34ub\source\skstu\xsmade\res\fonts\Monospace\Monospace.ttf)";
  // if (!wxFont::AddPrivateFont(privfont)) {
  // } else {
  //   auto success = true;
  // }
}
FrameActivate::~FrameActivate() {
}
void FrameActivate::OnEraseBackground(wxEraseEvent &evt) {
  evt.Skip();
}
void FrameActivate::OnPaint(wxPaintEvent &evt) {
  wxPaintDC dc(this);

  // 加载自定义字体（假设字体文件路径是 "C:\\path\\to\\font.ttf"）
  wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
  if (font.SetFaceName("Monospace")) {
    // 设置成功
    dc.SetFont(font.Bold());
  } else {
    // 设置失败，尝试加载自定义字体文件
    if (wxFont::GetDefaultEncoding() == wxFONTENCODING_DEFAULT) {
      wxFont customFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
      if (!customFont.SetFaceName(R"(C:\Users\k34ub\source\skstu\xsmade\res\fonts\Monospace\Monospace.ttf)")) {
        wxLogError("Failed to load custom font.");
      } else {
        dc.SetFont(customFont);
      }
    }
  }

  dc.SetTextForeground(*wxBLACK); // 设置文本颜色

  dc.DrawText(wxT("Memade"), 20, 0);  // 绘制文本

  evt.Skip();
}