#include "stl.hpp"
using namespace stl;
using namespace std;
namespace fs = filesystem;
std::u16string Path::Mormalize(const std::u16string &PathOrPathname) {
  std::u16string result{PathOrPathname};
  if (result.empty())
    return result;
  for (auto it = result.begin(); it != result.end();) {
    if (*it == u'\\') {
      *it = u'/';
    } else if (*it == 0) {
      it = result.erase(it);
      continue;
    }
    ++it;
  }
  do {
    auto found = result.find(u"//");
    if (found == std::u16string::npos)
      break;
    result.replace(found, std::u16string(u"//").size(), u"/");
  } while (1);
  return result;
}
std::string Path::Mormalize(const std::string &PathOrPathname) {
  std::string result{PathOrPathname};
  if (result.empty())
    return result;
  for (auto it = result.begin(); it != result.end();) {
    if (*it == '\\') {
      *it = '/';
    } else if (*it == 0) {
      it = result.erase(it);
      continue;
    }
    ++it;
  }
  do {
    auto found = result.find("\\\\");
    if (found == std::string::npos) {
      found = result.find("//");
      if (found == std::string::npos)
        break;
    }
    result.replace(found, 2, "/");
  } while (1);
  return result;
}
std::u16string Path::U8PathToU16Path(const std::string &input_path) {
  std::u16string result;
  try {
    fs::path path(input_path);
    result = path.generic_u16string();
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
std::string Path::U16PathToU8Path(const std::u16string &input_path) {
  std::string result;
  try {
    result = fs::path(input_path).generic_string();
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
std::wstring Path::U16PathToWPath(const std::u16string &input_path) {
  std::wstring result;
  try {
    result = fs::path(input_path).generic_wstring();
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
std::u16string Path::WPathToU16Path(const std::wstring &input_path) {
  std::u16string result;
  try {
    result = fs::path(input_path).generic_u16string();
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
string Path::Parent(const string &path) {
  string result;
  try {
#ifdef _STL_HAS_CXX17
    do {
      if (path.empty())
        break;
      fs::path fullPath(path);
      fs::path parentPath = fullPath.parent_path();
      result = parentPath.string();
    } while (0);
#endif
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
u16string Path::Parent(const u16string &path) {
  u16string result;
  try {
#ifdef _STL_HAS_CXX17
    do {
      if (path.empty())
        break;
      fs::path fullPath(path);
      fs::path parentPath = fullPath.parent_path();
      result = parentPath.u16string();
    } while (0);
#endif
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
wstring Path::Parent(const wstring &path) {
  wstring result;
  try {
#ifdef _STL_HAS_CXX17
    do {
      if (path.empty())
        break;
      fs::path fullPath(path);
      fs::path parentPath = fullPath.parent_path();
      result = parentPath.wstring();
    } while (0);
#endif
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
string Path::AppendU8(const string &abs, const string &rel) {
  string result;
  do {
    if (rel.empty())
      break;
    string tmp = abs + "/" + rel;
    fs::path path = tmp;
    result = path.lexically_normal().string();
  } while (0);
  return result;
}
wstring Path::AppendW(const wstring &abs, const wstring &rel) {
  wstring result;
  do {
    if (rel.empty())
      break;
    wstring tmp = abs + L"/" + rel;
    fs::path path = tmp;
    result = path.lexically_normal().wstring();
  } while (0);
  return result;
}
string Path::PathnameToPath(const string &input_pathname) {
  string result;
  do {
    if (IsDirectoryPath(input_pathname)) {
      result = input_pathname;
    } else if (IsFilePath(input_pathname)) {
      result = Parent(input_pathname);
    } else
      break;
  } while (0);
  return result;
}
wstring Path::PathnameToPath(const wstring &input_pathname) {
  wstring result;
  do {
    if (IsDirectoryPath(input_pathname)) {
      result = input_pathname;
    } else if (IsFilePath(input_pathname)) {
      result = Parent(input_pathname);
    } else
      break;
  } while (0);
  return result;
}
std::u16string Path::PathnameToPath(const std::u16string &input_pathname) {
  u16string result;
  do {
    if (IsDirectoryPath(input_pathname)) {
      result = input_pathname;
    } else if (IsFilePath(input_pathname)) {
      result = Parent(input_pathname);
    } else
      break;
  } while (0);
  return result;
}
bool Path::IsDirectoryPath(const std::string &input_path) {
  bool result = false;
  try {
    do {
      if (!std::filesystem::exists(input_path))
        break;
      if (std::filesystem::is_regular_file(input_path))
        break;
      if (!std::filesystem::is_directory(input_path))
        break;
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return result;
}
bool Path::IsDirectoryPath(const std::wstring &input_path) {
  bool result = false;
  try {
    do {
      if (!std::filesystem::exists(input_path))
        break;
      if (std::filesystem::is_regular_file(input_path))
        break;
      if (!std::filesystem::is_directory(input_path))
        break;
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return result;
}
bool Path::IsDirectoryPath(const std::u16string &input_path) {
  bool result = false;
  try {
    do {
      if (!std::filesystem::exists(input_path))
        break;
      if (std::filesystem::is_regular_file(input_path))
        break;
      if (!std::filesystem::is_directory(input_path))
        break;
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return result;
}
bool Path::IsFilePath(const std::string &input_path) {
  bool result = false;
  try {
    do {
      if (!std::filesystem::exists(input_path))
        break;
      if (!std::filesystem::is_regular_file(input_path))
        break;
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return result;
}
bool Path::IsFilePath(const std::wstring &input_path) {
  bool result = false;
  try {
    do {
      if (!std::filesystem::exists(input_path))
        break;
      if (!std::filesystem::is_regular_file(input_path))
        break;
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return result;
}
bool Path::IsFilePath(const std::u16string &input_path) {
  bool result = false;
  try {
    do {
      if (!std::filesystem::exists(input_path))
        break;
      if (!std::filesystem::is_regular_file(input_path))
        break;
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return result;
}
string Path::NormalU8(const string &path) {
  string result;
  do {
    if (path.empty())
      break;
#ifdef _STL_HAS_CXX17
    fs::path _path = path;
    result = _path.lexically_normal().string();
#endif
  } while (0);
  return result;
}
u16string Path::NormalU16(const u16string &path) {
  u16string result;
  do {
    if (path.empty())
      break;
#ifdef _STL_HAS_CXX17
    fs::path _path = path;
    result = _path.lexically_normal().u16string();
#endif
  } while (0);
  return result;
}
wstring Path::NormalW(const wstring &path) {
  wstring result;
  do {
    if (path.empty())
      break;
#ifdef _STL_HAS_CXX17
    fs::path _path = path;
    result = _path.lexically_normal().wstring();
#endif
  } while (0);
  return result;
}
// std::string parent_path, filename,  extension,  stem
bool Path::ParsePathname(const std::string &pathname, std::string &parent_path,
                         std::string &filename, std::string &extension,
                         std::string &stem) {
  bool result = false;
  do {
#ifdef _STL_HAS_CXX17
    if (pathname.empty())
      break;
    if (!File::Exists(pathname))
      break;
    const std::filesystem::path pathname_ = pathname;
    std::filesystem::path filename_ = pathname_.filename();
    std::filesystem::path stem_ = pathname_.stem();
    std::filesystem::path extension_ = pathname_.extension();
    std::filesystem::path parent_path_ = pathname_.parent_path();

    if (!filename_.empty()) {
      filename = filename_.string();
    }
    if (!stem_.empty()) {
      stem = stem_.string();
    }
    if (!extension_.empty()) {
      extension = extension_.string();
    }
    if (!parent_path_.empty()) {
      parent_path = parent_path_.string();
    }
    result = true;
#endif
  } while (0);
  return result;
}