#if !defined(__9A251ADD_7C16_48FD_8E24_652C6BF9CD17__)
#define __9A251ADD_7C16_48FD_8E24_652C6BF9CD17__

enum class FFXStreamServerType : unsigned short {
  TCP = 0x00,
  UPD = 0x10,
  LOOP = 0x20,
};

enum class ComponentType : unsigned long long {
  FFX_SCREEN_RECORDING = 0x101000,
  FFX_RTSP_SERVER = 0x102000,
  FFX_RTSP_SERVER_TCP =
      FFX_RTSP_SERVER | (unsigned long long)FFXStreamServerType::TCP,
  FFX_RTSP_SERVER_UDP =
      FFX_RTSP_SERVER | (unsigned long long)FFXStreamServerType::UPD,
  FFX_RTSP_SERVER_LOOP =
      FFX_RTSP_SERVER | (unsigned long long)FFXStreamServerType::LOOP,
};

/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 22 Nov 2024 12:32:11 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__9A251ADD_7C16_48FD_8E24_652C6BF9CD17__