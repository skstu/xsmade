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

  do {
    char *path_tmp = nullptr;
    size_t path_len = 0;
    xs_sys_process_getpath(&path_tmp, &path_len);
    std::string path =
        stl::Path::PathnameToPath(std::string(path_tmp, path_len));
    xs_sys_free((void **)&path_tmp);

    std::string route_path = path + "\\route.json";

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
  server_->listen("127.0.0.1", port_);
}