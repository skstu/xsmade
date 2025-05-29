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

  void worker() {
    int task_id = 0;
    while (true) {
      std::string url;
      {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        queue_cv_.wait(lock, [this] { return stop_ || !urls_.empty(); });
        if (stop_ && urls_.empty())
          return;
        url = urls_.front();
        urls_.pop();
        ++active_tasks_;
      }

      std::string response;
      CURL *curl = curl_easy_init();
      if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        if (follow_redirects_) {
          curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        }

        if (!user_agent_.empty()) {
          curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent_.c_str());
        }

        if (!referer_.empty()) {
          curl_easy_setopt(curl, CURLOPT_REFERER, referer_.c_str());
        }

        if (!cookie_file_.empty()) {
          curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookie_file_.c_str());
          curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie_file_.c_str());
        }

        struct curl_slist *header_list = nullptr;
        {
          std::lock_guard<std::mutex> lock(header_mutex_);
          for (const auto &h : extra_headers_) {
            header_list = curl_slist_append(header_list, h.c_str());
          }
        }
        if (header_list) {
          curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
        }

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
          std::string filename =
              output_dir_ + "/page_" + std::to_string(task_id++) + ".html";
          std::ofstream fout(filename);
          fout << response;
          fout.close();
          std::cout << "Saved: " << filename << "\n";
        } else {
          std::cerr << "Error fetching " << url << ": "
                    << curl_easy_strerror(res) << "\n";
        }

        if (header_list)
          curl_slist_free_all(header_list);
        curl_easy_cleanup(curl);
      }

      {
        std::lock_guard<std::mutex> lock(done_mutex_);
        --active_tasks_;
      }
      done_cv_.notify_one();
    }
  }
};

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 20 May 2025 01:34:44 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__C81794DB_B1A3_4BC6_B2B9_8AC3C589291E__