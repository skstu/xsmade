#include "perform.h"
#if defined(__OSWIN__)
static HANDLE ghWritePipe = nullptr;
static PROCESS_INFORMATION g_pi = {};
static void sendCommand(HANDLE writePipe, const std::string &command) {
  do {
    if (!writePipe)
      break;
    DWORD written;
    if (!WriteFile(writePipe, command.c_str(), command.size(), &written,
                   nullptr))
      break;
    if (!WriteFile(writePipe, "\n", 1, &written, nullptr))
      break;
  } while (0);
}
#endif
FFmpeg::FFmpeg() {
}
FFmpeg::~FFmpeg() {
}
bool FFmpeg::Start(const std::vector<std::string> &cmdline, const bool &show) {
  do {
    if (open_.load())
      break;
    if (!stl::File::Exists(main))
      break;
#if defined(__OSWIN__)
    // 创建管道
    HANDLE readPipe;
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), nullptr,
                              TRUE}; // 允许子进程继承管道句柄

    if (!CreatePipe(&readPipe, &ghWritePipe, &sa, 0))
      break;

    // 设置写端句柄为非继承
    if (!SetHandleInformation(ghWritePipe, HANDLE_FLAG_INHERIT, 0))
      break;

    // 配置启动信息
    STARTUPINFOA si = {sizeof(STARTUPINFO)};
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput = readPipe; // 将子进程的标准输入重定向到我们创建的管道
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.wShowWindow = SW_HIDE; // 隐藏子进程窗口

    // 构建 ffmpeg 命令
    std::string ffmpegCmd;
    for (const auto &node : cmdline) {
      ffmpegCmd.append(node).append(" ");
    }
    if (!ffmpegCmd.empty())
      ffmpegCmd.pop_back();
    if (!CreateProcessA(Conv::u16_to_u8(main).c_str(), // 应用程序名称
                        ffmpegCmd.data(),              // 命令行
                        nullptr,                       // 进程安全属性
                        nullptr,                       // 线程安全属性
                        TRUE,                          // 继承句柄
                        CREATE_NO_WINDOW,              // 创建标志：无窗口
                        nullptr,                       // 环境变量
                        nullptr,                       // 工作目录
                        &si,                           // 启动信息
                        &g_pi))                        // 进程信息
      break;

    // 关闭管道的读端，因为只需要写入
    CloseHandle(readPipe);
#elif defined(__OSMAC__)

#endif
    open_.store(true);
  } while (0);
  return open_.load();
}
void FFmpeg::Stop() {
  do {
    if (!open_.load())
      break;
#if defined(__OSWIN__)
    // 模拟录制一段时间
    // std::this_thread::sleep_for(std::chrono::seconds(10));

    // 发送 'q' 指令
    sendCommand(ghWritePipe, "q\n");

    // 等待子进程退出
    WaitForSingleObject(g_pi.hProcess, INFINITE);

    // 清理资源
    CloseHandle(g_pi.hProcess);
    CloseHandle(g_pi.hThread);
    CloseHandle(ghWritePipe);
#elif defined(__OSMAC__)

#endif
    open_.store(false);
  } while (0);
}
void FFmpeg::Release() const {
  delete this;
}
#if 0


bool FFmpeg::Start() {
  do {
    if (open_.load())
      break;

    open_.store(true);
  } while (0);
  return open_.load();
}
void FFmpeg::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
  } while (0);
}
const std::string &FFmpeg::GetName() const {
  return name_;
}
const std::uint64_t &FFmpeg::GetIdentify() const {
  return identify_;
}
#endif