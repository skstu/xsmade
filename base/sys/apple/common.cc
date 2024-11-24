#include "sys.h"
XS_EXTERN void xs_sys_startup(void) {
}
XS_EXTERN void xs_sys_shutdown(void) {
}
XS_EXTERN int xs_sys_get_appdata_path(char **out, size_t *len) {
  int r = -1;
  const char *homeDir = std::getenv("HOME");
  do {
    if (!homeDir)
      break;
    std::string appSupportDir =
        std::string(homeDir) + "/Library/Application Support";
    *len = appSupportDir.size();
    *out = (char *)malloc(appSupportDir.size());
    memcpy(*out, appSupportDir.data(), appSupportDir.size());
    r = 0;
  } while (0);
  return r;
}

XS_EXTERN int xs_sys_capturescreen(xs_position_t pos,
                                   xs_image_stream_type_t type,
                                   xs_image_stream_t **stream) {
#if 0
 std::string result;
  std::vector<uint8_t> pngData;

  do {
    // 截取主显示器的屏幕内容
    CGImageRef screenshot = CGDisplayCreateImage(kCGDirectMainDisplay);
    if (!screenshot) {
      break;
    }
    // 创建一个内存流
    CFMutableDataRef imageData = CFDataCreateMutable(kCFAllocatorDefault, 0);
    CGImageDestinationRef destination =
        // CGImageDestinationCreateWithData(imageData, kUTTypePNG, 1, nullptr);
        CGImageDestinationCreateWithData(imageData, kUTTypeJPEG, 1, nullptr);
    if (!destination) {
      CGImageRelease(screenshot);
      CFRelease(imageData);
      break;
    }
    // 将截图图像写入内存流，保存为 PNG 格式
    CGImageDestinationAddImage(destination, screenshot, nullptr);
    CGImageDestinationFinalize(destination);
    // 将 CFData 内容复制到 std::vector
    CFIndex length = CFDataGetLength(imageData);
    pngData.resize((size_t)length);
    CFDataGetBytes(imageData, CFRangeMake(0, length), pngData.data());
    result.append((char *)&pngData[0], pngData.size() * sizeof(char));
    // 释放资源
    CFRelease(destination);
    CFRelease(imageData);
    CGImageRelease(screenshot);
  } while (0);
#endif
  return 0;
}