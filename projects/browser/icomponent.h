#if !defined(__71A8E348_DF0B_4209_8849_F31A5D37BC5F__)
#define __71A8E348_DF0B_4209_8849_F31A5D37BC5F__

#include <interface.hpp>
class IBrwComponent : public Interface<IBrwComponent> {
public:
  //!@ common
  virtual bool Start() = 0;
  virtual void Stop() = 0;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 19 Feb 2025 07:52:18 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__71A8E348_DF0B_4209_8849_F31A5D37BC5F__