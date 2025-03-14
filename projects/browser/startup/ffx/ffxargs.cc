#include "startup.h"
namespace ffx {
FFXArgs::FFXArgs(const tfFFXArgs &args) : args_(args) {
}

FFXArgs::~FFXArgs() {
}
void FFXArgs::Push(const std::string &key, const std::string &value) {
  do {
    std::string inster_value(value);
    bool found = false;
    for (auto &arg : args_) {
      if (arg.second.first.compare(key) == 0) {
        arg.second.second = inster_value;
        found = true;
        break;
      }
    }
    if (found)
      break;
    args_.emplace(args_.size(), tfArgs{key, inster_value});
  } while (0);
}
std::vector<std::string> FFXArgs::GetArgs() const {
  std::vector<std::string> result;
  for (const auto &arg : args_) {
    std::string node;
    if (arg.second.first.find("-xs-") == std::string::npos &&
        !arg.second.first.empty()) {
      node.append(arg.second.first).append(1, 0x20);
    }
    if (!arg.second.second.empty())
      node.append(arg.second.second).append(1, 0x20);
    result.emplace_back(node);
  }
  return result;
}
} // namespace ffx
