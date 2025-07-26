#include "config.h"

void WebCrawler::worker() {
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

      curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L); // 连接超时10秒
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);        // 总超时20秒

      // 设置 SOCKS5 代理
      {
        std::lock_guard<std::mutex> lock(proxy_mutex_);
        if (!socks5_proxy_.empty()) {
          // 只填 host:port，不要加协议前缀
          curl_easy_setopt(curl, CURLOPT_PROXY, socks5_proxy_.c_str());
          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
          // curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
          if (!socks5_user_.empty()) {
            curl_easy_setopt(curl, CURLOPT_PROXYUSERNAME, socks5_user_.c_str());
          }
          if (!socks5_pwd_.empty()) {
            curl_easy_setopt(curl, CURLOPT_PROXYPASSWORD, socks5_pwd_.c_str());
          }
        }
      }

      // ...existing code...
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
      switch (res) {
      case CURLE_OK: {
        const std::string &output_filename =
            Config::CreateOrGet()->GetCurlResponseFilename();
        std::string fname = output_filename;
        if (fname.empty()) {
          fname = ".curlcc.cache";
        }
        std::ofstream fout(fname);
        fout << response;
        fout.close();
      } break;
      case CURLE_OPERATION_TIMEDOUT: {

      } break;
      case CURLE_SSL_CONNECT_ERROR: {

      } break;
      default:
        break;
      }
      if (CURLE_OK != res) {
        std::cerr << "Error fetching " << url << ": " << curl_easy_strerror(res)
                  << "\n";
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