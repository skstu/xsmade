#if !defined(__980867EE_F1DC_4FB6_91FE_C9001D8BBEDD__)
#define __980867EE_F1DC_4FB6_91FE_C9001D8BBEDD__
#include <string>
#include <map>
namespace chromium {
using tfRouteIndex = unsigned long;
using tfRoutePak = std::string;
using tfRouteRes = std::map<tfRouteIndex, tfRoutePak>;
#pragma pack(push, 1)
typedef struct tagROUTEDATA {
  unsigned long data_identify;
  unsigned long data_postion;
  unsigned long data_size;
} ROUTEDATA, *PROUTEDATA;

typedef struct tagROUTEDATAHEAD {
  unsigned long flag_head;
  unsigned long data_count;
  unsigned long data_size;
  unsigned long flag_tail;
} ROUTEDATAHEAD, *PROUTEDATAHEAD;
#pragma pack(pop)
constexpr unsigned long routedata_flag_head = 0xFEFF;
constexpr unsigned long routedata_flag_tail = 0x200B;
constexpr unsigned long routedata_head_size = sizeof(tagROUTEDATAHEAD);
constexpr unsigned long routedata_data_size = sizeof(tagROUTEDATA);
class Packet final {
public:
  inline Packet();
  inline ~Packet();
  inline void *operator new(size_t) = delete;
  inline void operator delete(void *) = delete;
  inline Packet(const Packet &) = delete;
  inline Packet &operator=(const Packet &) = delete;

private:
  inline void init_route_data(tagROUTEDATA &) const;
  inline void init_route_data_head(tagROUTEDATAHEAD &) const;
  inline bool verify_route_data_head(const tagROUTEDATAHEAD &head) const;

public:
  inline bool unmade(const tfRoutePak &route_data, tfRouteRes &outpak) const;
  inline bool made(const tfRouteRes &ress, tfRoutePak &outres) const;
};
inline Packet::Packet() {
}
inline Packet::~Packet() {
}
inline bool Packet::verify_route_data_head(const tagROUTEDATAHEAD &head) const {
  return head.flag_head == routedata_flag_head &&
         head.flag_tail == routedata_flag_tail;
}
inline void Packet::init_route_data(tagROUTEDATA &data) const {
  data.data_identify = 0;
  data.data_postion = 0;
  data.data_size = 0;
}
inline void Packet::init_route_data_head(tagROUTEDATAHEAD &head) const {
  head.flag_head = routedata_flag_head;
  head.data_count = 0;
  head.data_size = 0;
  head.flag_tail = routedata_flag_tail;
}

inline bool Packet::made(const tfRouteRes &ress, tfRoutePak &outres) const {
  bool result = false;
  outres.clear();
  do {
    if (ress.empty()) {
      break;
    }
    ROUTEDATAHEAD head;
    init_route_data_head(head);
    head.data_count = static_cast<decltype(head.data_count)>(ress.size());
    outres.append((char *)&head, sizeof(head));

    std::for_each(ress.begin(), ress.end(), [&](const auto &node) {
      ROUTEDATA dataInfo = {0};
      init_route_data(dataInfo);
      dataInfo.data_identify = node.first;
      dataInfo.data_size =
          static_cast<decltype(dataInfo.data_size)>(node.second.size());
      dataInfo.data_postion =
          static_cast<decltype(dataInfo.data_postion)>(outres.size());
      outres.append((char *)&dataInfo, sizeof(dataInfo));
      if (dataInfo.data_size > 0) {
        outres.append(node.second);
      }
      ((PROUTEDATAHEAD)outres.data())->data_size += dataInfo.data_size;
    });
    result = !outres.empty();
  } while (0);
  return result;
}
inline bool Packet::unmade(const tfRoutePak &route_data,
                           tfRouteRes &outpak) const {
  bool result = false;
  outpak.clear();
  do {
    if (route_data.empty())
      break;
    PROUTEDATAHEAD pHead = (PROUTEDATAHEAD)(route_data.data());
    if (!verify_route_data_head(*pHead))
      break;
    unsigned long info_pos = routedata_head_size;
    for (decltype(pHead->data_count) i = 0; i < pHead->data_count; ++i) {
      PROUTEDATA pInfo = (PROUTEDATA)(&route_data[info_pos]);
      info_pos += sizeof(ROUTEDATA);
      outpak.emplace(pInfo->data_identify,
                     std::string(&route_data[info_pos], pInfo->data_size));
      info_pos += pInfo->data_size;
    }
    result = !outpak.empty();
  } while (0);
  return result;
}

} // namespace chromium

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 20 Jun 2025 01:08:51 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__980867EE_F1DC_4FB6_91FE_C9001D8BBEDD__
