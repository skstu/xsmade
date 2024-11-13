#include "sys.h"

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