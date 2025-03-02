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
