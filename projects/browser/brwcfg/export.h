#if !defined(__5F0E26E1_8D0C_418A_86B1_831DD24458AF__)
#define __5F0E26E1_8D0C_418A_86B1_831DD24458AF__
#include "interface.hpp"
namespace browser {
class IConfig {
public:
};

class IBrwcfg {
public:
  virtual IConfig* ConfigGet() const = 0;
  virtual void OnMainProcessStartup(void) = 0;
  virtual void OnMainProcessShutdown(int rv) = 0;
};
} // namespace browser

/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 07 Dec 2024 06:49:11 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__5F0E26E1_8D0C_418A_86B1_831DD24458AF__