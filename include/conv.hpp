#if !defined(__7A39994E_D449_441B_BDCA_5E5C824BD001__)
#define __7A39994E_D449_441B_BDCA_5E5C824BD001__

#include <stl.hpp>
#include <utf8.h>

class Conv {
public:
  Conv() = default;
  ~Conv() = default;

public:
  static std::u16string ws_to_u16(const std::wstring &input) {
    std::u16string result;
    if (!input.empty()) {
      result = std::u16string(input.begin(), input.end());
    }
    return result;
  }
  static std::wstring u16_to_ws(const std::u16string &input) {
    std::wstring result;
    if (!input.empty()) {
      result = std::wstring(input.begin(), input.end());
    }
    return result;
  }
  static std::u16string u8_to_u16(const std::string &input) {
    std::u16string result;
    do {
      if (input.empty())
        break;
      auto end_it = utf8::find_invalid(input.begin(), input.end());
      std::vector<unsigned short> utf16line;
      utf8::utf8to16(input.begin(), end_it, std::back_inserter(utf16line));
      result.append((char16_t *)&utf16line[0], utf16line.size());
    } while (0);
    return result;
  }
  static std::string u16_to_u8(const std::u16string &input) {
    std::string result;
    do {
      if (input.empty())
        break;
      utf8::utf16to8(input.begin(), input.end(), std::back_inserter(result));
    } while (0);
    return result;
  }
  static std::string ws_to_u8(const std::wstring &input) {
    std::string result;
    if (!input.empty()) {
      std::u16string u16str = ws_to_u16(input);
      result = u16_to_u8(u16str);
    }
    return result;
  }
  static std::wstring u8_to_ws(const std::string &input) {
    std::wstring result;
    if (!input.empty()) {
      std::u16string u16str = u8_to_u16(input);
      result = u16_to_ws(u16str);
    }
    return result;
  }
#if _STL_HAS_CXX20
  static std::u8string str_to_u8(const std::string &input) {
    std::u8string result;
    if (!input.empty()) {
      result = std::u8string(input.begin(), input.end());
    }
    return result;
  }
  static std::string u8_to_str(const std::u8string &input) {
    std::string result;
    if (!input.empty()) {
      result = std::string(input.begin(), input.end());
    }
    return result;
  }
#endif
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 17 Nov 2024 01:37:32 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__7A39994E_D449_441B_BDCA_5E5C824BD001__