#include "MediaStreamServer.h"

MediaStreamServer::MediaStreamServer() {
}
MediaStreamServer::~MediaStreamServer() {
}
bool MediaStreamServer::Start() {
  do {
    if (open_.load())
      break;

    IServer *tcp = new ServerTcp();
    if (!tcp)
      break;
    if (tcp->Start()) {
      servers_.emplace_back(tcp);
    } else {
      tcp->Stop();
      tcp->Release();
    }

    open_.store(true);
  } while (0);
  return open_.load();
}
void MediaStreamServer::Stop() {
  for (auto &s : servers_) {
    s->Stop();
    s->Release();
  }
  servers_.clear();
}
//////////////////////////////////////////////////////////////
static MediaStreamServer *__gpMediaStreamServer = nullptr;
MediaStreamServer *MediaStreamServer::Create() {
  if (!__gpMediaStreamServer)
    __gpMediaStreamServer = new MediaStreamServer();
  return __gpMediaStreamServer;
}
void MediaStreamServer::Destroy() {
  if (__gpMediaStreamServer)
    __gpMediaStreamServer->Stop();
  SK_DELETE_PTR(__gpMediaStreamServer);
}