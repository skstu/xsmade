#if !defined(__E234AB9E_227D_4700_AF59_61096C0013E6__)
#define __E234AB9E_227D_4700_AF59_61096C0013E6__

#include "interface.hpp"

class IFFXCtrl : public Interface<IFFXCtrl> {
public:
  virtual bool Start() = 0;
  virtual void Stop() = 0;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 27 Nov 2024 05:39:29 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__E234AB9E_227D_4700_AF59_61096C0013E6__