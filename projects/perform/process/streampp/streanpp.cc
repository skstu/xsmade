#include "perform.h"

IStreamPP::IStreamPP() {
  Init();
}
IStreamPP::~IStreamPP() {
  UnInit();
}
void IStreamPP::Release() const {
  delete this;
}
void IStreamPP::Init() {
}
void IStreamPP::UnInit() {
}
bool IStreamPP::Start() {
  return false;
}
void IStreamPP::Stop() {
}
IConfig *IStreamPP::ConfigGet() const {
  return nullptr;
}