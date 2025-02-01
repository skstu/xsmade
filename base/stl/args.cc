#include "stl.hpp"
using namespace stl;
using namespace std;
Args::Args() {
}
Args::Args(const std::string &cmdline) {
  Parse(cmdline);
}
Args::Args(const int &argc, char **argv) {
  do {
    if (argc <= 0 || !argv || !(*argv))
      break;
    std::string cmdline;
    for (int i = 0; i < argc; ++i) {
      if (!argv[i])
        continue;
      cmdline.append(argv[i]).append(" ");
    }
    if (cmdline.empty())
      break;
    Parse(cmdline);
  } while (0);
}
Args::~Args() {
}
void Args::operator=(const std::string &cmdline) {
  Parse(cmdline);
}
bool Args::Empty() const {
  return source_.empty();
}
bool Args::Parse(const std::string &cmdline) {
  bool result = false;
  do {
    if (source_.empty())
      break;
  } while (0);
  return result;
}
std::u16string Args::PackageCommandLine(const int &argc, char **argv) {
  std::u16string result;
  do {
    if (argc <= 0 || !argv || !(*argv))
      break;
    std::string cmdline;
    for (int i = 0; i < argc; ++i) {
      if (!argv[i])
        continue;
      cmdline.append(argv[i]).append(" ");
    }
    if (cmdline.empty())
      break;
    Parse(cmdline);
  } while (0);
  return result;
}