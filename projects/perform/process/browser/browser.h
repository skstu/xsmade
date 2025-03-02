#if !defined(__1C0784BE_0C5C_4709_85DD_998E36608AC3__)
#define __1C0784BE_0C5C_4709_85DD_998E36608AC3__

class Browser {
public:
  Browser(const std::string &cfg);
  ~Browser();
  void Release() const;

private:
  void Init();
  void UnInit();

public:
  bool Open();
  void Close();
  const xs_process_id_t &GetPid() const;
  const std::string &GetKey() const;

private:
  Configure *brwcfg_ = nullptr;
  std::atomic_bool open_ = false;
  std::atomic_bool ready_ = false;
  xs_process_id_t pid_ = 0;
  const std::string cfg_;
  std::u16string brw_module_pathname_;
  std::vector<std::string> brw_startup_args_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sat, 16 Nov 2024 10:48:07 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__1C0784BE_0C5C_4709_85DD_998E36608AC3__