#if !defined(__93D4C1C3_EE54_412F_B275_F96BA725525A__)
#define __93D4C1C3_EE54_412F_B275_F96BA725525A__

class Comps final {
public:
  enum class CompKey {
    kNull = 0x0,
    kCurl = 0x1,
    kIcu = 0x2,
    kBridge = 0x3,
    kMax,
  };

public:
  static Comps *CreateOrGet();
  static void Destroy();

public:
  void Release() const;
  bool Start();
  void Stop();
  bool Ready() const;
  template <typename T> T *GetComp(const CompKey &key) const {
    T *result = nullptr;
    std::lock_guard<std::mutex> lck(*mtx_);
    do {
      auto it = comps_.find(key);
      if (it == comps_.end())
        break;
      result = dynamic_cast<T *>(it->second);
    } while (0);
    return result;
  }

private:
  Comps();
  ~Comps();

private:
  void Init();
  void UnInit();

private:
  std::atomic_bool open_ = false;
  std::map<CompKey, IComponent *> comps_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 27 Aug 2025 03:09:29 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__93D4C1C3_EE54_412F_B275_F96BA725525A__