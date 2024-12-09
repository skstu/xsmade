#include "MediaStreamComm.h"

ServerUdp::ServerUdp() {
  Init();
}
ServerUdp::~ServerUdp() {
  UnInit();
}
void ServerUdp::Release() const {
  delete this;
}
void ServerUdp::Init() {
}
void ServerUdp::UnInit() {
}
bool ServerUdp::Start() {
  return open_.load();
}
void ServerUdp::Stop() {
}