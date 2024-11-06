#include <iostream>
#include <fmt/format.h>
#include <stl.hpp>
#include <utf8.h>
#include <httplib.h>
#include <rapidjson.h>
int main(int argc, char **argv) {
  do { //!@ test cpp-httplib
    httplib::Client cli("https://github.com");
    auto res = cli.Get("/");
    if (!res)
      break;
    std::string body = res->body;
    std::cout << body << std::endl;
    auto sss = 0;
  } while (0);

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

  do { //!@ rapidjson
    rapidjson::Document doc;
    doc.Parse(R"({"hi":"martell!"})");
    if (doc.HasParseError())
      break;

    std::string out = Json::toString(doc);
    std::cout << out << std::endl;
  } while (0);

  do { //!@ fmt
    std::string test = fmt::format("{:.2f}", 1.8845);

    std::cout << test << std::endl;

  } while (0);
  return 0;
}