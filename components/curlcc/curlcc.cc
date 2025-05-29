#include "curlcc.h"

Curl::Curl() {
  Init();
}
Curl::~Curl() {
  UnInit();
}
void Curl::Init() {
  CURLcode code;
  do {
    code = curl_global_init(CURL_GLOBAL_ALL);
    if (CURLE_OK != code)
      break;
    ready_.store(true);
  } while (0);
}
void Curl::UnInit() {
  curl_global_cleanup();
}
bool Curl::Start() {
  do {
    if (!ready_.load())
      break;

    open_.store(true);
  } while (0);
  return open_.load();
}
void Curl::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
  } while (0);
}
bool Curl::Ready() const {
  return ready_.load();
}
bool Curl::Perform() {
  bool result = false;
  do {
    WebCrawler crawler(4);
    crawler.setUserAgent(
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Chrome/136.0.0.0 Safari/537.36");
    crawler.setCookieFile("my_cookies.txt");
    crawler.addUrl("https://example.com");
    crawler.addUrl("https://www.baidu.com");
    crawler.addUrl("https://www.google.com/search?q=memade");

    crawler.waitUntilDone(); // 自动等待所有任务完成
    crawler.shutdown();      // 安全退出线程池
  } while (0);
  return result;
}
//////////////////////////////////////////////////////////////////////////////////////////
static Curl *__gpCurl = nullptr;
Curl *Curl::Create() {
  if (!__gpCurl)
    __gpCurl = new Curl();
  return __gpCurl;
}
void Curl::Destroy() {
  SK_DELETE_PTR(__gpCurl);
}
#ifdef __cplusplus
extern "C" {
#endif

SHARED_API void *interface_init(void *data, unsigned long len) {
  auto curl = Curl::Create();

  return dynamic_cast<ICurl *>(curl);
}
SHARED_API void interface_uninit() {
  Curl::Destroy();
}

#ifdef __cplusplus
}
#endif
