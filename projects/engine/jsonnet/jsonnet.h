#if !defined(__0966764A_D935_400B_9922_1D015FA8A4BF__)
#define __0966764A_D935_400B_9922_1D015FA8A4BF__

#include "libjsonnet.h"
#include "libjsonnet++.h"
#include "libjsonnet_fmt.h"
#include "export.h"
using namespace engine;

class Jsonnet : public IJsonnet {
public:
  static Jsonnet *Get();
  static void Destroy();

private:
  Jsonnet();
  virtual ~Jsonnet();
  static Jsonnet *jsonnet_; 
  static std::mutex mtx_;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 26 Jan 2025 10:23:05 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__0966764A_D935_400B_9922_1D015FA8A4BF__