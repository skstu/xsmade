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
  return false;
}
void Curl::Stop() {
}
bool Curl::Ready() const {
  return ready_.load();
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
