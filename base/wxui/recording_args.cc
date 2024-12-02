#include "wxui.h"
RecordingArgs::RecordingArgs() {
}
RecordingArgs::~RecordingArgs() {
}
void RecordingArgs::Release() const {
  delete this;
}
void RecordingArgs::SetPos(const int &x, const int &y, const int &cx,
                           const int &cy) {
  x_ = x;
  y_ = y;
  cx_ = cx;
  cy_ = cy;
}
int RecordingArgs::GetX() const {
  return x_;
}
int RecordingArgs::GetY() const {
  return y_;
}
int RecordingArgs::GetCX() const {
  return cx_;
}
int RecordingArgs::GetCY() const {
  return cy_;
}
#if 0
namespace ffx {
FFXArgs::FFXArgs(const tfFFXArgs &args) : args_(args) {
}

FFXArgs::~FFXArgs() {
}
void FFXArgs::Push(const std::string &key, const std::string &value) {
  do {
    std::string inster_value(value);
    if (!key.compare("-xs-outfile")) {
      inster_value = stl::Path::Mormalize(System::GetCurrentProcessPath() +
                                          "/" + inster_value);
    }
    bool found = false;
    for (auto &arg : args_) {
      if (arg.second.first.compare(key) == 0) {
        arg.second.second = inster_value;
        found = true;
        break;
      }
    }
    if (found)
      break;
    args_.emplace(args_.size(), tfArgs{key, inster_value});
  } while (0);
}
Args *FFXArgs::GetArgs() const {
  Args *result = new Args();
  for (const auto &arg : args_) {
    std::string node;
    if (arg.second.first.find("-xs-") == std::string::npos &&
        !arg.second.first.empty()) {
      node.append(arg.second.first).append(1, 0x20);
    }
    if (!arg.second.second.empty())
      node.append(arg.second.second).append(1, 0x20);
    result->Push(node);
  }
  result->PushEnd();
  return result;
}
//////////////////////////////////////////////////////////
Args::Args() {
}
Args::~Args() {
}
void Args::Release() const {
  for (auto &s : source_)
    free((void *)s);
  delete this;
}
void Args::Push(const std::string &input) {
  if (!input.empty()) {
    char *m = (char *)malloc(input.size() + 1);
    memcpy(m, input.data(), input.size());
    m[input.size()] = 0;
    source_.push_back(m);
  }
}
void Args::PushEnd() {
  source_.push_back(nullptr);
}
std::vector<const char *> Args::GetSource() const {
  return source_;
}
} // namespace ffx
#endif