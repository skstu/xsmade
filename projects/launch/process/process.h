#if !defined(__B26051AF_41E8_4609_B11F_FB4D41EADBC1__)
#define __B26051AF_41E8_4609_B11F_FB4D41EADBC1__

enum class ChildProcessType : unsigned long {
  None = 0x0000,
  Console = 0x1000,
  GUI = 0x2000,
  Service = 0x3000,
};
enum class ProcessType : unsigned long long {
  None = 0,
  Parent = 0x00000000,
  Child = 0x00001000,
};

class IProcess {
public:
  IProcess();
  ~IProcess();

public:
};

#include "parent.h"
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 02 Feb 2025 09:16:59 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__B26051AF_41E8_4609_B11F_FB4D41EADBC1__