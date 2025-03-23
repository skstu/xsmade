#if !defined(__B7672112_2269_4E6C_93A3_24D2CFA41FDD__)
#define __B7672112_2269_4E6C_93A3_24D2CFA41FDD__

class Args final : public IBrwcfg::IArgs {
public:
  Args();
  Args(const std::string &u8key);
  Args(const std::string &u8key, const std::string &u8value,
       const bool &ispath = false);
  virtual ~Args();

public:
  void Release() const override final;

protected:
  IBrwcfg::IBuffer *GetKey() const override final;
  IBrwcfg::IBuffer *GetValue() const override final;
  bool IsPath() const override final;

private:
  Buffer *key_ = nullptr;
  Buffer *value_ = nullptr;
  bool ispath_ = false;
};

class ArgsArray final : public IBrwcfg::IArgsArray {
public:
  ArgsArray();

private:
  virtual ~ArgsArray();

protected:
  size_t Total() const override final;
  IBrwcfg::IArgs *Next(const size_t &) const override final;
  void Release() const override final;

public:
  void Push(Args *);

private:
  std::vector<Args *> source_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 19 Feb 2025 10:01:46 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__B7672112_2269_4E6C_93A3_24D2CFA41FDD__