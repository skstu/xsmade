#include "perform.h"

PerformCmdLine::PerformCmdLine(const std::string &input_cmdline)
    : stl::CmdLine(input_cmdline) {
  Init();
}
PerformCmdLine::~PerformCmdLine() {
  UnInit();
}
void PerformCmdLine::Release() const {
  delete this;
}
void PerformCmdLine::Init() {
  std::string key_type = GetValue("type");
  if (stl::Common::strIcmp(key_type, "service")) {
    type_ = PerformProcessType::IBROWSER;
  } else if (stl::Common::strIcmp(key_type, "download")) {
    type_ = PerformProcessType::DOWNLOAD;
  } else if (stl::Common::strIcmp(key_type, "streampp")) {
    type_ = PerformProcessType::STREAMPP;
  }
  url_ = GetValue("url");
  ofile_ = GetValue("ofile");
  ifile_ = GetValue("ifile");
}
void PerformCmdLine::UnInit() {
}
const PerformProcessType &PerformCmdLine::ProcessType() const {
  return type_;
}
//////////////////////////////////////////////////////////////////////////
static PerformCmdLine *__gpPerformCmdLine = nullptr;
PerformCmdLine *PerformCmdLine::Get() {
  return __gpPerformCmdLine;
}
PerformCmdLine *PerformCmdLine::Create(const std::string &cmdline) {
  if (!__gpPerformCmdLine)
    __gpPerformCmdLine = new PerformCmdLine(cmdline);
  return __gpPerformCmdLine;
}
void PerformCmdLine::Destroy() {
  SK_DELETE_PTR(__gpPerformCmdLine);
}