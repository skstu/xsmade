#include "stl.hpp"
using namespace stl;
MainProc::MainProc(const MainProcCb &callback) : callback_(callback) {
  if (callback_) {
    Proc();
  } else {
    std::cerr << "Callback function is not valid!" << std::endl;
  }
}
void MainProc::Proc() {
  std::string input;
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input.empty()) {
      continue;
    }
    bool exit_flag = false;
    callback_(input, exit_flag);
    if (exit_flag || std::cin.eof()) {
      break;
    }
  } while (true);
}
bool Common::strIcmp(const std::string &str1, const std::string &str2) {
  return toLower(str1).compare(toLower(str2)) == 0;
}
std::string Common::toLower(const std::string &input) {
  std::string result(input);
  if (!result.empty()) {
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  }
  return result;
}
std::vector<std::string> Common::StringSplit(const std::string &input,
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
