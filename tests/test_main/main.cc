#include <iostream>
// #include <icu.hpp>
#include <stl.hpp>
#include <utf8.h>
int main(int argc, char **argv) {
  do { //!@ test utfcpp
    std::string u8text = u8R"("asglkasdgh你好啊。@#￥……@……！";)";
    std::string::iterator end_it =
        utf8::find_invalid(u8text.begin(), u8text.end());
    std::vector<unsigned short> utf16line;
    utf8::utf8to16(u8text.begin(), end_it, std::back_inserter(utf16line));
    std::u16string u16text;
    u16text.append((char16_t *)&utf16line[0], utf16line.size());

    std::string utf8line;
    utf8::utf16to8(u16text.begin(), u16text.end(),
                   std::back_inserter(utf8line));
    auto kk = u16text.c_str();
    std::cout << "u8:" << utf8line << std::endl;
    // std::cout << "u16:" << u16text << std::endl;
    auto __pause__ = 1;
  } while (0);

#if 0
  std::string name;
  const std::string src = "asglkasdgh你好啊。@#￥……@……！";
  Icu::Detect(src, name);
  std::string dst;
  Icu::Convert("UTF-16", "UTF-8", src, dst);
  char16_t *tmp = (char16_t *)malloc(dst.size());
  std::u16string u16tmp;
  u16tmp.resize(dst.size() + sizeof(char16_t), 0x00);
  memcpy((char *)&u16tmp[0], dst.data(), dst.size());
  std::cout << name << std::endl;
  std::cout << dst << std::endl;
#endif
  return 0;
}