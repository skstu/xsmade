#if !defined(__F1A22018_64A3_4A0E_AD6A_1B8A0183C9EC__)
#define __F1A22018_64A3_4A0E_AD6A_1B8A0183C9EC__
#include "xs.h"
#ifdef __cplusplus
extern "C" {
#endif
#include <uv.h>
#ifdef __cplusplus
}
#endif
namespace uvcc {
class System final {
public:
  System();
  ~System();

public:
  static xs_errno_t exepath(std::string &);
  static xs_errno_t os_gethostname(std::string &hostname);
  struct utsname_t {
    std::string sysname;
    std::string release;
    std::string version;
    std::string machine;
  };
  static xs_errno_t os_uname(utsname_t &uname);
};

} // namespace uvcc

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 04 Apr 2025 23:46:19 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__F1A22018_64A3_4A0E_AD6A_1B8A0183C9EC__