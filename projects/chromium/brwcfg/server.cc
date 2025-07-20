#include "brwcfg.h"

Server::Server() {
  Init();
}
Server::~Server() {
  UnInit();
}
void Server::Init() {
  port_ = xs_sys_get_free_port();
  server_ = new httplib::Server();
}
void Server::UnInit() {
  SK_DELETE_PTR(server_);
}
const std::uint16_t &Server::GetPort() const {
  return port_;
}
const std::string &Server::GetHost() const {
  return host_;
}
bool Server::Start() {
  do {
    if (open_.load())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { Process(); });
    threads_.emplace_back([this]() { Listen(); });
    server_->wait_until_ready();
  } while (0);
  return open_.load();
}
void Server::Stop() {
  do {
    if (!open_.load())
      break;
    server_->stop();
    open_.store(false);
    for (auto &t : threads_) {
      if (t.joinable())
        t.join();
    }
    threads_.clear();
  } while (0);
}
void Server::Listen() {
  do {
    server_->Post("/chromium/cookies",
                  [](const httplib::Request &req, httplib::Response &res) {
                    std::cout << req.body << std::endl;
                    res.set_content("{}", "application/json; charset=utf-8");
                  });
    server_->listen(host_, port_);
  } while (0);
}
void Server::Process() {
  do {
    if (!open_.load())
      break;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  } while (1);
}
///////////////////////////////////////////////////////////////////////////////
static Server *__gpsServer = nullptr;
Server *Server::GetOrCreate() {
  if (!__gpsServer)
    __gpsServer = new Server();
  return __gpsServer;
}
void Server::Destroy() {
  SK_DELETE_PTR(__gpsServer);
}