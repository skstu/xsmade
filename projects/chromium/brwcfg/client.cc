#include "brwcfg.h"

Client::Client() {
  Init();
}
Client::~Client() {
  UnInit();
}
void Client::Init() {
}
void Client::UnInit() {
}
bool Client::Start() {
  do {
    if (open_.load())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { Process(); });
  } while (0);
  return open_.load();
}
void Client::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}

bool Client::Post(const std::string &path, const std::string &body) {
  send_data_q_.push(std::make_tuple(path, body));
  return true;
}
void Client::Process() {
  do {
    do {
      if (send_data_q_.empty())
        break;
      rapidjson::Document doc(rapidjson::Type::kArrayType);
      auto msgs = send_data_q_.pops();
      for (const auto &msg : msgs) {
        std::string path = std::get<0>(msg);
        std::string content = std::get<1>(msg);
        rapidjson::Document itemDoc;
        if (itemDoc.Parse(content.data(), content.size()).HasParseError())
          continue;
        if (!itemDoc.IsObject())
          continue;
        doc.PushBack(rapidjson::Value(itemDoc, doc.GetAllocator()).Move(),
                     doc.GetAllocator());
      }
      std::string content = Json::toString(doc);
      httplib::Client cli("127.0.0.1", 65535);
      httplib::Headers heads = {{"content-type", "application/json"}};
      auto postRes = cli.Post("/chromium/cookies", heads, content.data(),
                              content.size(), "application/json");
    } while (0);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (!open_.load())
      break;
  } while (1);
}
//////////////////////////////////////////////////////////////////////////////////////////
Client *__gpsClient = nullptr;
Client *Client::GetOrCreate() {
  if (!__gpsClient)
    __gpsClient = new Client();
  return __gpsClient;
}
void Client::Destroy() {
  SK_DELETE_PTR(__gpsClient);
}
