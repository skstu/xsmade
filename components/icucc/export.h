#if !defined(__87266A07_9F95_460A_AC5C_E330AEE2A7FD__)
#define __87266A07_9F95_460A_AC5C_E330AEE2A7FD__

#include "component.h"

class IIcucc : public IComponent {
public:
  enum class CharsetType : unsigned long long {
    UNKNOWN = 0,
    UTF8,
    UTF16,
    UTF16LE,
    UTF16BE,
    UTF32,
    UTF32LE,
    UTF32BE,
    ASCII,
    GBK,
    GB18030,
  };

public:
  virtual bool Start() {
    return false;
  }
  virtual void Stop() {
  }
  virtual bool Ready() const = 0;
  virtual bool GetZoneOffsetMinutes(const char *tzid, int &out_minutes,
                                    long long tp_ms) const = 0;
};
//
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 01 Feb 2025 13:28:28 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__87266A07_9F95_460A_AC5C_E330AEE2A7FD__
