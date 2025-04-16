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
class Pipe {
  typedef void (*tfMessageCb)(const unsigned long &cmd, const std::string &data,
                              unsigned long &replyCmd, std::string &reply);
  typedef void (*tfConnentedCb)(unsigned long &reqCmd, std::string &request);
  typedef void (*tfDisconnentCb)(bool &exit);
  typedef void (*tfErrorCb)(const std::string &error);

public:
  inline Pipe(const std::string &addr);
  inline void Release() const;

private:
  inline ~Pipe();
  inline void Init();
  inline void UnInit();

public:
  inline bool Start();
  inline void Stop();
  inline bool Write(const unsigned long &cmd, const std::string &data);
  inline void RegisterConnentedCb(const tfConnentedCb &);
  inline void RegisterDisconnentCb(const tfDisconnentCb &);
  inline void RegisterErrorCb(const tfErrorCb &);
  inline void RegisterMessageCb(const tfMessageCb &);

private:
  inline bool Connent();
  inline void Process();
  inline void Worker();
  inline bool Packet(const unsigned long &cmd, const std::string &in,
                     std::string &out) const;
  inline bool UnPacket(const std::string &in, unsigned long &cmd,
                       std::string &out) const;
  inline bool Read(const char *buf, const ssize_t &len, unsigned long &cmd,
                   std::string &out) const;

  inline void OnMessage(const unsigned long &cmd, const std::string &data,
                        unsigned long &replyCmd, std::string &reply);
  inline void OnConnented(unsigned long &reqCmd, std::string &request);
  inline void OnDisconnent(bool &exit);
  inline void OnError(const std::string &error);

private:
  const std::string addr_;
  std::atomic_bool open_{false};
  std::atomic_bool ready_{false};
  std::atomic_int fd_{-1};
  std::vector<std::thread> threads_;
  std::queue<std::string> write_queue_;
  std::queue<std::tuple<unsigned long, std::string>> read_queue_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  std::shared_ptr<std::mutex> mtx_rw_ = std::make_shared<std::mutex>();
  std::shared_ptr<std::mutex> mtx_rd_ = std::make_shared<std::mutex>();
  tfMessageCb message_cb_ = nullptr;
  tfErrorCb error_cb_ = nullptr;
  tfConnentedCb connented_cb_ = nullptr;
  tfDisconnentCb disconnent_cb_ = nullptr;
};

inline Pipe::Pipe(const std::string &addr) : addr_(addr) {
  Init();
}
inline Pipe::~Pipe() {
  UnInit();
}
inline void Pipe::Init() {
  do {
    if (addr_.empty())
      break;
    ready_.store(true);
  } while (0);
}
inline void Pipe::UnInit() {
  if (fd_.load() > 0) {
    close(fd_.load());
    fd_.store(-1);
  }
  ready_.store(false);
}
inline void Pipe::Release() const {
  delete this;
}
inline bool Pipe::Connent() {
  bool result = false;
  do {
    if (addr_.empty())
      break;
    if (fd_.load() > 0) {
      close(fd_.load());
      fd_.store(-1);
    }
    fd_.store(socket(AF_LOCAL, SOCK_STREAM, 0));
    if (fd_.load() < 0)
      break;
    const char *pipe_name = addr_.c_str();
    struct sockaddr_un srv_addr = {0};
    srv_addr.sun_family = AF_LOCAL;
    snprintf(srv_addr.sun_path, sizeof(srv_addr.sun_path), "%s", pipe_name);
    if (0 > connect(fd_.load(), (struct sockaddr *)&srv_addr, sizeof(srv_addr)))
      break;
    int flags = fcntl(fd_.load(), F_GETFL, 0);
    fcntl(fd_.load(), F_SETFL, flags | O_NONBLOCK);
    result = true;
  } while (0);
  return result;
}
inline bool Pipe::Start() {
  do {
    if (!ready_.load())
      break;
    if (open_.load())
      break;
    bool connect_result = Connent();
    if (!connect_result) {
      OnError("Connect error");
      break;
    }
    unsigned long reqCmd = 0;
    std::string request;
    OnConnented(reqCmd, request);
    if (!request.empty()) {
      Write(reqCmd, request);
    }
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
inline void Pipe::OnMessage(const unsigned long &cmd, const std::string &data,
                            unsigned long &replyCmd, std::string &reply) {
  std::lock_guard<std::mutex> lck(*mtx_);
  if (message_cb_) {
    message_cb_(cmd, data, replyCmd, reply);
  }
}
inline void Pipe::OnConnented(unsigned long &reqCmd, std::string &request) {
  std::lock_guard<std::mutex> lck(*mtx_);
  if (connented_cb_) {
    connented_cb_(reqCmd, request);
  }
}
inline void Pipe::OnDisconnent(bool &exit) {
  std::lock_guard<std::mutex> lck(*mtx_);
  if (disconnent_cb_) {
    disconnent_cb_(exit);
  }
}
inline void Pipe::OnError(const std::string &error) {
  std::lock_guard<std::mutex> lck(*mtx_);
  if (error_cb_) {
    error_cb_(error);
  }
}
inline void Pipe::RegisterConnentedCb(const tfConnentedCb &cb) {
  std::lock_guard<std::mutex> lck(*mtx_);
  connented_cb_ = cb;
}
inline void Pipe::RegisterDisconnentCb(const tfDisconnentCb &cb) {
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
  std::unique_lock<std::mutex> lck(*mtx_rw_, std::defer_lock);
  lck.lock();
  do {
    std::string data;
    if (!Packet(cmd, in, data))
      break;
    write_queue_.push(data);
    result = true;
  } while (0);
  lck.unlock();
  return result;
}
inline void Pipe::Worker() {
  volatile bool idle = false;
  do {
    idle = false;
    do {
      std::tuple<unsigned long, std::string> data;
      std::unique_lock<std::mutex> lck(*mtx_rd_, std::defer_lock);
      lck.lock();
      if (read_queue_.empty()) {
        idle = true;
        break;
      }
      data = read_queue_.front();
      read_queue_.pop();
      lck.unlock();

      const unsigned long cmd = std::get<0>(data);
      const std::string body = std::get<1>(data);

      std::string reply;
      unsigned long replyCmd = 0;
      OnMessage(cmd, body, replyCmd, reply);
      if (!reply.empty()) {
        Write(replyCmd, reply);
      }
      // if (body.empty())
      //   break;
      // Write(cmd, "Hello!!!!!!!!!!!");
      // std::cout << cmd << time(NULL) << std::endl;
    } while (0);
    if (!open_.load())
      break;
    std::this_thread::sleep_for(std::chrono::milliseconds(idle ? 100 : 20));
  } while (true);
}
inline void Pipe::Process() {
  struct pollfd pfd[2];
  memset(pfd, 0, sizeof(pfd));
  pfd[0].fd = fd_.load();
  pfd[0].events = POLLIN;
  pfd[1].fd = fd_.load();
  pfd[1].events = POLLOUT;

  bool exit = false;
  do {
    int ret = poll(pfd, 2, -1);
    if (ret < 0) {
      OnError("poll error: ");
      // std::cerr << "poll error: " << strerror(errno) << std::endl;
      break;
    }
    do {
      if (!(pfd[0].revents & POLLIN))
        break;
      char buf[8192] = {0};
      ssize_t bytes_read = read(pfd[0].fd, buf, sizeof(buf));
      if (bytes_read > 0) {
        std::string out;
        unsigned long cmd = 0;
        if (!Read(buf, bytes_read, cmd, out)) {
          OnError("Read error: ");
          // std::cerr << "Read error: " << strerror(errno) << std::endl;
          exit = true;
          break;
        }
        std::unique_lock<std::mutex> lck(*mtx_rd_, std::defer_lock);
        lck.lock();
        read_queue_.push(std::make_tuple(cmd, out));
        lck.unlock();
      } else if (bytes_read == 0) {
        // std::cout << "Connection closed." << std::endl;
        OnDisconnent(exit);
        break;
      } else {
        OnError("Read error: ");
        // std::cerr << "Read error: " << strerror(errno) << std::endl;
        exit = true;
        break;
      }
    } while (0);

    do {
      if (exit)
        break;
      if (!(pfd[1].revents & POLLOUT))
        break;
      std::string data;
      std::unique_lock<std::mutex> lck(*mtx_rw_, std::defer_lock);
      lck.lock();
      if (write_queue_.empty())
        break;
      data = write_queue_.front();
      write_queue_.pop();
      lck.unlock();
      if (data.empty())
        break;
      ssize_t bytes_written = write(pfd[1].fd, data.data(), data.size());
      if (bytes_written < 0) {
        OnError("Write error: ");
        // std::cerr << "Write error: " << strerror(errno) << std::endl;
        exit = true;
        break;
      }
    } while (0);

    if (!open_.load() || exit)
      break;
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  } while (true);
}
inline bool Pipe::Packet(const unsigned long &cmd, const std::string &in,
                         std::string &out) const {
  bool result = false;
  do {
    HEAD head = {0};
    out.append((char *)&head, sizeof(HEAD));
    PHEAD pHead = reinterpret_cast<PHEAD>(out.data());
    pHead->header_logo = 0xFAC9C2D0;
    pHead->footer_logo = 0xB4B4AAC1;
    pHead->command_code = cmd;
    pHead->zip_type = 0;
    pHead->encryption_type = 0;
    pHead->data_size = static_cast<decltype(pHead->data_size)>(in.size());
    pHead->original_size = pHead->data_size;
    out.pop_back();
    out.append(in);
    pHead = reinterpret_cast<PHEAD>(out.data());
    pHead->packet_size = out.size();
    result = true;
  } while (0);
  return result;
}
inline bool Pipe::UnPacket(const std::string &in, unsigned long &cmd,
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
inline bool Pipe::Read(const char *buf, const ssize_t &len, unsigned long &cmd,
                       std::string &out) const {
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
// #endif///#if BUILDFLAG(IS_LINUX)
#endif //#if defined (__OSLINUX__)
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 15 Apr 2025 05:28:28 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__9411D64F_928D_4958_89A2_603259F337F4__