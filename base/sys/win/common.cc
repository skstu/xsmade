#include "sys.h"

XS_EXTERN int xs_sys_get_appdata_path(char **path, size_t *path_len) {
  int r = -1;
  std::string result;
  LPITEMIDLIST ppidl = nullptr;
  do {
    if (::SHGetSpecialFolderLocation(nullptr, CSIDL_APPDATA, &ppidl) != S_OK)
      break;
    char pszPath[_MAX_PATH] = {0};
    if (!::SHGetPathFromIDListA(ppidl, pszPath))
      break;
    result = pszPath;
    if (result.empty())
      break;
    auto end = std::prev(result.end());
    if (*end != '\\' && *end != '/')
      result.append("\\");
    *path = (char *)malloc(result.size());
    *path_len = result.size();
    memcpy(*path, result.data(), result.size());
    r = 0;
  } while (0);
  if (ppidl) {
    ::CoTaskMemFree(ppidl);
    ppidl = nullptr;
  }
  return r;
}