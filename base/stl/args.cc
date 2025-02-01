#include "stl.hpp"
using namespace stl;
using namespace std;

Args::Args(const std::string &args) : cmdline_(args) {
}
Args::Args(const int &argc, char **argv) {
  do {
    if (argc <= 0 || !argv || !(*argv))
      break;
    for (int i = 0; i < argc; ++i) {
      if (!argv[i])
        continue;
      cmdline_.append(argv[i]).append(" ");
    }
  } while (0);
}
Args::~Args() {
}
const std::string &Args::GetSource() const {
  return cmdline_;
}
bool Args::Parse() {
  bool result = false;
  do {
    if (cmdline_.empty())
      break;
  } while (0);
  return result;
}