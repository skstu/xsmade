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

  server_->Post("/browser/cookies",
                [this](const httplib::Request &req, httplib::Response &res) {
                  // std::string repRes;
                  // IRequest reqObj(req.body,
                  // Config::CreateOrGet()->GetCurrentDir()); reqObj >> repRes;
                  std::cout << req.body << std::endl;
                  res.set_content("{}", "application/json; charset=utf-8");
                });
  server_->Post("/browser/open", [this](const httplib::Request &req,
                                        httplib::Response &res) {
    std::string repRes;

    IRequest reqObj(req.body, Config::CreateOrGet()->GetCurrentDir());
    Browser::CreateOrGet()->CreateChromium(reqObj);
    reqObj >> repRes;
    res.set_content(repRes.empty() ? "{}" : repRes,
                    "application/json; charset=utf-8");
  });
  server_->Post("/browser/close",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  unsigned short current_port = 65535;
  if (!Config::DevelopMode()) {
    current_port = xs_sys_get_free_port();
  }
  server_->listen("127.0.0.1", current_port);
}
