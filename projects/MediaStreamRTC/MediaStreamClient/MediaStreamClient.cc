#include "MediaStreamClient.h"

MediaStreamClient::MediaStreamClient() {
}
MediaStreamClient::~MediaStreamClient() {
}
bool MediaStreamClient::Start() {
  do {
    if (open_.load())
      break;

    IClient *tcp = new ClientTcp();
    if (!tcp)
      break;
    if (tcp->Start()) {
      clients_.emplace_back(tcp);
    } else {
      tcp->Stop();
      tcp->Release();
    }

    open_.store(true);
  } while (0);
  return open_.load();
}
void MediaStreamClient::Stop() {
  for (auto &s : clients_) {
    s->Stop();
    s->Release();
  }
  clients_.clear();
}
//////////////////////////////////////////////////////////////
static MediaStreamClient *__gpMediaStreamClient = nullptr;
MediaStreamClient *MediaStreamClient::Create() {
  if (!__gpMediaStreamClient)
    __gpMediaStreamClient = new MediaStreamClient();
  return __gpMediaStreamClient;
}
void MediaStreamClient::Destroy() {
  if (__gpMediaStreamClient)
    __gpMediaStreamClient->Stop();
  SK_DELETE_PTR(__gpMediaStreamClient);
}