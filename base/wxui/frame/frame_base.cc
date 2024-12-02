#include "wxui.h"

FrameBase::FrameBase(wxWindow *parent, wxWindowID id, const wxString &title,
                     const wxPoint &pos, const wxSize &size, long style,
                     const wxString &name)
    : wxFrame(parent, id, title, pos, size, style, name) {
}
FrameBase::~FrameBase() {
}
const FrameType &FrameBase::Type() const {
  return Config::Get()->GetFrameType();
}
void FrameBase::SetRegion(long x, long y, long cx, long cy) {
}
bool FrameBase::IsFullScreenShown() const {
  return is_fullscreen_shown_.load();
}
bool FrameBase::IsDragging() const {
  return is_dragging_.load();
}