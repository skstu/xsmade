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
  server_->Post("/chromium/adscore",
                [this](const httplib::Request &req, httplib::Response &res) {
                  auto now = std::chrono::system_clock::now();
                  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                  std::tm tm;
#ifdef _WIN32
                  localtime_s(&tm, &now_c);
#else
    localtime_r(&now_c, &tm);
#endif
                  std::cout << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
                            << "] " << req.body << std::endl;
                  LOG_INFO("{}", req.body);
                  res.set_content("{}", "application/json; charset=utf-8");
                  Startup::GetOrCreate()->ChromiumClose();
                });

  server_->Post("/chromium/spider",
                [this](const httplib::Request &req, httplib::Response &res) {
                  auto now = std::chrono::system_clock::now();
                  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                  std::tm tm;
#ifdef _WIN32
                  localtime_s(&tm, &now_c);
#else
    localtime_r(&now_c, &tm);
#endif
                  std::cout << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
                            << "] " << req.body << std::endl;
                  LOG_INFO("{}", req.body);
                  res.set_content("{}", "application/json; charset=utf-8");
                });

  server_->Post("/adscore/ub",
                [this](const httplib::Request &req, httplib::Response &res) {
                  auto now = std::chrono::system_clock::now();
                  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                  std::tm tm;
#ifdef _WIN32
                  localtime_s(&tm, &now_c);
#else
    localtime_r(&now_c, &tm);
#endif
                  std::cout << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
                            << "] " << req.body << std::endl;

                  LOG_INFO("{}", req.body);
                  res.set_content("{}", "application/json; charset=utf-8");
                });

  server_->Post("/adscore/chrome/fps",
                [this](const httplib::Request &req, httplib::Response &res) {
                  auto now = std::chrono::system_clock::now();
                  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                  std::tm tm;
#ifdef _WIN32
                  localtime_s(&tm, &now_c);
#else
    localtime_r(&now_c, &tm);
#endif
                  std::cout << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
                            << "] " << req.body << std::endl;
                  LOG_INFO("{}", req.body);
                  res.set_content("{}", "application/json; charset=utf-8");
                });
  server_->Post("/adscore/ub",
                [this](const httplib::Request &req, httplib::Response &res) {
                  auto now = std::chrono::system_clock::now();
                  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                  std::tm tm;
#ifdef _WIN32
                  localtime_s(&tm, &now_c);
#else
    localtime_r(&now_c, &tm);
#endif
                  std::cout << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
                            << "] " << req.body << std::endl;

                  LOG_INFO("{}", req.body);
                  res.set_content("{}", "application/json; charset=utf-8");
                });

  server_->Post("/chromium/cookies",
                [this](const httplib::Request &req, httplib::Response &res) {
                  // 获取当前时间
                  auto now = std::chrono::system_clock::now();
                  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                  std::tm tm;
#ifdef _WIN32
                  localtime_s(&tm, &now_c);
#else
    localtime_r(&now_c, &tm);
#endif
                  std::cout << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
                            << "] " << req.body << std::endl;
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
    // current_port = xs_sys_get_free_port();
  }
  server_->listen("0.0.0.0", current_port);
}
