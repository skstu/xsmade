#include <xs.h>
#include <stl.hpp>
#include <components/icucc/export.h>
int main(int argc, char **argv) {
  auto icucc = IIcucc::Create(R"(icucc.dll)");

  IIcucc::Destroy(&icucc);
  return 0;
}
