#include "config.h"
//////////////////////////////////////////////////////////////////////////////////////
Client::Packet::Packet() {
}
Client::Packet::~Packet() {
}
//////////////////////////////////////////////////////////////////////////////////////
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
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (open_.load())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { Process(); });
  } while (0);
  return open_.load();
}
void Client::Stop() {
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &t : threads_)
      t.join();
    threads_.clear();
  } while (0);
}
void Client::Post(const Packet &pak) {
  std::lock_guard<std::mutex> lck(*mtx_);
  requests_.push(pak);
}
void Client::Process() {
  do {
    std::unique_lock<std::mutex> lck(*mtx_, std::defer_lock);
    lck.lock();
    do {
      if (requests_.empty())
        break;
      auto reqs = requests_.pops();
      for (const auto &pak : reqs) {

        /*

httplib::Headers{
                {"Content-Encoding", "gzip"},
                {"Accept", "application/json"}
                                        }
*/
        // Process each request here
        httplib::Client cli(pak.target_host, pak.target_port);
        auto postRes =
            cli.Post(pak.path.empty() ? "/" : pak.path, pak.headers,
                     pak.body.data(), pak.body.size(), "application/json");
        if (postRes) {
          if (postRes->status != 200) {
            std::cerr << "Error: " << postRes->status << std::endl;
          }
        } else {
          std::cerr << "Error: Failed to send request" << std::endl;
        }
      }
    } while (0);
    lck.unlock();
    if (!open_.load())
      break;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  } while (1);
}
/////////////////////////////////////////////////////////////////////
Client *__gpsClient = nullptr;
Client *Client::CreateOrGet() {
  if (!__gpsClient)
    __gpsClient = new Client();
  return __gpsClient;
}
void Client::Destroy() {
  if (__gpsClient) {
    delete __gpsClient;
    __gpsClient = nullptr;
  }
}