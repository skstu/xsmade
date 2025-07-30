#if !defined(__DBF6427B_81A7_4A73_8F2F_DED725E368A4__)
#define __DBF6427B_81A7_4A73_8F2F_DED725E368A4__
class IModel {
public:
  struct Model {
    std::vector<chromium::xsiumio::IXSiumio::Fingerprint::Canvas> canvas;
    std::vector<chromium::xsiumio::IXSiumio::Fingerprint::Webgl> webgl;
    std::vector<chromium::xsiumio::IXSiumio::Fingerprint::Audio> audio;
    std::vector<chromium::xsiumio::IXSiumio::Fingerprint::Font> font;
    std::vector<int> cpu_cores;
    std::vector<int> device_memory;
  };

protected:
  IModel();
  virtual ~IModel();

public:
  virtual bool LoadModelParts();
  virtual bool Ready() const;
  virtual void Release() const = 0;
  virtual bool GenModel();
  virtual bool GetModel(chromium::xsiumio::IXSiumio &) const = 0;
  virtual const char *GetModelIdentify() const = 0;

protected:
  std::atomic_bool ready_ = false;
  Model model_;
  std::map<std::uint64_t, chromium::xsiumio::IXSiumio> xsiumios_;
  std::unique_ptr<std::mutex> mtx_ = std::make_unique<std::mutex>();
};
class ModelLevel0 final : public IModel {
public:
  ModelLevel0();
  ~ModelLevel0();
  void Release() const override final;

protected:
  bool GetModel(chromium::xsiumio::IXSiumio &) const override final;
  const char *GetModelIdentify() const override final;

private:
};
class ModelLevel1 final : public IModel {
public:
  ModelLevel1();
  ~ModelLevel1();
  void Release() const override final;

protected:
  bool GetModel(chromium::xsiumio::IXSiumio &) const override final;
  const char *GetModelIdentify() const override final;

private:
};
class ModelLevel2 final : public IModel {
public:
  ModelLevel2();
  ~ModelLevel2();
  void Release() const override final;

protected:
  bool GetModel(chromium::xsiumio::IXSiumio &) const override final;
  const char *GetModelIdentify() const override final;
};
class ModelLevel3 final : public IModel {
public:
  ModelLevel3();
  ~ModelLevel3();
  void Release() const override final;

protected:
  bool GetModel(chromium::xsiumio::IXSiumio &) const override final;
  const char *GetModelIdentify() const override final;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 26 Jul 2025 13:07:17 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__DBF6427B_81A7_4A73_8F2F_DED725E368A4__