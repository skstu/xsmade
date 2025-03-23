#if !defined(__7C8631D5_07CD_43BB_85CB_B012A8088BC7__)
#define __7C8631D5_07CD_43BB_85CB_B012A8088BC7__
#include <xs.h>
#include <rapidjson.h>
#include <tinyxml2.hpp>
#include <fmt/format.h>
#include <log.hpp>
#include <conv.hpp>
#include <components/uvpp/export.h>
using namespace uvpp;
#include "ibrwsvr.h"
#include "isettings.hpp"
#include "configure.hpp"
#include "protocol.hpp"
#include "config.h"
#include "ffcodec.h"
#include "brwobj.h"
#include "brwmnr.h"
class Server final {
public:
  static Server *GetOrCreate();
  static void Destroy();

private:
  Server();
  virtual ~Server();

private:
  void Init();
  void UnInit();

public:
  bool Start(void);
  void Stop(void);
  void Request(IRequest *);
  void RegisterCbs(tf_frame_buffer_stream_cb, tf_notify_cb);
  void OnNotify(const browser_id_t &, const std::string &) const;
  void OnFrameBufferStream(const browser_id_t &, const char *,
                           const size_t &) const;
  bool RequestInput(const browser_id_t &, const std::string &) const;

private:
  std::atomic_bool ready_ = false;
  std::atomic_bool open_ = false;

  stl::container::queue<IRequest *> request_queue_;

  stl::tfThreads threads_;
  void Process(void);
  tf_notify_cb notify_cb_ = nullptr;
  tf_frame_buffer_stream_cb frame_buffer_stream_cb_ = nullptr;

private:
  IUvpp *uvpp_ = nullptr;
  IService *uvpp_service_ = nullptr;
  IConfig *uvpp_config_ = nullptr;
#if ENABLE_FFCODEC
  FFCodec *ffcodec_ = nullptr;
#endif
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  stl::container::map<browser_id_t, uvpp::ISession *> sessions_gpu_;
  stl::container::map<browser_id_t, uvpp::ISession *> sessions_main_;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 14 Mar 2025 21:47:43 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__7C8631D5_07CD_43BB_85CB_B012A8088BC7__