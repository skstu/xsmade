#include "ui.h"

Global::Global() {
  Init();
}

Global::Global(Global &&global) noexcept
// : mapped_span_(std::exchange(mapping.mapped_span_, span<uint8_t>())),
//   size_(mapping.size_), guid_(mapping.guid_), mapper_(mapping.mapper_)
{
  font_monospace_ = global.font_monospace_;
}

Global &Global::operator=(Global &&global) noexcept {
  //   Unmap();
  //   mapped_span_ = std::exchange(mapping.mapped_span_, span<uint8_t>());
  //   size_ = mapping.size_;
  //   guid_ = mapping.guid_;
  //   mapper_ = mapping.mapper_;
  font_monospace_ = global.font_monospace_;
  return *this;
}

Global::~Global() {
  UnInit();
}
void Global::Init() {
  project_root_ = wxStandardPaths::Get().GetExecutablePath();
  wxFileName fileName(project_root_);
  project_root_ = fileName.GetPath(wxPATH_GET_VOLUME);
  project_res_dir_ = project_root_ + "/../../res";
  project_res_font_dir_ = project_res_dir_ + "/font";

//   font_monospace_ =
//       wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

//   if (font_monospace_->SetFaceName(project_res_font_dir_ + "/Monospace.ttf")) {
//     int ok = 0;
//   }
}
void Global::UnInit() {
}
////////////////////////////////////////////////////////
Global *__gpGlobal = nullptr;
//!@ static
Global *Global::Create() {
  if (!__gpGlobal)
    __gpGlobal = new Global();
  return __gpGlobal;
}
//!@ static
void Global::Destroy() {
  SK_DELETE_PTR(__gpGlobal);
}