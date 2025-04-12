#if !defined(__8BD8E130_6DF0_4CEC_8BF2_357BE4569AD2__)
#define __8BD8E130_6DF0_4CEC_8BF2_357BE4569AD2__

class IChromiumProcess {
public:
  IChromiumProcess(const ChromiumProcessType &, const xs_process_id_t &);
  ~IChromiumProcess();
  virtual void Release() const = 0;
  virtual bool Request(const command_type_t &, const std::string &) const = 0;

public:
  const xs_process_id_t &GetProcessId() const;
#if ENABLE_UVPP
  void SetSession(const uvpp::ISession *);
#endif
protected:
#if ENABLE_UVPP
  uvpp::ISession *session_ = nullptr;
#endif
  const ChromiumProcessType process_type_;
  const xs_process_id_t process_id_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};

class ChromiumMain final : public IChromiumProcess {
public:
  ChromiumMain(const xs_process_id_t &);
  virtual ~ChromiumMain();
  void Release() const override final;

protected:
  bool Request(const command_type_t &,
               const std::string &) const override final;
};
class ChromiumGpu final : public IChromiumProcess {
public:
  ChromiumGpu(const xs_process_id_t &);
  virtual ~ChromiumGpu();
  void Release() const override final;

protected:
  bool Request(const command_type_t &,
               const std::string &) const override final;
};

class Brwobj final {
public:
  Brwobj(const browser_id_t &);

public:
  void Release() const;
  bool Open();
  void Close();
  const unsigned long &GetPid(void) const;
  const browser_id_t &GetId() const;

private:
  ~Brwobj();

private:
  const browser_id_t brwid_;
  unsigned long pid_ = 0;
  std::atomic_bool open_ = false;
};

class IChromium {
public:
  IChromium(const std::string& cfg);
  void Release() const;

public:
  bool Open();
  void Close();
  const browser_id_t &GetBrowserId() const;
  IChromiumProcess *GetProcess(const ChromiumProcessType &) const;
  bool ProcessReady(const ChromiumProcessType &, const xs_process_id_t &,
                    const uvpp::ISession *);
  bool Request(const command_type_t &, const std::string &, mp_errno_t &) const;

private:
  ~IChromium();
  const brwcfg::IConfigure brwcfg_;

private:
  std::atomic_bool open_ = false;
  xs_process_id_t main_pid_ = 0;
  stl::container::map<ChromiumProcessType, IChromiumProcess *> processes_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 17 Mar 2025 01:59:39 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8BD8E130_6DF0_4CEC_8BF2_357BE4569AD2__