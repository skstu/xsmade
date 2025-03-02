#if !defined(__99F57EC7_2FFB_46C2_995B_CE6744B8B79E__)
#define __99F57EC7_2FFB_46C2_995B_CE6744B8B79E__

class DataArray final : public IBrwcfg::IDataArray {
public:
  DataArray();

private:
  virtual ~DataArray();

protected:
  void Push(IBrwcfg::IData *) override final;
  IBrwcfg::IData *CreateData(const char *, const size_t &) override final;
  IBrwcfg::IData *Next(const size_t &) const override final;
  size_t Total() const override final;
  void Release() const override final;

private:
  std::vector<Data *> source_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 07 Jan 2025 07:28:07 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__99F57EC7_2FFB_46C2_995B_CE6744B8B79E__