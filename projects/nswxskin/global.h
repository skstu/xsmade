#if !defined(__2902EB13_3635_4F0C_9CE0_33FD551643AB__)
#define __2902EB13_3635_4F0C_9CE0_33FD551643AB__

enum class InstallerType : UINT {
  Install = 0,
  Uninstall = 1,
};

class Global {
public:
  static Global *Get();

public:
  stl::Signal *SignalGet() const;
  void SetExtra(extra_parameters *extra);
  extra_parameters *GetExtra() const;
  void LoadResource(const std::u16string &resPath);
  wxImage *GetResImage(const std::u16string &imgName) const;

private:
  Global();
  ~Global();
  void Init();
  void UnInit();

private:
  std::u16string resource_dir_;
  extra_parameters *extra_ = nullptr;
  std::map<std::u16string, wxImage *> imgres_;
  std::map<std::u16string, std::string> binres_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
  std::shared_ptr<stl::Signal> signal_ = std::make_shared<stl::Signal>();
};

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 03 Feb 2025 14:33:48 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__2902EB13_3635_4F0C_9CE0_33FD551643AB__