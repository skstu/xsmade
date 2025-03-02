#include "MediaStreamComm.h"

ServerHttp::ServerHttp() {
  Init();
}
ServerHttp::~ServerHttp() {
  UnInit();
}
void ServerHttp::Release() const {
  delete this;
}
void ServerHttp::Init() {
}
void ServerHttp::UnInit() {
}
bool ServerHttp::Start() {
  return open_.load();
}
void ServerHttp::Stop() {
}