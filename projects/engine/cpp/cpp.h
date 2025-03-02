#if !defined(__57D466C6_BF89_401B_BFDE_5BC787489FD9__)
#define __57D466C6_BF89_401B_BFDE_5BC787489FD9__

#include "export.h"
using namespace engine;

class Cpp : public ICpp {
public:
  static Cpp *Get();
  static void Destroy();

private:
  Cpp();
  virtual ~Cpp();
  static Cpp *cpp_;
  static std::mutex mtx_;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 16 Feb 2025 11:20:07 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__57D466C6_BF89_401B_BFDE_5BC787489FD9__
