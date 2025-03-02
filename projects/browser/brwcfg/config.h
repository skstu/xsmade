#if !defined(__CDA0FE42_5C23_4350_89DE_6EE9A7004DB7__)
#define __CDA0FE42_5C23_4350_89DE_6EE9A7004DB7__

class Config final {
public:
  Config();
  virtual ~Config();

private:
  void Init();
  void UnInit();

public:
  const std::u16string &GetRoot() const;
  const std::u16string &GetConfigurePathname() const;
  const std::u16string &GetChromiumCacheRoot() const;
  std::u16string
  GetChromiumCachePath(const unsigned long long &policy_id) const;

private:
  std::u16string root_;
  std::u16string configure_pathname_;
  std::u16string chromium_cache_root_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 22 Feb 2025 05:04:36 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__CDA0FE42_5C23_4350_89DE_6EE9A7004DB7__