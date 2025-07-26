#if !defined(__C81794DB_B1A3_4BC6_B2B9_8AC3C589291E__)
#define __C81794DB_B1A3_4BC6_B2B9_8AC3C589291E__

class WebCrawler {
public:
  WebCrawler(size_t thread_count)
      : stop_(false), active_tasks_(0), follow_redirects_(false) {
    curl_global_init(CURL_GLOBAL_ALL);
    for (size_t i = 0; i < thread_count; ++i) {
      workers_.emplace_back(&WebCrawler::worker, this);
    }
  }

  ~WebCrawler() {
    shutdown();
    curl_global_cleanup();
  }

  void addUrl(const std::string &url) {
    {
      std::lock_guard<std::mutex> lock(queue_mutex_);
      urls_.push(url);
    }
    queue_cv_.notify_one();
  }
  void setSocks5Proxy(const std::string &proxy, const std::string &user = "",
                      const std::string &pwd = "") {
    std::lock_guard<std::mutex> lock(proxy_mutex_);
    socks5_proxy_ = proxy;
    socks5_user_ = user;
    socks5_pwd_ = pwd;
  }
  void waitUntilDone() {
    std::unique_lock<std::mutex> lock(done_mutex_);
    done_cv_.wait(lock, [this] {
      std::lock_guard<std::mutex> qlock(queue_mutex_);
      return urls_.empty() && active_tasks_ == 0;
    });
  }

  void shutdown() {
    {
      std::lock_guard<std::mutex> lock(queue_mutex_);
      stop_ = true;
    }
    queue_cv_.notify_all();
    for (auto &t : workers_) {
      if (t.joinable())
        t.join();
    }
  }

  // ---------------- 可配置参数设置 ----------------

  void setUserAgent(const std::string &ua) {
    user_agent_ = ua;
  }

  void setReferer(const std::string &referer) {
    referer_ = referer;
  }

  void addHeader(const std::string &header) {
    std::lock_guard<std::mutex> lock(header_mutex_);
    extra_headers_.push_back(header);
  }

  void setCookieFile(const std::string &path) {
    cookie_file_ = path;
  }

  void setFollowRedirects(bool follow) {
    follow_redirects_ = follow;
  }

  void setOutputDir(const std::string &path) {
    output_dir_ = path;
    std::filesystem::create_directories(output_dir_);
  }

private:
  std::string socks5_proxy_;
  std::string socks5_user_;
  std::string socks5_pwd_;
  std::mutex proxy_mutex_;

  std::vector<std::thread> workers_;
  std::queue<std::string> urls_;
  std::mutex queue_mutex_;
  std::condition_variable queue_cv_;
  std::atomic<int> active_tasks_;
  std::mutex done_mutex_;
  std::condition_variable done_cv_;
  bool stop_;

  // HTTP 配置项
  std::string user_agent_;
  std::string referer_;
  std::string cookie_file_;
  std::vector<std::string> extra_headers_;
  std::mutex header_mutex_;
  bool follow_redirects_;
  std::string output_dir_ = "./output";

  static size_t writeCallback(void *contents, size_t size, size_t nmemb,
                              void *userp) {
    std::string *out = static_cast<std::string *>(userp);
    out->append(static_cast<char *>(contents), size * nmemb);
    return size * nmemb;
  }

  void worker();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 20 May 2025 01:34:44 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__C81794DB_B1A3_4BC6_B2B9_8AC3C589291E__