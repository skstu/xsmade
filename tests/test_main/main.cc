#include "system.h"
#include "conv.hpp"

int main(int argc, char **argv) {
  std::u16string current_path_u16;
  do {
    const char *ddd = xs_err_name(xs_errno_t::XS_OK);
    char *curpath = nullptr;
    size_t curpath_len = 0;
    xs_sys_process_getpath(&curpath, &curpath_len);
    std::string strPath(stl::Path::Parent(std::string(curpath, curpath_len)));
    xs_sys_free((void **)&curpath);
    current_path_u16 = Conv::u8_to_u16(strPath);
  } while (0);

  do {
    char *cmdline = nullptr;
    size_t cmdline_len = 0;
    xs_sys_get_commandline(&cmdline, &cmdline_len);
    std::string strCmdline(cmdline, cmdline_len);
    xs_sys_free((void **)&cmdline);
    std::cout << strCmdline << std::endl;
    auto ss = 0;
  } while (0);

  do {
    char *path = nullptr;
    size_t path_len = 0;
    if (xs_errno_t::XS_OK != xs_sys_get_home_path(&path, &path_len))
      break;
    std::string strPath(path, path_len);
    std::cout << strPath << std::endl;
    xs_sys_free((void **)&path);
    auto ss = 0;
  } while (0);

  do {
    char *path = nullptr;
    size_t path_len = 0;
    if (xs_errno_t::XS_OK != xs_sys_get_cache_path(&path, &path_len))
      break;
    std::string strPath(path, path_len);
    std::cout << strPath << std::endl;
    xs_sys_free((void **)&path);
    auto ss = 0;
  } while (0);

  stl::MainProc([](const std::string &input, bool &exit_flag) {
    if (input == "q") {
      exit_flag = true;
    } else {
      std::cout << "You entered: " << input << std::endl;
    }
  });

  return 0;
}

#if 0
#include <iostream>
#include <wxwidgets.hpp>
#include <windows.h>
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow){
  return 0;
}
#include <fmt/format.h>
#include <stl.hpp>
#include <utf8.h>
#include <httplib.h>
#include <rapidjson.h>
#include <system.hpp>
#include <uv.h>
#define TEST_WXWIDGETS 1

#if TEST_WXWIDGETS
#include <wxwidgets.hpp>
int main(int argc, char **argv) {
  return 0;
}
// int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int
// cmdshow)
// {
//     return MessageBox(NULL, "hello, world", "caption", 0);
// }
#else
void timer_callback(uv_timer_t *handle) {
  std::cout << "Hello from libuv! The timer callback was triggered."
            << std::endl;
}

int main(int argc, char **argv) {
  do { //!@ libuv
       // 创建一个 libuv 事件循环
    uv_loop_t *loop = uv_default_loop();

    // 创建一个定时器句柄
    uv_timer_t timer_req;

    // 初始化定时器：每 1000 毫秒触发一次
    uv_timer_init(loop, &timer_req);

    // 启动定时器：每 1000 毫秒触发一次定时器回调
    uv_timer_start(&timer_req, timer_callback, 1000, 1000);

    std::cout << "libuv test program running... Press Ctrl+C to exit."
              << std::endl;

    // 运行事件循环
    uv_run(loop, UV_RUN_DEFAULT);

    // 清理资源
    uv_loop_close(loop);

    return 0;
  } while (0);
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
#endif

#endif