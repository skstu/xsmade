#include "config.h"

Server::Server() {
  Init();
}
Server::~Server() {
  UnInit();
}
void Server::Init() {
  server_ = new httplib::Server();
}
void Server::UnInit() {
  SK_DELETE_PTR(server_);
}

bool Server::Start() {
  do {
    if (open_.load())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { Listen(); });
    server_->wait_until_ready();
  } while (0);
  return open_.load();
}

void Server::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    server_->stop();
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}
bool Server::IsOpen() const {
  return open_.load();
}
void Server::Listen() {
  server_->Post("/chromium/adscore", [this](const httplib::Request &req,
                                            httplib::Response &res) {
    std::cout << "[" << stl::Time::GetLogTimeCN() << "] " << req.body
              << std::endl;
    /*
[2025-07-26 12:56:20]
[{"type":"page_loaded","url":"https://www.bing.com/","path":"/chromium/adscore","result":0}]
*/
    LOG_INFO("{}", req.body);
    res.set_content("{}", "application/json; charset=utf-8");
    Startup::GetOrCreate()->NotifyRequestResult(req.body);
    Startup::GetOrCreate()->ChromiumClose();
  });

  server_->Post("/",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::cout << "[" << stl::Time::GetLogTimeCN() << "] "
                            << req.body << std::endl;
                  LOG_INFO("{}", req.body);
                  res.set_content("{}", "application/json; charset=utf-8");
                  Startup::GetOrCreate()->ChromiumClose();
                });

  unsigned short current_port = 65535;
  if (!Config::DevelopMode()) {
    // current_port = xs_sys_get_free_port();
  }
  server_->listen("0.0.0.0", current_port);
}
