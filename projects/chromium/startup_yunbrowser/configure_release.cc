#include "config.h"

void Startup::ConfigureRelease() {
  do {
    if (!Config::CreateOrGet()->DevelopMode())
      break;
    // 生成随机用户名
    std::string chromium_proxy_string, curl_proxy_string;
    GenerateDynamicProxyInfo(chromium_proxy_string, curl_proxy_string);
    LOG_INFO("Proxy: {}", chromium_proxy_string);

    // 设置代理字符串
    // Config::CreateOrGet()->settings_->SetProxyString(
    //     "socks5h://1Ap7HA38151774A39724:EAE0W4S0QLE1@");
  } while (0);
}