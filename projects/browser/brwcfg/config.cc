#include "brwcfg.h"
/////////////////////////////////////////////////////////////////
Config::Config() {
  Init();
}
Config::~Config() {
  UnInit();
}
void Config::Init() {
  xs_buffer_t *dllpath = nullptr;
  do {
    static int static_dummy_variable;
    xs_sys_get_dll_path(&dllpath, &static_dummy_variable);
    if (!dllpath)
      break;
    std::string u8Dllpath(dllpath->buffer, dllpath->len);
    configure_pathname_ = Conv::u8_to_u16(u8Dllpath);
    root_ = stl::Path::Parent(stl::Path::PathnameToPath(configure_pathname_));

    const std::u16string format = u".json";
    configure_pathname_.replace(configure_pathname_.find(u".dll"),
                                format.size(), format);
    chromium_cache_root_ = root_ + u"/cache";

  } while (0);
  xs_sys_free_buffer(&dllpath);
}
void Config::UnInit() {
}
const std::u16string &Config::GetRoot() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return root_;
}
const std::u16string &Config::GetConfigurePathname() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return configure_pathname_;
}
const std::u16string &Config::GetChromiumCacheRoot() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return chromium_cache_root_;
}
std::u16string
Config::GetChromiumCachePath(const unsigned long long &policy_id) const {
  std::lock_guard<std::mutex> lock(*mtx_);
  std::u16string result;
  do {
    if (chromium_cache_root_.empty())
      break;
    std::string hexPolicyIdString = fmt::format("{:x}", policy_id);
    result =
        chromium_cache_root_ + u"/" +
        ((!policy_id) ? (u"default") : (Conv::u8_to_u16(hexPolicyIdString)));
  } while (0);
  return result;
}
