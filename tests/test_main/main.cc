#include <iostream>
#include <icu.hpp>
int main(int argc, char **argv) {
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
  return 0;
}