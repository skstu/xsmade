#if !defined(__D911105A_3FCD_4391_A635_15971B7E1900__)
#define __D911105A_3FCD_4391_A635_15971B7E1900__

class Extension final : public IBrw::IExtension {
public:
  Extension(const Buffer *root, const Buffer *manifest,const bool& reload = false);
  virtual ~Extension();
  void Release() const override final;

protected:
  bool IsReload() const override final;
  const IBrw::IBuffer *Manifest() const override final;
  const IBrw::IBuffer *Root() const override final;

private:
  const Buffer *manifest_;
  const Buffer *root_;
  bool reload_ = false;
};

class ExtensionArray final : public IBrw::IExtensionArray {
public:
  ExtensionArray();

private:
  virtual ~ExtensionArray();

protected:
  size_t Total() const override final;
  IBrw::IExtension *Next(const size_t &) const override final;
  void Release() const override final;

public:
  void Push(Extension *);

private:
  std::vector<Extension *> source_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 19 Feb 2025 07:59:48 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__D911105A_3FCD_4391_A635_15971B7E1900__