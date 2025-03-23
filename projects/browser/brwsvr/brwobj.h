#if !defined(__8BD8E130_6DF0_4CEC_8BF2_357BE4569AD2__)
#define __8BD8E130_6DF0_4CEC_8BF2_357BE4569AD2__

class Brwobj final {
public:
  Brwobj(const browser_id_t &);

public:
  void Release() const;
  bool Open();
  void Close();
  const unsigned long &GetPid(void) const;
  const browser_id_t& GetId() const;

private:
  ~Brwobj();
private:
  const browser_id_t brwid_;
  unsigned long pid_ = 0;
  std::atomic_bool open_ = false;
};
/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 17 Mar 2025 01:59:39 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__8BD8E130_6DF0_4CEC_8BF2_357BE4569AD2__