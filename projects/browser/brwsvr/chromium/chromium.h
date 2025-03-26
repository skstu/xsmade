#if !defined(__8BD8E130_6DF0_4CEC_8BF2_357BE4569AD2__)
#define __8BD8E130_6DF0_4CEC_8BF2_357BE4569AD2__

class IChromiumProcess {
public:
  IChromiumProcess(const ChromiumProcessType &);
  ~IChromiumProcess();
  virtual void Release() const = 0;

protected:
  const ChromiumProcessType process_type_;
};

class ChromiumMain final : public IChromiumProcess {
public:
  ChromiumMain();
  virtual ~ChromiumMain();
  void Release() const override final;
};
class ChromiumGpu final : public IChromiumProcess {
public:
  ChromiumGpu();
  virtual ~ChromiumGpu();
  void Release() const override final;
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
  IChromium(const browser_id_t &brwid);
  void Release() const;

public:
  bool Open();
  void Close();
  const browser_id_t &GetBrowserId() const;

private:
  ~IChromium();
  const browser_id_t browser_id_;

private:
  std::atomic_bool open_ = false;
  xs_process_id_t main_pid_ = 0;
  std::map<xs_process_id_t, IChromiumProcess *> processes_;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 17 Mar 2025 01:59:39 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8BD8E130_6DF0_4CEC_8BF2_357BE4569AD2__