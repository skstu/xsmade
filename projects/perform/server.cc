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
void Server::Process() {
  do {

  } while (0);
}
void Server::OnRequest(const RequestType &reqType, const std::string &body,
                       std::string &res) {
  /*
      "code": 0,
    "message": "ok",
    "browser_id": 19264,
  */
  int code = -1;
  std::string message;
  long long brwpid = 0;

  switch (reqType) {
  case RequestType::SERVER_OPEN: {

  } break;
  case RequestType::SERVER_CLOSE: {

  } break;
  case RequestType::BROWSER_OPEN: {
    rapidjson::Document doc;
    if (doc.Parse(body.data(), body.size()).HasParseError() ||
        doc.ObjectEmpty()) {
      code = -1001;
      message = "Invalid request data";
      break;
    }

    stl::Directory::Create(Config::ConfigGet()->WorkProjectsPath());
    stl::File::WriteFile(Config::ConfigGet()->WorkProjectsPath() +
                             "/brwccfg.json",
                         Json::toString(doc));

    // stl::Directory::EnumU8(const std::string &inputPath,
    // std::map<std::string, std::string> &dirs, std::map<std::string,
    // std::string> &files)
#if 0
    const char *args[] = {chromium_path, /*"--proxy-server=127.0.0.1",*/
                          "www.baidu.com", nullptr};
    long long pid = 0;
    int status = xs_sys_process_spawn(chromium_path, args, &pid);
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    xs_sys_process_kill(pid);
        xs_sys_process_spawn(const char *proc, const char **args,
                         long long *out_pid) code = 0;
#endif

    message = "ok";
  } break;
  case RequestType::BROWSER_CLOSE: {

  } break;
  case RequestType::BROWSER_GET: {

  } break;
  default:
    break;
  }

  do {
    rapidjson::Document resDoc(rapidjson::Type::kObjectType);
    resDoc.AddMember(
        rapidjson::Value().SetString("code", resDoc.GetAllocator()).Move(),
        rapidjson::Value().SetInt(code).Move(), resDoc.GetAllocator());
    resDoc.AddMember(
        rapidjson::Value().SetString("message", resDoc.GetAllocator()).Move(),
        rapidjson::Value()
            .SetString(message.c_str(), resDoc.GetAllocator())
            .Move(),
        resDoc.GetAllocator());
    res = Json::toString(resDoc);
  } while (0);
}
void Server::Listen() {
  server_->Post("/server/open",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::SERVER_OPEN, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/server/close",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::SERVER_CLOSE, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/browser/down",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  // OnRequest(RequestType::BROWSER_OPEN, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/browser/open",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::BROWSER_OPEN, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/browser/close",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::BROWSER_CLOSE, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/browser/get",
                [this](const httplib::Request &req, httplib::Response &res) {
                  std::string repRes;
                  OnRequest(RequestType::BROWSER_GET, req.body, repRes);
                  res.set_content(repRes.empty() ? "{}" : repRes,
                                  "application/json; charset=utf-8");
                });
  server_->Post("/", [](const httplib::Request &req, httplib::Response &res) {

  });

  do {
    std::string route_path =
        Config::ConfigGet()->CurrentProcessPath() + "/route.json";

    rapidjson::Document doc;
    std::string route_buffer = stl::File::ReadFile(route_path);
    if (doc.Parse(route_buffer.data(), route_buffer.size()).HasParseError()) {
      stl::File::Remove(route_path);
      stl::File::Create(route_path);
      stl::File::WriteFile(route_path, "{}");
      doc.Parse("{}");
    }
    if (doc.HasMember("server_port"))
      doc.RemoveMember("server_port");
    doc.AddMember(
        rapidjson::Value().SetString("server_port", doc.GetAllocator()).Move(),
        rapidjson::Value().SetUint(port_).Move(), doc.GetAllocator());

    stl::File::WriteFile(route_path, Json::toString(doc));
  } while (0);
#if _DEBUG
  server_->listen("127.0.0.1", 65535);
#else
  server_->listen("127.0.0.1", port_);
#endif
}
