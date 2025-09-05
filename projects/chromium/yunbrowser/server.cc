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
    open_.store(false);
    server_->stop();
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}
bool Server::Ready() const {
  return open_.load();
}
void Server::OnRequest(const chromium::xsiumio::HttpRequestType &type,
                       const httplib::Request &req, httplib::Response &res) {
  chromium::IRequest *reqObj = new chromium::IRequest(req.body);
  std::string resBody = reqObj->GetResponse();
  if (!reqObj->Ready()) {
    reqObj->Release();
  } else {
    Startup::GetOrCreate()->Request(reqObj);
  }
  res.set_content(resBody, "application/json; charset=utf-8");
}
void Server::Listen() {
#if 0
  // server_->Post("/browser/create",
  //               [this](const httplib::Request &req, httplib::Response &res) {
  //                 Browser::CreateOrGet()->CreateChromiumResult(req.body);
  //                 res.set_content("{}", "application/json; charset=utf-8");
  //               });
  // server_->Post("/browser/close",
  //               [this](const httplib::Request &req, httplib::Response &res) {
  //                 Browser::CreateOrGet()->CreateChromiumResult(req.body);
  //                 res.set_content("{}", "application/json; charset=utf-8");
  //               });
  server_->Post("/chromium/init",
                [this](const httplib::Request &req, httplib::Response &res) {
                  Browser::CreateOrGet()->CreateChromiumResult(req.body);
                  res.set_content("{}", "application/json; charset=utf-8");
                });
  server_->Post(
      "/chromium/google_search_results",
      [this](const httplib::Request &req, httplib::Response &res) {
        // Handle the request and send a response
        do {
          rapidjson::Document doc;
          if (doc.Parse(req.body.c_str(), req.body.size()).HasParseError())
            break;
          if (!doc.IsObject())
            break;
          /*
    chrome.runtime.sendMessage({
      type: "google_search",
      url: window.location.href,
      path: "/chromium/google_search_results",
      results: {
      url: window.location.href,
      title: document.title,
      timestamp: Date.now(),
      search_results: resultsArr[],
      snapshoot: document.documentElement.outerHTML
    },
    });
*/
          std::string type, url, path, results;
          if (doc.HasMember("type") && doc["type"].IsString()) {
            type = doc["type"].GetString();
          }
          if (doc.HasMember("url") && doc["url"].IsString()) {
            url = doc["url"].GetString();
          }
          if (doc.HasMember("path") && doc["path"].IsString()) {
            path = doc["path"].GetString();
          }
          if (doc.HasMember("results") && doc["results"].IsObject()) {
            const auto &resObj = doc["results"];
            std::string title, url, search_results;
            if (resObj.HasMember("title") && resObj["title"].IsString()) {
              title = resObj["title"].GetString();
            }
            if (resObj.HasMember("url") && resObj["url"].IsString()) {
              url = resObj["url"].GetString();
            }
            if (resObj.HasMember("search_results") &&
                resObj["search_results"].IsArray()) {
              search_results = Json::toString(resObj["search_results"]);
            }
            if (resObj.HasMember("snapshoot")) {
              auto view = 0;
            }
            std::string log = fmt::format(R"(
url({})
title({})
search_results({})
)",
                                          url, title, search_results);

            std::cout << log << std::endl;
          }
          auto ss = 0;
        } while (0);
        auto sss = 0;
      });

#endif
  server_->Post("/chromium/adscore",
                [this](const httplib::Request &req, httplib::Response &res) {
  /*
[2025-07-26 12:56:20]
[{"type":"page_loaded","url":"https://www.bing.com/","path":"/chromium/adscore","result":0}]
*/
#if ENABLE_DEVELOP_MODE
                  LOG_INFO("{}", req.body);
                  std::cout << "[" << stl::Time::GetLogTimeCN() << "] "
                            << req.body << std::endl;
#endif
                  res.set_content("{}", "application/json; charset=utf-8");
                  Startup::GetOrCreate()->NotifyRequestResult(req.body);
                  // Startup::GetOrCreate()->ChromiumClose();
                });
  server_->Post(
      "/", [this](const httplib::Request &req, httplib::Response &res) {
        OnRequest(chromium::xsiumio::HttpRequestType::kPost, req, res);
      });

  unsigned short current_port = 65535;
  if (!Config::DevelopMode()) {
    // current_port = xs_sys_get_free_port();
  }
  std::cout << "server port " << current_port << std::endl;
  server_->listen("0.0.0.0", current_port);
}
void Server::Process() {
  std::string req;
  do {
    do {
      if (requests_.empty())
        break;
      auto reqs = requests_.pops();
      if (reqs.empty())
        break;
      for (const auto &req : reqs) {
      }
    } while (0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  } while (1);
}
/////////////////////////////////////////////////////////////////////
Server *__gpsServer = nullptr;
Server *Server::CreateOrGet() {
  if (!__gpsServer)
    __gpsServer = new Server();
  return __gpsServer;
}
void Server::Destroy() {
  if (__gpsServer) {
    delete __gpsServer;
    __gpsServer = nullptr;
  }
}