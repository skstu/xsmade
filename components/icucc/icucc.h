#if !defined(__A7AE0FB6_90A8_4123_82E4_70BE2492B465__)
#define __A7AE0FB6_90A8_4123_82E4_70BE2492B465__

#include <xs.h>
#include "export.h"

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

class Icucc final : public IIcucc {
public:
  static Icucc *Create();
  static void Destroy();

private:
  Icucc();
  virtual ~Icucc();

public:
  bool Ready() const override final;

private:
  void Init();
  void UnInit();

private:
  std::atomic_bool ready_ = false;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 02:23:49 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__A7AE0FB6_90A8_4123_82E4_70BE2492B465__
