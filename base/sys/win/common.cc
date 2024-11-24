#include "sys.h"
static ULONG_PTR gdiplustoken_ = 0;
static Gdiplus::GdiplusStartupInput gdiplusStartupInput_ = {0};
XS_EXTERN void xs_sys_startup(void) {
  SetProcessDPIAware();
  Gdiplus::GdiplusStartup(&gdiplustoken_, &gdiplusStartupInput_, NULL);
}
XS_EXTERN void xs_sys_shutdown(void) {
  Gdiplus::GdiplusShutdown(gdiplustoken_);
}
XS_EXTERN int xs_sys_get_appdata_path(char **path, size_t *path_len) {
  int r = -1;
  std::string result;
  LPITEMIDLIST ppidl = nullptr;
  do {
    if (SHGetSpecialFolderLocation(nullptr, CSIDL_APPDATA, &ppidl) != S_OK)
      break;
    char pszPath[_MAX_PATH] = {0};
    if (!SHGetPathFromIDListA(ppidl, pszPath))
      break;
    result = pszPath;
    if (result.empty())
      break;
    auto end = std::prev(result.end());
    if (*end != '\\' && *end != '/')
      result.append("\\");
    *path = (char *)malloc(result.size());
    *path_len = result.size();
    memcpy(*path, result.data(), result.size());
    r = 0;
  } while (0);
  if (ppidl) {
    CoTaskMemFree(ppidl);
    ppidl = nullptr;
  }
  return r;
}

int GetEncoderClsid(const WCHAR *format, CLSID *pClsid) {
  UINT num = 0;  //   number   of   image   encoders
  UINT size = 0; //   size   of   the   image   encoder   array   in   bytes

  Gdiplus::ImageCodecInfo *pImageCodecInfo = NULL;

  Gdiplus::GetImageEncodersSize(&num, &size);
  if (size == 0)
    return -1; //   Failure

  pImageCodecInfo = (Gdiplus::ImageCodecInfo *)(malloc(size));
  if (pImageCodecInfo == NULL)
    return -1; //   Failure

  GetImageEncoders(num, size, pImageCodecInfo);

  for (UINT j = 0; j < num; ++j) {
    if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
      *pClsid = pImageCodecInfo[j].Clsid;
      free(pImageCodecInfo);
      return j; //   Success
    }
  }

  free(pImageCodecInfo);
  return -1; //   Failure
}

XS_EXTERN int xs_sys_capturescreen(xs_position_t pos,
                                   xs_image_stream_type_t type,
                                   xs_image_stream_t **stream) {
  int r = -1;
  std::string imageStream;
  do {
    HWND hwnd_ = GetDesktopWindow();
    IStream *pStream = nullptr;
    HBITMAP hBitmap = nullptr;
    HDC hScreenDC = nullptr;
    HDC hMemoryDC = nullptr;

    RECT rtWindow;
    GetWindowRect(hwnd_, &rtWindow);
    const long left = rtWindow.left;
    const long top = rtWindow.top;
    const long right = rtWindow.right;
    const long bottom = rtWindow.bottom;
    const long width = rtWindow.right - rtWindow.left;
    const long height = rtWindow.bottom - rtWindow.top;
    do {
      if (right && bottom) { //!@ unused variable ...
      }
      if (width <= 0 && height <= 0) {
        break;
      }
      hScreenDC = GetDC(NULL);
      hMemoryDC = CreateCompatibleDC(hScreenDC);
      if (!hScreenDC || !hMemoryDC) {
        break;
      }
      hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
      HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
      if (!hBitmap || !hOldBitmap) {
        break;
      }
      if (FALSE == BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, left, top,
                          SRCCOPY)) {
        break;
      }
      Gdiplus::Bitmap bitmap(hBitmap, NULL);
      if (FAILED(CreateStreamOnHGlobal(NULL, TRUE, &pStream)) || !pStream) {
        break;
      }
      CLSID clsid;
#if 0
image/bmp  : {557cf400-1a04-11d3-9a73-0000f81ef32e}
image/jpeg : {557cf401-1a04-11d3-9a73-0000f81ef32e} 
image/gif  : {557cf402-1a04-11d3-9a73-0000f81ef32e} 
image/tiff : {557cf405-1a04-11d3-9a73-0000f81ef32e}
image/png  : {557cf406-1a04-11d3-9a73-0000f81ef32e}

      GUID guidPng = {};
      GetEncoderClsid(L"image/png", &guidPng);

GUID guidBmp = {};
    GUID guidJpeg = {};
    GUID guidGif = {};
    GUID guidTiff = {};
    GUID guidPng = {};

    GetGdiplusEncoderClsid(L"image/bmp", &guidBmp);
    GetGdiplusEncoderClsid(L"image/jpeg", &guidJpeg);
    GetGdiplusEncoderClsid(L"image/gif", &guidGif);
    GetGdiplusEncoderClsid(L"image/tiff", &guidTiff);
    GetGdiplusEncoderClsid(L"image/png", &guidPng);
#endif

      if (FAILED(CLSIDFromString(L"{557cf406-1a04-11d3-9a73-0000f81ef32e}",
                                 &clsid))) {
        break;
      }
      if (Gdiplus::Status::Ok != bitmap.Save(pStream, &clsid, NULL)) {
        break;
      }
      STATSTG statstg = {0};
      if (FAILED(pStream->Stat(&statstg, STATFLAG_NONAME))) {
        break;
      }
      ULONG streamSize = statstg.cbSize.LowPart;
      imageStream.resize(streamSize);
      //*len = streamSize;
      //*buffer = (char *)malloc(*len);
      LARGE_INTEGER liZero = {};
      pStream->Seek(liZero, STREAM_SEEK_SET, NULL);
      ULONG bytesRead = 0;
      pStream->Read(&imageStream[0], streamSize, &bytesRead);
      imageStream.resize(bytesRead);
      SelectObject(hMemoryDC, hOldBitmap);
      if (imageStream.empty()) {
        break;
      }
      *stream = (xs_image_stream_t *)malloc(sizeof(xs_image_stream_t));
      (*stream)->len = imageStream.size();
      (*stream)->buffer = (char *)malloc(imageStream.size());
      memcpy((*stream)->buffer, imageStream.data(), imageStream.size());
      r = 0;
    } while (0);

    if (hBitmap) {
      DeleteObject(hBitmap);
    }
    if (hMemoryDC) {
      DeleteDC(hMemoryDC);
    }
    if (hScreenDC) {
      ReleaseDC(NULL, hScreenDC);
    }

  } while (0);
  return r;
}