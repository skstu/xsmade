#if !defined(__823CB97A_F25F_4048_B62B_3359130FA69A__)
#define __823CB97A_F25F_4048_B62B_3359130FA69A__

class PerformCmdLine final : public stl::CmdLine {
public:
  static PerformCmdLine *Create(const std::string &);
  static void Destroy();
  static PerformCmdLine *Get();

private:
  PerformCmdLine(const std::string &input_cmdline);
  virtual ~PerformCmdLine();
  void Release() const override final;

private:
  void Init();
  void UnInit();

public:
  const PerformProcessType &ProcessType() const;

private:
  PerformProcessType type_ = PerformProcessType::DEFAULT;
  std::string url_;
  std::string ofile_;
  std::string ifile_;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Wed, 04 Dec 2024 03:25:33 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__823CB97A_F25F_4048_B62B_3359130FA69A__