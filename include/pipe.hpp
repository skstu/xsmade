#if !defined(__9411D64F_928D_4958_89A2_603259F337F4__)
#define __9411D64F_928D_4958_89A2_603259F337F4__
#include "xs.h"
#include <string>
#include <memory>
#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <chrono>
#include <tuple>
#if defined(__OSLINUX__)
//#if BUILDFLAG(IS_LINUX)
#include <sys/poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>
#include <structs.h>
/////////////////////////////////////////////////////////////////////////////
#define PIPE_POLL_TIMEOUT -1
#define PIPE_POLL_NFDS 2
#define PIPE_POLL_POLLIN 0
#define PIPE_POLL_POLLOUT 1
#define PIPE_POLL_READ_BUFFER_MAX 8192
#define PIPE_POLL_DEFAULT_RECONNECT_INTERVAL_MS 3000
#define PIPE_POLL_DEFAULT_ADDREASS "/tmp/xs_pipe_server.sock"
typedef int tfPipeStatusType;
typedef tfPipeStatusType tfPipeErrornoType;
typedef unsigned long tfPipeCommandType;
class Pipe {
public:
  enum class Status : tfPipeStatusType {
    CONNFAILED = -0x04,
    RWERROR = -0x03,
    RDERROR = -0x02,
    POLLERROR = -0x01,
    UNKNOWN = 0x00,
    SUCCESS = 0x00,
    CONNECTING = 0x01,
    DISCONNECT = 0x02,
    READYED = 0x03,
    CLOSING = 0x04,
    CLOSED = 0x05,
  };
  class Config {
  public:
    inline Config();
    inline ~Config();
    inline void Release() const;
    inline const std::string &Address() const;
    inline void Address(const std::string &addr);
    inline const std::time_t &ReconnectionIntervalMS() const;
    inline void ReconnectionIntervalMS(const std::time_t &ms);

  private:
    inline void Init();
    inline void UnInit();

  private:
    std::string address_ = PIPE_POLL_DEFAULT_ADDREASS;
    std::time_t reconnection_interval_ms_ =
        PIPE_POLL_DEFAULT_RECONNECT_INTERVAL_MS;
    std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  };

public:
  typedef void (*tfMessageCb)(const tfPipeCommandType &cmd,
                              const std::string &data,
                              tfPipeCommandType &replyCmd, std::string &reply);
  typedef void (*tfConnectedCb)(tfPipeCommandType &reqCmd,
                                std::string &request);
  typedef void (*tfDisconnectCb)();
  typedef void (*tfErrorCb)(const tfPipeErrornoType &eno, const char *estr);
  typedef void (*tfReadyedCb)(void);
  typedef void (*tfWriteCb)(PHEAD head);

public:
  inline Pipe(const unsigned long long &server_identify = 0);
  inline void Release() const;
  inline Pipe::Config *ConfigGet() const;

private:
  inline ~Pipe();
  inline void Init();
  inline void UnInit();

public:
  inline bool Start();
  inline void Stop();
  inline bool Ready() const;
  inline Status StatusGet() const;
  inline bool Write(const tfPipeCommandType &cmd, const std::string &data);
  inline void RegisterConnectedCb(const tfConnectedCb &);
  inline void RegisterDisconnectCb(const tfDisconnectCb &);
  inline void RegisterErrorCb(const tfErrorCb &);
  inline void RegisterMessageCb(const tfMessageCb &);
  inline void RegisterReadyedCb(const tfReadyedCb &);
  inline void RegisterWriteCb(const tfWriteCb &);

private:
  inline void StatusSet(const Status &status);
  template <typename T> inline std::time_t TimeStamp();
  inline tfPipeErrornoType Connect();
  inline void Process();
  inline void Worker();
  inline void Packet(const std::string &in, std::string &out) const;
  inline bool UnPacket(const std::string &in, tfPipeCommandType &cmd,
                       std::string &out) const;
  inline bool Read(const char *buf, const ssize_t &len, tfPipeCommandType &cmd,
                   std::string &out) const;

  inline void OnMessage(const tfPipeCommandType &cmd, const std::string &data,
                        tfPipeCommandType &replyCmd, std::string &reply);
  inline void OnConnented(tfPipeCommandType &reqCmd, std::string &request);
  inline void OnDisconnent(void);
  inline void OnError(const tfPipeErrornoType &eno, const char *estr);
  inline void OnReadyed(void);
  inline void FDDestroy();
  inline bool FDCreate();

private:
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  std::shared_ptr<std::mutex> mtx_rw_ = std::make_shared<std::mutex>();
  std::shared_ptr<std::mutex> mtx_rd_ = std::make_shared<std::mutex>();

private:
  std::atomic_bool open_{false};
  std::atomic_bool ready_{false};
  std::vector<std::thread> threads_;
  std::queue<std::string> write_queue_;
  std::queue<std::tuple<tfPipeCommandType, std::string>> read_queue_;
  tfMessageCb message_cb_ = nullptr;
  tfErrorCb error_cb_ = nullptr;
  tfConnectedCb connented_cb_ = nullptr;
  tfDisconnectCb disconnent_cb_ = nullptr;
  tfWriteCb write_cb_ = nullptr;
  tfReadyedCb readyed_cb_ = nullptr;
  std::shared_ptr<Pipe::Config> config_ = std::make_shared<Pipe::Config>();
  int fd_ = -1;
  struct pollfd pollfds_[PIPE_POLL_NFDS];
  Status status_ = Status::UNKNOWN;
  const unsigned long long server_identify_;
};

inline Pipe::Pipe(const unsigned long long &server_identify)
    : server_identify_(server_identify) {
  Init();
}
inline Pipe::~Pipe() {
  UnInit();
}
inline void Pipe::Init() {
  fd_ = -1;
  memset(&pollfds_, 0x00, sizeof(pollfds_));
}
inline void Pipe::UnInit() {
  FDDestroy();
  ready_.store(false);
}
inline void Pipe::Release() const {
  delete this;
}
template <typename T> inline std::time_t Pipe::TimeStamp() {
  return std::chrono::duration_cast<T>(
             std::chrono::time_point_cast<T>(std::chrono::system_clock::now())
                 .time_since_epoch())
      .count();
}
//!@ Private
inline tfPipeErrornoType Pipe::Connect() {
  tfPipeErrornoType err = -1;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    if (config_->Address().empty())
      break;
    FDDestroy();
    if (!FDCreate())
      break;
    struct sockaddr_un srv_addr;
    memset(&srv_addr, 0x00, sizeof(srv_addr));
    srv_addr.sun_family = AF_LOCAL;
    snprintf(srv_addr.sun_path, sizeof(srv_addr.sun_path), "%s",
             config_->Address().c_str());
    if (0 > connect(fd_, (struct sockaddr *)&srv_addr, sizeof(srv_addr))) {
      err = errno;
      break;
    }
    err = 0;
  } while (0);
  return err;
}
inline bool Pipe::Ready() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return ready_.load() && open_.load() && (status_ == Pipe::Status::READYED);
}
inline Pipe::Status Pipe::StatusGet() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return status_;
}
//!@ Private
inline void Pipe::StatusSet(const Pipe::Status &status) {
  std::lock_guard<std::mutex> lck(*mtx_);
  status_ = status;
}
inline bool Pipe::Start() {
  do {
    if (open_.load())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { Worker(); });
    threads_.emplace_back([this]() { Process(); });
  } while (0);
  return open_.load();
}
inline void Pipe::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &it : threads_)
      it.join();
    threads_.clear();
  } while (0);
}
inline void Pipe::OnMessage(const tfPipeCommandType &cmd,
                            const std::string &data,
                            tfPipeCommandType &replyCmd, std::string &reply) {
  std::lock_guard<std::mutex> lck(*mtx_);
  if (message_cb_) {
    message_cb_(cmd, data, replyCmd, reply);
  }
}
inline void Pipe::OnConnented(tfPipeCommandType &reqCmd, std::string &request) {
  std::lock_guard<std::mutex> lck(*mtx_);
  if (connented_cb_) {
    connented_cb_(reqCmd, request);
  }
}
inline void Pipe::RegisterWriteCb(const tfWriteCb &cb) {
  std::lock_guard<std::mutex> lck(*mtx_);
  write_cb_ = cb;
}
inline void Pipe::RegisterReadyedCb(const tfReadyedCb &cb) {
  std::lock_guard<std::mutex> lck(*mtx_);
  readyed_cb_ = cb;
}
inline void Pipe::OnReadyed(void) {
  std::lock_guard<std::mutex> lck(*mtx_);
  if (readyed_cb_) {
    readyed_cb_();
  }
}
inline void Pipe::OnDisconnent() {
  std::lock_guard<std::mutex> lck(*mtx_);
  if (disconnent_cb_) {
    disconnent_cb_();
  }
}
inline void Pipe::OnError(const tfPipeErrornoType &eno, const char *estr) {
  std::lock_guard<std::mutex> lck(*mtx_);
  if (error_cb_) {
    error_cb_(eno, estr);
  }
}
inline void Pipe::RegisterConnectedCb(const tfConnectedCb &cb) {
  std::lock_guard<std::mutex> lck(*mtx_);
  connented_cb_ = cb;
}
inline void Pipe::RegisterDisconnectCb(const tfDisconnectCb &cb) {
  std::lock_guard<std::mutex> lck(*mtx_);
  disconnent_cb_ = cb;
}
inline void Pipe::RegisterErrorCb(const tfErrorCb &cb) {
  std::lock_guard<std::mutex> lck(*mtx_);
  error_cb_ = cb;
}
inline void Pipe::RegisterMessageCb(const tfMessageCb &cb) {
  std::lock_guard<std::mutex> lck(*mtx_);
  message_cb_ = cb;
}
inline bool Pipe::Write(const unsigned long &cmd, const std::string &in) {
  bool result = false;
  const Pipe::Status curstatus = StatusGet();
  do {
    if (curstatus != Pipe::Status::READYED)
      break;
    std::unique_lock<std::mutex> lckrw(*mtx_rw_, std::defer_lock);
    lckrw.lock();
    std::string data;
    Packet(in, data);
    PHEAD pHead = reinterpret_cast<PHEAD>(data.data());
    pHead->command_code = cmd;
    pHead->server_identify = server_identify_;
    if (write_cb_) {
      write_cb_(pHead);
    }
    write_queue_.push(data);
    lckrw.unlock();
    result = true;
  } while (0);
  return result;
}
inline void Pipe::Worker() {
  volatile bool idle = false;
  do {
    idle = false;
    const Status current_status = StatusGet();
    do {
      if (current_status != Pipe::Status::READYED)
        break;
      std::tuple<tfPipeCommandType, std::string> data;
      std::unique_lock<std::mutex> lck(*mtx_rd_, std::defer_lock);
      lck.lock();
      if (read_queue_.empty()) {
        idle = true;
        break;
      }
      data = read_queue_.front();
      read_queue_.pop();
      lck.unlock();

      const tfPipeCommandType cmd = std::get<0>(data);
      const std::string body = std::get<1>(data);

      std::string reply;
      tfPipeCommandType replyCmd = 0;
      OnMessage(cmd, body, replyCmd, reply);
      if (replyCmd != 0) {
        Write(replyCmd, reply);
      }
    } while (0);
    if (!open_.load())
      break;
    std::this_thread::sleep_for(std::chrono::milliseconds(idle ? 100 : 20));
  } while (true);
}
inline void Pipe::Process() {
  std::time_t time_prev = 0;
  bool notify_disconnent_flag = false;
  do {
    const std::time_t time_current = TimeStamp<std::chrono::milliseconds>();
    const Status current_status = StatusGet();
    do {
      if (current_status == Pipe::Status::CONNECTING ||
          current_status == Pipe::Status::READYED)
        break;
      if (time_current - time_prev < config_->ReconnectionIntervalMS())
        break;
      if (notify_disconnent_flag) {
        notify_disconnent_flag = false;
        OnDisconnent();
      }
      StatusSet(Pipe::Status::CONNECTING);
      time_prev = time_current;
      int err = Connect();
      if (!err) {
        notify_disconnent_flag = true;
        StatusSet(Pipe::Status::READYED);
        std::string request;
        tfPipeCommandType reqCmd = 0;
        OnConnented(reqCmd, request);
        if (!request.empty()) {
          Write(reqCmd, request);
        }
        OnReadyed();
      } else {
        StatusSet(Pipe::Status::CONNFAILED);
        OnError(err, strerror(err));
      }
    } while (false);

    do {
      if (current_status != Pipe::Status::READYED)
        break;
      if (poll(pollfds_, PIPE_POLL_NFDS, PIPE_POLL_TIMEOUT) < 0) {
        StatusSet(Pipe::Status::POLLERROR);
        OnError(errno, strerror(errno));
        break;
      }
      do {
        if (!(pollfds_[PIPE_POLL_POLLIN].revents & POLLIN))
          break;
        char buf[PIPE_POLL_READ_BUFFER_MAX] = {0};
        ssize_t bytes_read =
            read(pollfds_[PIPE_POLL_POLLIN].fd, buf, sizeof(buf));
        if (bytes_read > 0) {
          std::string out;
          unsigned long cmd = 0;
          if (!Read(buf, bytes_read, cmd, out)) {
            StatusSet(Pipe::Status::RDERROR);
            OnError(errno, strerror(errno));
            break;
          }
          std::unique_lock<std::mutex> lckrd(*mtx_rd_, std::defer_lock);
          lckrd.lock();
          read_queue_.push(std::make_tuple(cmd, out));
          lckrd.unlock();
        } else if (bytes_read == 0) {
          StatusSet(Pipe::Status::DISCONNECT);
          break;
        } else {
          StatusSet(Pipe::Status::RDERROR);
          break;
        }
      } while (0);

      do {
        if (!(pollfds_[PIPE_POLL_POLLOUT].revents & POLLOUT))
          break;
        std::string data;
        std::unique_lock<std::mutex> lckrw(*mtx_rw_, std::defer_lock);
        lckrw.lock();
        if (write_queue_.empty())
          break;
        data = write_queue_.front();
        write_queue_.pop();
        lckrw.unlock();
        if (data.empty())
          break;
        ssize_t bytes_written =
            write(pollfds_[PIPE_POLL_POLLOUT].fd, data.data(), data.size());
        if (bytes_written < 0) {
          StatusSet(Pipe::Status::RWERROR);
          OnError(errno, strerror(errno));
          break;
        }
      } while (0);
    } while (0);

    if (!open_.load())
      break;
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  } while (true);
}
inline Pipe::Config *Pipe::ConfigGet() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return config_.get();
}
inline void Pipe::Packet(const std::string &in, std::string &out) const {
  HEAD head;
  memset(&head, 0x00, sizeof(HEAD));
  out.append((char *)&head, sizeof(HEAD));
  PHEAD pHead = reinterpret_cast<PHEAD>(out.data());
  pHead->server_identify = 0;
  pHead->header_logo = 0xFAC9C2D0;
  pHead->footer_logo = 0xB4B4AAC1;
  pHead->command_code = 0;
  pHead->zip_type = 0;
  pHead->encryption_type = 0;
  pHead->data_size = static_cast<decltype(pHead->data_size)>(in.size());
  pHead->original_size = pHead->data_size;
  out.pop_back();
  out.append(in);
  pHead = reinterpret_cast<PHEAD>(out.data());
  pHead->packet_size = out.size();
}
inline bool Pipe::UnPacket(const std::string &in, tfPipeCommandType &cmd,
                           std::string &out) const {
  bool result = false;
  out.clear();
  cmd = 0;
  do {
    PHEAD pHead = (PHEAD)in.data();
    if (!pHead)
      break;
    if (!(pHead->header_logo == 0xFAC9C2D0 && pHead->footer_logo == 0xB4B4AAC1))
      break;
    cmd = pHead->command_code;
    result = true;
    if (pHead->data_size <= 0)
      break;
    out.append(pHead->data, pHead->data_size);
  } while (0);
  return result;
}
inline bool Pipe::Read(const char *buf, const ssize_t &len,
                       tfPipeCommandType &cmd, std::string &out) const {
  bool result = true;
  do {
    if (!buf || len <= 0)
      break;
    if (static_cast<size_t>(len) < sizeof(HEAD))
      break;
    PHEAD pHead = (PHEAD)buf;
    if (!(pHead->header_logo == 0xFAC9C2D0 &&
          pHead->footer_logo == 0xB4B4AAC1)) {
      result = false;
      break;
    }
    if (!(pHead->packet_size ==
          (sizeof(HEAD) - sizeof(HEAD::data) + pHead->data_size)))
      break;

    if (!UnPacket(std::string(buf, static_cast<size_t>(len)), cmd, out)) {
      result = false;
      break;
    }
    result = true;
  } while (0);
  return result;
}
//!@ Private
bool Pipe::FDCreate() {
  bool result = false;
  do {
    fd_ = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd_ < 0)
      break;
    pollfds_[PIPE_POLL_POLLIN].fd = fd_;
    pollfds_[PIPE_POLL_POLLIN].events = POLLIN;
    pollfds_[PIPE_POLL_POLLOUT].fd = fd_;
    pollfds_[PIPE_POLL_POLLOUT].events = POLLOUT;
    int flags = fcntl(fd_, F_GETFL, 0);
    fcntl(fd_, F_SETFL, flags | O_NONBLOCK);
    result = true;
  } while (0);
  return result;
}
//!@ Private
void Pipe::FDDestroy() {
  if (fd_ > 0) {
    close(fd_);
    fd_ = -1;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
inline Pipe::Config::Config() {
  Init();
}
inline Pipe::Config::~Config() {
  UnInit();
}
inline void Pipe::Config::Release() const {
  delete this;
}
inline void Pipe::Config::Init() {
}
inline void Pipe::Config::UnInit() {
}
inline const std::time_t &Pipe::Config::ReconnectionIntervalMS() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return reconnection_interval_ms_;
}
inline void Pipe::Config::ReconnectionIntervalMS(const std::time_t &ms) {
  std::lock_guard<std::mutex> lck(*mtx_);
  reconnection_interval_ms_ = ms;
}
inline const std::string &Pipe::Config::Address() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return address_;
}
inline void Pipe::Config::Address(const std::string &addr) {
  std::lock_guard<std::mutex> lck(*mtx_);
  address_ = addr;
}
// #endif///#if BUILDFLAG(IS_LINUX)
#endif //#if defined (__OSLINUX__)
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 15 Apr 2025 05:28:28 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__9411D64F_928D_4958_89A2_603259F337F4__