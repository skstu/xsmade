#include "config.h"
namespace {
constexpr int kThreadPoolSize = 8;
} // namespace

static size_t curlWriteCallback(void *contents, size_t size, size_t nmemb,
                                void *userp) {
  std::string *out = static_cast<std::string *>(userp);
  out->append(static_cast<char *>(contents), size * nmemb);
  return size * nmemb;
}
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
ICurl::IConfig *Curl::GetConfig() const {
  return dynamic_cast<ICurl::IConfig *>(Config::CreateOrGet());
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
void Curl::Free(void **p) const {
  if (p && (*p)) {
    free(*p);
    *p = nullptr;
  }
}
ICurl::IRequestArray *Curl::Perform(ICurl::IRequestArray *reqArray) {
  RequestArray *result = new RequestArray();
  std::vector<std::future<void>> futures;
  const size_t reqTotal = reqArray->Total();
  for (size_t i = 0; i < reqTotal; ++i) {
    futures.emplace_back(std::async(std::launch::async, [this, result, reqArray,
                                                         i]() {
      Request *req = dynamic_cast<Request *>(reqArray->Next(i));
      if (!req)
        return;
      CURL *curl = curl_easy_init();
      if (!curl)
        return;
      std::string response;
      curl_easy_setopt(curl, CURLOPT_URL, req->GetUrl());
      curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
      curl_easy_setopt(
          curl, CURLOPT_USERAGENT,
          "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/"
          "537.36 (KHTML, like Gecko) Chrome/138.0.7204.158 Safari/"
          "537.36");
      if (std::string(req->GetUrl()).find("https://") != std::string::npos) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
      }
      { // http headers
        struct curl_slist *header_list = nullptr;
        std::map<std::string, std::string> header_map = req->GetHeaders();
        for (const auto &it : header_map) {
          std::string h = it.first + ": " + it.second;
          header_list = curl_slist_append(header_list, h.c_str());
        }
        if (header_list) {
          curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
        }
      }
      {
        std::string proxy_address = req->GetProxyAddress();
        std::string proxy_username = req->GetProxyUsername();
        std::string proxy_password = req->GetProxyPassword();

        if (!proxy_address.empty()) {
          curl_easy_setopt(curl, CURLOPT_PROXY, proxy_address.c_str());
          if (req->GetProxyType() == ProxyType::SOCKS5) {
            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
            
          } else if (req->GetProxyType() == ProxyType::SOCKS4) {
            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
          } else {
            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
          }
          if (!proxy_username.empty()) {
            curl_easy_setopt(curl, CURLOPT_PROXYUSERNAME,
                             proxy_username.c_str());
          }
          if (!proxy_password.empty()) {
            curl_easy_setopt(curl, CURLOPT_PROXYPASSWORD,
                             proxy_password.c_str());
          }
        }
      }
      CURLcode res = curl_easy_perform(curl);
      req->SetResponseCode(static_cast<int>(res));
      if (CURLE_OK == res) {
        req->SetResponse(response);
      }
      result->Push(dynamic_cast<ICurl::IRequest *>(req));
      curl_easy_cleanup(curl);
    }));
  }
  for (auto &f : futures)
    f.get();
  return dynamic_cast<ICurl::IRequestArray *>(result);
}

ICurl::IRequest *Curl::CreateRequest() const {
  ICurl::IRequest *result = nullptr;
  std::unique_lock<std::mutex> lock(*mtx_, std::defer_lock);
  lock.lock();
  Request *req = new Request();
  result = dynamic_cast<ICurl::IRequest *>(req);
  lock.unlock();
  return result;
}
ICurl::IRequestArray *Curl::CreateRequestArray() const {
  ICurl::IRequestArray *result = nullptr;
  std::unique_lock<std::mutex> lock(*mtx_, std::defer_lock);
  lock.lock();
  RequestArray *reqs = new RequestArray();
  result = dynamic_cast<ICurl::IRequestArray *>(reqs);
  lock.unlock();
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

#if 0
do {
    const std::vector<std::string> &urls =
        Config::CreateOrGet()->GetCurlRequestUrls();
    if (urls.empty())
      break;
    WebCrawler crawler(urls.size());
    for (const auto &url : urls) {
      crawler.addUrl(url);
    }
    crawler.setSocks5Proxy(
        Config::CreateOrGet()->GetCurlProxyString(),
        Config::CreateOrGet()->GetCurlProxyInfo().username,
        Config::CreateOrGet()->GetCurlProxyInfo().password);
    // crawler.setUserAgent(
    //     "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML,
    //     " "like Gecko) Chrome/136.0.0.0 Safari/537.36");
    // crawler.setCookieFile("my_cookies.txt");
    // crawler.addUrl("https://example.com");
    // crawler.addUrl("https://www.baidu.com");
    // crawler.addUrl("https://www.google.com/search?q=memade");

    crawler.waitUntilDone(); // 自动等待所有任务完成
    crawler.shutdown();      // 安全退出线程池
  } while (0);
#endif