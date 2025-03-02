#include "stl.hpp"
using namespace stl;
CmdLine::CmdLine(const std::string &cmdline) {
  source_ = ParserCommandLines(cmdline);
}
CmdLine::~CmdLine() {
}
void CmdLine::Release() const {
  delete this;
}
std::string CmdLine::GetValue(const std::string &key) const {
  std::string result;
  do {
    auto found = source_.find(Common::toLower(key));
    if (found == source_.end())
      break;
    result = found->second;
  } while (0);
  return result;
}
bool CmdLine::HasKey(const std::string &key) const {
  bool result = false;
  auto found = source_.find(Common::toLower(key));
  if (found != source_.end())
    result = true;
  return result;
}
std::string CmdLine::PackageCommandLine(const char **args) {
  std::string result;
  size_t total = 0;
  while (args[total]) {
    result.append(args[total]).append(" ");
    ++total;
  }
  return result;
}
std::string CmdLine::PackageCommandLine(const int &argc, char **argv) {
  std::string result;
  do {
    if (argc <= 0 || !argv || !(*argv))
      break;
    for (int i = 0; i < argc; ++i) {
      if (!argv[i])
        continue;
      result.append(argv[i]).append(" ");
    }
  } while (0);
  return result;
}
tfCommandLines CmdLine::ParserCommandLines(const std::string &input) {
  tfCommandLines result;
  do {
    if (input.empty())
      break;
    std::vector<std::string> parsers = Common::StringSpilt(input, " ");
    if (parsers.empty())
      break;
    for (size_t i = 0; i < parsers.size(); ++i) {
      if (parsers[i].empty())
        continue;
      std::string key, value;
      size_t equal = parsers[i].find('=');
      if (*parsers[i].begin() == '/') {
        key = parsers[i].substr(1, equal - 1);
      } else if (parsers[i].size() > 1 &&
                 (parsers[i][0] == '-' && parsers[i][1] == '-')) {
        key = parsers[i].substr(2, equal - 2);
      } else if (i == 0) {
        key = parsers[i];
      } else {
        continue;
      }
      if (key.empty())
        continue;
      if (equal != std::string::npos) {
        value = parsers[i].substr(equal + 1, parsers[i].size());
      }
      result.emplace(key, value);
    }
  } while (0);
  return result;
}