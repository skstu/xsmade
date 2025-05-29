#if !defined(__03406DC9_3BF3_47A3_927C_502ACED2AF60__)
#define __03406DC9_3BF3_47A3_927C_502ACED2AF60__

#include "component.h"

namespace curl {
class ICurl : public IComponent {
public:
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual bool Perform() {
    return false;
  }
  virtual bool Ready() const = 0;
};
} // namespace curl
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 06:16:26 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__03406DC9_3BF3_47A3_927C_502ACED2AF60__