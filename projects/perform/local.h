#if !defined(__9A251ADD_7C16_48FD_8E24_652C6BF9CD17__)
#define __9A251ADD_7C16_48FD_8E24_652C6BF9CD17__

enum class PerformProcessType : unsigned long {
  DEFAULT = 0x00,
  UTILITY = DEFAULT,
  IBROWSER = 0x01, //!@ browser interface service
  DOWNLOAD = 0x02, //!@ downloader
  STREAMPP = 0x03, //!@ FlowRelay service 'stream' "STUN" and "TURN"
};

enum class FFXStreamServerType : unsigned short {
  TCP = 0x00,
  UPD = 0x10,
  LOOP = 0x20,
};

enum class ComponentType : unsigned long long {
  FFX_SCREEN_RECORDING = 0x101000,
  FFX_RTSP_SERVER = 0x102000,
  FFX_RTSP_SERVER_TCP =
      FFX_RTSP_SERVER | (unsigned long long)FFXStreamServerType::TCP,
  FFX_RTSP_SERVER_UDP =
      FFX_RTSP_SERVER | (unsigned long long)FFXStreamServerType::UPD,
  FFX_RTSP_SERVER_LOOP =
      FFX_RTSP_SERVER | (unsigned long long)FFXStreamServerType::LOOP,
};

enum class ResponseCode : int {
  Ok = 0x0000,
  Done = 0x0001,
  SystemError = -0x1100,
  BrwCreateError = -0x1101,
  BrwNotfound = -0x1102,
  BrwKeyError = -0x1103,
  BrwCookieReqError = -0x1104,
  ProcessAlreadyRunning = -0x1110,
  BrwAlreadyRunning = -0x2100,
  FfxAlreadyRunning = -0x3100,
  UnsupportedRequest = -0x4100,
};

static std::map<ResponseCode, std::string> ResponseCodeString = {
    {ResponseCode::Ok, "Ok"},
    {ResponseCode::Done, "Request completed, please wait for asynchronous push."},
    {ResponseCode::SystemError, "SystemError"},
    {ResponseCode::ProcessAlreadyRunning, "ProcessAlreadyRunning"},
    {ResponseCode::BrwAlreadyRunning, "BrwAlreadyRunning"},
    {ResponseCode::FfxAlreadyRunning, "FfxAlreadyRunning"},
    {ResponseCode::UnsupportedRequest, "UnsupportedRequest"},
    {ResponseCode::BrwCreateError, "BrwCreateError"},
    {ResponseCode::BrwNotfound, "BrwNotfound"},
    {ResponseCode::BrwKeyError, "BrwKeyError"},
    {ResponseCode::BrwCookieReqError, "BrwCookieReqError"},
};

enum class RequestType : unsigned long long {
  UNKNOWN = 0x00000,
  SYSTEM_DEVICE = 0x10001,
  SERVER_OPEN = 0x10010,      //!@ 打开(初始化)服务
  SERVER_CLOSE = 0x10020,     //!@ 退出(关闭)服务
  BROWSER_OPEN = 0x10101,     //!@ 打开浏览器
  BROWSER_CLOSE = 0x10102,    //!@ 关闭浏览器
  BROWSER_GET = 0x10103,      //!@ 获取浏览器列表
  BROWSER_ACTIVATE = 0x10104, //@ 激活浏览器窗口
  BROWSER_GET_CACHE = 0x10105,//!@ 获取缓存(前端)
  BROWSER_COOKIES_GET = 0x10110, //!@ 获取cookies
  BROWSER_COOKIES_SET = 0x10111, //!@ 设置cookies
  BROWSER_COOKIES_DEL = 0x10112, //!@ 删除cookies
  FFX_START_SCREEN_RECORDING = 0x10201,
  FFX_STOP_SCREEN_RECORDING = 0x10202,
  PLUGIN_FFXUI_OPEN = 0x10301,
  PLUGIN_FFXUI_CLOSE = 0x10302,
  // BROWSER_DOWN = 0x10104,  //!@ 下载浏览器
};

class IConfig {
protected:
  virtual void __impl__() const = 0;
};
class IPerform {
public:
  virtual void Release() const = 0;
  virtual bool Start() = 0;
  virtual void Stop() = 0;
  virtual IConfig *ConfigGet() const = 0;

protected:
  virtual void __impl__() const = 0;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 22 Nov 2024 12:32:11 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__9A251ADD_7C16_48FD_8E24_652C6BF9CD17__