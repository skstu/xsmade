#include <stl.hpp>

Stl::Stl() {
}

Stl::~Stl() {
}
std::string Stl::toLower(const std::string &input) {
  std::string result(input);
  if (!result.empty()) {
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  }
  return result;
}
std::string Stl::PackageCommandLine(const int &argc, char **argv) {
  std::string result;
  do {
    if (argc <= 0 || !argv || !(*argv))
      break;
    for (int i = 0; i < argc; ++i) {
      if (!argv[i])
        continue;
      result.append(argv[i]);
    }
  } while (0);
  return result;
}
std::vector<std::string> Stl::StringSpilt(const std::string &input,
                                          const std::string &delim) {
  std::vector<std::string> result;
  do {
    if (input.empty()) {
      break;
    }
    if (delim.empty()) {
      result.emplace_back(input);
      break;
    }
    std::string escaped_delim =
        regex_replace(delim, std::regex(R"([\.\+\*\?\[\^\$\(\|])"), R"(\$&)");
    std::regex re(escaped_delim);
    result = std::vector<std::string>{
        std::sregex_token_iterator(input.begin(), input.end(), re, -1),
        std::sregex_token_iterator()};
  } while (0);
  return result;
}
tfCommandLines Stl::ParserCommandLines(const std::string &input) {
  tfCommandLines result;
  do {
    if (input.empty())
      break;
    std::vector<std::string> parsers = Stl::StringSpilt(input, " ");
    if (parsers.empty())
      break;
    for (const auto &str : parsers) {
      if (str.empty())
        continue;
      std::string key, value;
      size_t equal = str.find('=');
      if (*str.begin() == '/') {
        key = str.substr(1, equal - 1);
      } else if (str.size() > 1 && (str[0] == '-' && str[1] == '-')) {
        key = str.substr(2, equal - 2);
      } else {
        key = str;
      }
      if (key.empty())
        continue;
      if (equal != std::string::npos) {
        value = str.substr(equal + 1, str.size());
      }
      result.emplace(Stl::toLower(key), value);
    }
  } while (0);
  return result;
}