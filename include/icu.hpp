#if !defined(__C34E226C_724B_471A_A481_D9C371FD8EB9__)
#define __C34E226C_724B_471A_A481_D9C371FD8EB9__

#include <unicode/uclean.h>
#include <unicode/ustdio.h>
#include <unicode/platform.h>
#include <unicode/putil.h>
#include <unicode/ucnv.h>
#include <unicode/uconfig.h>
#include <unicode/ucsdet.h>
#include <unicode/udata.h>
#include <unicode/unistr.h>
#include <unicode/ustring.h>
#include <unicode/utf16.h>
#include <unicode/utf32.h>
#include <unicode/utf8.h>
#include <unicode/utypes.h>

#include "stl.hpp"

class Icu {
public:
Icu() = default;
~Icu() = default;
public:
static bool Detect(const std::string& src,std::string& name) {
  bool result = false;
  name.clear();
  UErrorCode status;
  UCharsetDetector *ucs = nullptr;
  do {
    if(src.empty())
    break;
    status = U_ZERO_ERROR;
    ucs = ucsdet_open(&status);
    if (U_ZERO_ERROR != status || !ucs)
      break;
    status = U_ZERO_ERROR;
    ucsdet_setText(ucs, src.data(), src.size(), &status);
    if (U_ZERO_ERROR != status)
      break;
    status = U_ZERO_ERROR;
    const UCharsetMatch *ucsm = ucsdet_detect(ucs, &status);
    if (U_ZERO_ERROR != status || !ucsm)
      break;
    status = U_ZERO_ERROR;
    const char *name_ = ucsdet_getName(ucsm, &status);
    if (U_ZERO_ERROR != status || !name_)
      break;
    name = name_;
    result = true;
  } while (0);
  if (ucs) {
    ucsdet_close(ucs);
    ucs = NULL;
  }
  return result;
}
static bool Convert(const std::string& to_name,const std::string& from_name,const std::string& src,std::string& dst){
bool result = false;
  UErrorCode status = U_ZERO_ERROR;
  do {
    if(src.empty())
    break;
    if(to_name.compare(from_name)==0){
      result = true;
      break;
    }
    size_t tmp_len = ucnv_convert(to_name.c_str(), from_name.c_str(), NULL, 0, src.data(),
                           src.size(), &status);
    if (U_BUFFER_OVERFLOW_ERROR != status && tmp_len != 0)
      break;
    status = U_ZERO_ERROR;
    dst.resize(tmp_len,0x00);
    ucnv_convert(to_name.c_str(), from_name.c_str(), (char*)&dst[0], dst.size(), src.data(),
                 src.size(), &status);
    if (status != U_ZERO_ERROR)
      break;
    result = true;
  } while (0);
  return result;
}
#if 0
bool Convert(const char *to_name, const char *src, const size_t &srcLen,
                  char **dst, size_t *dstLen) const {
  bool result = false;
  UErrorCode status = U_ZERO_ERROR;
  *dst = NULL;
  *dstLen = 0;
  char *from_name = NULL;
  size_t from_nameLen = 0;
  do {
    if (!src || srcLen <= 0 || !to_name)
      break;
    if (!DetectName(src, srcLen, &from_name, &from_nameLen))
      break;
    if (strcmp(to_name, from_name) == 0) {
      *dst = (char *)malloc(srcLen);
      *dstLen = srcLen;
      memcpy(*dst, src, *dstLen);
      status = U_ZERO_ERROR;
      result = true;
      break;
    }
    status = U_ZERO_ERROR;
    *dstLen = ucnv_convert(to_name, from_name, NULL, 0, (const char *)src,
                           srcLen, &status);
    if (U_BUFFER_OVERFLOW_ERROR != status && *dstLen != 0)
      break;
    status = U_ZERO_ERROR;
    *dstLen += sizeof(char);
    *dst = (char *)malloc(*dstLen);
    ucnv_convert(to_name, from_name, (char *)(*dst), *dstLen, (const char *)src,
                 srcLen, &status);
    if (status != U_ZERO_ERROR)
      break;
    *dstLen -= sizeof(char);
    result = true;
  } while (0);
  SK_FREE_PTR(from_name);
  return result;
}
#endif
};

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 05 Nov 2024 12:29:10 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__C34E226C_724B_471A_A481_D9C371FD8EB9__