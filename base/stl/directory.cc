#include "stl.hpp"
using namespace stl;
using namespace std;
namespace fs = std::filesystem;
bool Directory::RemoveAllU8(const std::string &dir) {
  bool result = false;
  do {
    fs::path path = dir;
    if (!fs::is_directory(path))
      break;
    result = fs::remove_all(path);
  } while (0);
  return result;
}
bool Directory::RemoveAllU16(const std::u16string &dir) {
  bool result = false;
  do {
    fs::path path = dir;
    if (!fs::is_directory(path))
      break;
    result = fs::remove_all(path);
  } while (0);
  return result;
}
bool Directory::RemoveAllW(const std::wstring &dir) {
  bool result = false;
  do {
    fs::path path = dir;
    if (!fs::is_directory(path))
      break;
    result = fs::remove_all(path);
  } while (0);
  return result;
}
bool Directory::ExistsW(const std::wstring &input_path) {
  bool result = false;
#ifdef _STL_HAS_CXX17
  do {
    if (input_path.empty())
      break;
    if (!std::filesystem::exists(input_path))
      break;
    if (!std::filesystem::is_directory(input_path))
      break;
    result = true;
  } while (0);
#endif
  return result;
}
bool Directory::ExistsU8(const std::string &input_path) {
  bool result = false;
#ifdef _STL_HAS_CXX17
  do {
    if (input_path.empty())
      break;
    if (!std::filesystem::exists(input_path))
      break;
    if (!std::filesystem::is_directory(input_path))
      break;
    result = true;
  } while (0);
#endif
  return result;
}
bool Directory::ExistsU16(const std::u16string &input_path) {
  bool result = false;
#ifdef _STL_HAS_CXX17
  do {
    if (input_path.empty())
      break;
    if (!std::filesystem::exists(input_path))
      break;
    if (!std::filesystem::is_directory(input_path))
      break;
    result = true;
  } while (0);
#endif
  return result;
}
bool Directory::Create(const std::u16string &path) {
  bool result = false;
  do {
    if (path.empty())
      break;
    try {
#ifdef _STL_HAS_CXX17
      fs::path _path = path;
      if (fs::exists(_path)) {
        result = true;
        break;
      }
      result = fs::create_directories(_path.lexically_normal());
#endif
    } catch (const std::filesystem::filesystem_error &e) {
      result = false;
      std::cout << e.what() << std::endl;
    }
  } while (0);
  return result;
}
bool Directory::Create(const string &path) {
  bool result = false;
  try {
    do {
      if (path.empty())
        break;
#ifdef _STL_HAS_CXX17
      fs::path _path = path;
      if (fs::exists(_path)) {
        result = true;
        break;
      }
      result = fs::create_directories(_path.lexically_normal());
#endif
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool Directory::Create(const wstring &path) {
  bool result = false;
  try {
    do {
      if (path.empty())
        break;
#ifdef _STL_HAS_CXX17
      fs::path _path = path;
      if (fs::exists(_path)) {
        result = true;
        break;
      }
      result = fs::create_directories(_path.lexically_normal());
#endif
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}

std::string Directory::GetTempDir() {
  std::string tempDir;
#ifdef _WIN32
  tempDir = std::getenv("TEMP");
  if (tempDir.empty()) {
    tempDir = std::getenv("TMP");
  }
#else
  tempDir = std::getenv("TMPDIR");
  if (tempDir.empty()) {
    tempDir = "/tmp";
  }
#endif
  if (!tempDir.empty())
    tempDir.append("/");
  return tempDir;
}
void Directory::EnumU16(const std::u16string &inputPath,
                        std::map<std::u16string /*full path*/,
                                 std::u16string /*relative path*/> &dirs,
                        std::map<std::u16string /*full path*/,
                                 std::u16string /*relative path*/> &files,
                        const bool &recursive) {
  do {
    if (!ExistsU16(inputPath))
      break;
    if (recursive) {
      auto iterator = fs::recursive_directory_iterator(inputPath);
      for (const fs::directory_entry &entry : iterator) {
        fs::path relativePath = fs::relative(entry.path(), inputPath);
        std::u16string relativePathStr = relativePath.generic_u16string();

        if (fs::is_directory(entry.path())) {
          dirs.emplace(relativePathStr, stl::Path::NormalU16(inputPath + u"\\" +
                                                             relativePathStr));
        } else {
          files.emplace(
              relativePathStr,
              stl::Path::NormalU16(inputPath + u"\\" + relativePathStr));
        }
      }
    } else {
      auto iterator = fs::directory_iterator(inputPath);
      for (const fs::directory_entry &entry : iterator) {
        fs::path relativePath = fs::relative(entry.path(), inputPath);
        std::u16string relativePathStr = relativePath.generic_u16string();

        if (fs::is_directory(entry.path())) {
          dirs.emplace(relativePathStr, stl::Path::NormalU16(inputPath + u"\\" +
                                                             relativePathStr));
        } else {
          files.emplace(
              relativePathStr,
              stl::Path::NormalU16(inputPath + u"\\" + relativePathStr));
        }
      }
    }
  } while (0);
}
void Directory::EnumU8(
    const std::string &inputPath,
    std::map<std::string /*full path*/, std::string /*relative path*/> &dirs,
    std::map<std::string /*full path*/, std::string /*relative path*/> &files,
    const bool &recursive) {
  do {
    if (!ExistsU8(inputPath))
      break;
    if (recursive) {
      auto iterator = fs::recursive_directory_iterator(inputPath);
      for (const fs::directory_entry &entry : iterator) {
        fs::path relativePath = fs::relative(entry.path(), inputPath);
        std::string relativePathStr = relativePath.generic_string();

        if (fs::is_directory(entry.path())) {
          dirs.emplace(relativePathStr,
                       stl::Path::NormalU8(inputPath + "\\" + relativePathStr));
        } else {
          files.emplace(relativePathStr, stl::Path::NormalU8(inputPath + "\\" +
                                                             relativePathStr));
        }
      }
    } else {
      auto iterator = fs::directory_iterator(inputPath);
      for (const fs::directory_entry &entry : iterator) {
        fs::path relativePath = fs::relative(entry.path(), inputPath);
        std::string relativePathStr = relativePath.generic_string();

        if (fs::is_directory(entry.path())) {
          dirs.emplace(relativePathStr,
                       stl::Path::NormalU8(inputPath + "\\" + relativePathStr));
        } else {
          files.emplace(relativePathStr, stl::Path::NormalU8(inputPath + "\\" +
                                                             relativePathStr));
        }
      }
    }
  } while (0);
}

void Directory::EnumW(
    const std::wstring &inputPath,
    std::map<std::wstring /*full path*/, std::wstring /*relative path*/> &dirs,
    std::map<std::wstring /*full path*/, std::wstring /*relative path*/>
        &files) {
  do {
    if (!ExistsW(inputPath))
      break;
    for (const fs::directory_entry &entry :
         fs::recursive_directory_iterator(inputPath)) {
      fs::path relativePath = fs::relative(entry.path(), inputPath);
      std::wstring relativePathStr = relativePath.generic_wstring();
      if (fs::is_directory(entry.path())) {
        dirs.emplace(relativePathStr,
                     stl::Path::NormalW(inputPath + L"\\" + relativePathStr));
      } else {
        files.emplace(relativePathStr,
                      stl::Path::NormalW(inputPath + L"\\" + relativePathStr));
      }
    }
  } while (0);
}
