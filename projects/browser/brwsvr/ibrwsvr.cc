#include "server.h"
extern "C" {
static int started = 0;
SHARED_API int request(const char *protocol, unsigned long protocol_len) {
  int result = MP_EUNKN;
  do {
    if (!protocol || protocol_len <= 0) {
      result = MP_EINVALIDREQ;
      break;
    }
    Server::GetOrCreate()->Request(
        new IRequest(std::string(protocol, protocol_len)));
    result = MP_DONE;
  } while (0);
  return result;
}
SHARED_API int
register_request_cbs(tf_frame_buffer_stream_cb frame_buffer_stream_cb,
                     tf_notify_cb notify_cb) {
  int result = MP_EUNKN;
  Server::GetOrCreate()->RegisterCbs(frame_buffer_stream_cb, notify_cb);
  result = MP_OK;
  return result;
}

////////////////////////////////////////////////////////////////////////////////////
SHARED_API char *malloc_s(size_t len) {
  char *result = nullptr;
  if (len) {
    result = (char *)malloc(len);
  }
  return result;
}
SHARED_API void free_s(void **p) {
  if (p && *p) {
    free(*p);
    *p = nullptr;
  }
}
SHARED_API int startup(void) {
  int result = MP_EUNKN;
  do {
    if (started) {
      result = MP_EALREADY;
      break;
    }
    auto config = Config::GetOrCreate();
    auto brwmnr = Brwmnr::GetOrCreate();
    auto server = Server::GetOrCreate();

    LOG_INIT(config->GetPath().logs_path);
    if (!server->Start())
      break;
    started = 1;
    result = MP_OK;
  } while (0);
  return result;
}
SHARED_API void cleanup(void) {
  started = 0;
  Brwmnr::Destroy();
  Server::Destroy();
  Config::Destroy();
  LOG_UNINIT;
}
} /// extern "C"