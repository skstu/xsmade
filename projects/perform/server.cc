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
  if (server_) {
    delete server_;
    server_ = nullptr;
  }
}
bool Server::Start() {
  do {
    if (open_.load() || !server_)
      break;
    port_ = xs_sys_get_free_port();
    if (port_ <= 0)
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
void Server::Listen() {
  server_->Post("/server/open",
                [](const httplib::Request &req, httplib::Response &res) {});
  server_->Post("/server/close",
                [](const httplib::Request &req, httplib::Response &res) {});
  server_->Post("/browser/down",
                [](const httplib::Request &req, httplib::Response &res) {

                });
  server_->Post("/browser/open",
                [](const httplib::Request &req, httplib::Response &res) {
                  // open_browser();
                  auto a = 0;
                });
  server_->Post("/browser/close",
                [](const httplib::Request &req, httplib::Response &res) {

                });
  server_->Post("/browser/get",
                [](const httplib::Request &req, httplib::Response &res) {

                });
  server_->Post("/", [](const httplib::Request &req, httplib::Response &res) {

  });
  server_->listen("127.0.0.1", port_);
}