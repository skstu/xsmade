#include "brwcfg.h"

bool wxComm::GetImgStream(const wxImage *img, std::string &imgStream) {
  bool result = false;
  do {
    if (!img)
      break;
    if (!img->IsOk())
      break;
    wxMemoryOutputStream mstream;
    if (!img->SaveFile(mstream, wxBitmapType::wxBITMAP_TYPE_PNG))
      break;
    size_t length = mstream.GetLength();
    if (length == 0)
      break;
    imgStream.resize(length);
    mstream.CopyTo(imgStream.data(), length);
    result = true;
  } while (0);

  return result;
}

bool wxComm::LoadImgFormStream(const std::string &imageStream,
                               wxImage **outputImg) {
  bool result = false;
  *outputImg = nullptr;
  do {
    if (imageStream.empty())
      break;
    wxMemoryInputStream *mstream =
        new wxMemoryInputStream(imageStream.data(), imageStream.size());
    xs_image_type_t imgType;
    xs_sys_get_image_type(imageStream.data(), imageStream.size(), &imgType);
    switch (imgType) {
    case xs_image_type_t::_PNG: {
      *outputImg = new wxImage(*mstream, wxBitmapType::wxBITMAP_TYPE_PNG);
      if (!(*outputImg)->IsOk()) {
        SK_DELETE_PTR(*outputImg);
        break;
      }
      result = true;
    } break;
    case xs_image_type_t::_JPEG: {
      *outputImg = new wxImage(*mstream, wxBitmapType::wxBITMAP_TYPE_JPEG);
      if (!(*outputImg)->IsOk()) {
        SK_DELETE_PTR(*outputImg);
        break;
      }
      result = true;
    } break;
    case xs_image_type_t::_BMP: {
      *outputImg = new wxImage(*mstream, wxBitmapType::wxBITMAP_TYPE_BMP);
      if (!(*outputImg)->IsOk()) {
        SK_DELETE_PTR(*outputImg);
        break;
      }
      result = true;
    } break;
    case xs_image_type_t::_ICO: {
      *outputImg = new wxImage(*mstream, wxBitmapType::wxBITMAP_TYPE_ICO);
      if (!(*outputImg)->IsOk()) {
        SK_DELETE_PTR(*outputImg);
        break;
      }
      result = true;
    } break;
    case xs_image_type_t::_GIF: {
      *outputImg = new wxImage(*mstream, wxBitmapType::wxBITMAP_TYPE_GIF);
      if (!(*outputImg)->IsOk()) {
        SK_DELETE_PTR(*outputImg);
        break;
      }
      result = true;
    } break;
    default:
      break;
    }
  } while (0);
  return result;
}
bool wxComm::LoadImg(const std::u16string &imgPath, wxImage **outputImg) {
  bool result = false;
  *outputImg = nullptr;
  do {
    if (!stl::File::Exists(imgPath))
      break;
    std::string buffer = stl::File::ReadFile(imgPath);
    if (buffer.empty())
      break;
    if (!wxComm::LoadImgFormStream(buffer, outputImg))
      break;
    result = true;
  } while (0);
  return result;
}

#if 0
wxComm::TransparentBitmapButton::TransparentBitmapButton(
    wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
    const wxPoint &pos, const wxSize &size, long style,
    const wxValidator &validator, const wxString &name)
    : wxBitmapButton(parent, id, bitmap, pos, size, style, validator, name) {
  Bind(wxEVT_PAINT, &wxComm::TransparentBitmapButton::OnPaint, this);
}
wxComm::TransparentBitmapButton::~TransparentBitmapButton() {
  Unbind(wxEVT_PAINT, &wxComm::TransparentBitmapButton::OnPaint, this);
}
void wxComm::TransparentBitmapButton::OnPaint(wxPaintEvent &event) {
  wxAutoBufferedPaintDC dc(this);
  dc.SetBackground(*wxTRANSPARENT_BRUSH); // 设置背景为透明
  dc.Clear();

  // 绘制图片
  wxBitmapBundle bundle = GetBitmapBundle();
  wxBitmap bitmap = bundle.GetBitmap(0); // 获取第一张图片
  dc.DrawBitmap(bitmap, 0, 0);
}
#endif
