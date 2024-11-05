#include <iostream>
#include <icu.hpp>
int main(int argc, char **argv) {
  std::string name;
  Icu::Detect("asglkasdgh你好啊。@#￥……@……！",name);
  
  return 0;
}