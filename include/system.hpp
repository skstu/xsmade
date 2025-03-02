#if !defined(__DBFEB73C_C2B1_42BD_A043_47FB3B92BE75__)
#define __DBFEB73C_C2B1_42BD_A043_47FB3B92BE75__

#include <xs.h>
#include <conv.hpp>

class System {
public:
  System() = default;
  ~System() = default;

public:
  static std::string GetCurrentProcessPath() {
    std::string result;
    do {
      char *_path = nullptr;
      size_t _path_len = 0;
      if (0 != xs_sys_process_getpath(&_path, &_path_len))
        break;
      result.append(_path, _path_len);
      result = stl::Path::PathnameToPath(result);
      xs_sys_free((void **)&_path);
    } while (0);
    return result;
  }
  static std::u16string GetCurrentProcessPathU16() {
    std::u16string result;
    std::string u8result;
    do {
      char *_path = nullptr;
      size_t _path_len = 0;
      if (0 != xs_sys_process_getpath(&_path, &_path_len))
        break;
      u8result.append(_path, _path_len);
      xs_sys_free((void **)&_path);
      u8result = stl::Path::PathnameToPath(u8result);
      result = Conv::u8_to_u16(u8result);
    } while (0);
    return result;
  }
};

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 22 Nov 2024 06:17:14 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__DBFEB73C_C2B1_42BD_A043_47FB3B92BE75__