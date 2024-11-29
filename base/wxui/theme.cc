#include "wxui.h"

Theme::Theme() {
}
Theme::~Theme() {
  SK_DELETE_PTR(wximage_bkg_);
  SK_DELETE_PTR(wximage_shape_);
}
void Theme::SetShapeImage(const char *path) {
  image_shape_ = path ? path : "";
  if (stl::File::Exists(image_shape_)) {
    std::string buffer = stl::File::ReadFile(image_shape_);
    if (buffer.empty())
      return;
    SK_DELETE_PTR(wximage_shape_);
    wxComm::LoadImg(path, &wximage_shape_);
  }
}
void Theme::SetBackgroundImage(const char *path) {
  image_background_ = path ? path : "";
  if (stl::File::Exists(image_shape_)) {
    std::string buffer = stl::File::ReadFile(image_shape_);
    if (buffer.empty())
      return;
    SK_DELETE_PTR(wximage_bkg_);
    wxComm::LoadImg(path, &wximage_bkg_);
  }
}
tfThemeIdentify Theme::Identify() const {
  return identify_;
}
const wxImage &Theme::GetShapeImage() const {
  return *wximage_shape_;
}
const wxImage &Theme::GetBackgroundImage() const {
  return *wximage_bkg_;
}