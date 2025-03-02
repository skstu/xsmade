#if !defined(__87266A07_9F95_460A_AC5C_E330AEE2A7FD__)
#define __87266A07_9F95_460A_AC5C_E330AEE2A7FD__

#include "component.h"

class IJsonnetcc : public IComponent {
public:
  virtual bool Start() {
    return false;
  }
  virtual void Stop() {
  }
  virtual bool Ready() const = 0;
  // virtual bool Detect(const IBuffer *, IBuffer **) const = 0;
  // virtual bool Convert(const IBuffer *input, const CharsetType &from,
  //                      const CharsetType &to, IBuffer **output) const = 0;
};
//
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 01 Feb 2025 13:28:28 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__87266A07_9F95_460A_AC5C_E330AEE2A7FD__
