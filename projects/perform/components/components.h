#if !defined(__CB283E66_51BC_4C80_BACC_61FC238DD035__)
#define __CB283E66_51BC_4C80_BACC_61FC238DD035__

namespace local {
class IComponent {
public:
  virtual bool Start(const std::vector<std::string> &cmdline,
                     const bool &show) = 0;
  virtual void Stop() = 0;
  virtual void Release() const = 0;

public:
  void operator=(const IComponent &obj) {
    main = obj.main;
    identify = obj.identify;
  }
  bool operator<(const IComponent &obj) {
    bool result = false;
    do {
      if (main.compare(obj.main) >= 0)
        break;
      if (identify.compare(obj.identify) >= 0)
        break;
      result = true;
    } while (0);
    return result;
  }

public:
  std::u16string main;
  std::u16string identify;
  bool enable = false;
  xs_process_id_t pid_ = 0;
};

class Components {
public:
  static Components *Get();
  static void Destroy();

public:
  local::IComponent *GetComp(const std::u16string &) const;
  bool ffxRecordStart(const wxui::IRecordingArgs *);
  void ffxRecordStop();

private:
  Components();
  ~Components();

public:
  bool CreateComponent(const std::string &identify, const ComponentType &ctype,
                       const std::vector<std::string> &startup_args,
                       const bool &show);
  void DestroyComponent(const std::string &identify, const ComponentType &type);

private:
  void Init();
  void UnInit();

private:
  const std::u16string root_dir_name_ = u"components";
  std::map<std::u16string, IComponent *> comps_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
} // namespace local

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 22 Nov 2024 03:38:06 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__CB283E66_51BC_4C80_BACC_61FC238DD035__