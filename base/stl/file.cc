#include "stl.hpp"
using namespace stl;
using namespace std;
namespace fs = std::filesystem;

bool File::Remove(const u16string &file) {
  bool result = false;
  try {
#ifdef _STL_HAS_CXX17
    do {
      if (file.empty())
        break;
      fs::path file_path = file;
      if (fs::is_directory(file_path))
        break;
      result = fs::remove(file_path);
    } while (0);
#endif
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool File::Remove(const string &file) {
  bool result = false;
  try {
#ifdef _STL_HAS_CXX17
    do {
      if (file.empty())
        break;
      fs::path file_path = file;
      if (fs::is_directory(file_path))
        break;
      result = fs::remove(file_path);
    } while (0);
#endif
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool File::Remove(const wstring &file) {
  bool result = false;
  try {
#ifdef _STL_HAS_CXX17
    do {
      if (file.empty())
        break;
      fs::path file_path = file;
      if (fs::is_directory(file_path))
        break;
      result = fs::remove(file_path);
    } while (0);
#endif
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool File::Exists(const std::wstring &input_pathname) {
  bool result = false;
  try {
#ifdef _STL_HAS_CXX17
    do {
      if (input_pathname.empty())
        break;
      if (!std::filesystem::exists(input_pathname))
        break;
      if (!std::filesystem::is_regular_file(input_pathname))
        break;
      result = true;
    } while (0);
#endif
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool File::Exists(const std::string &input_pathname) {
  bool result = false;
  try {
#ifdef _STL_HAS_CXX17
    do {
      if (input_pathname.empty())
        break;
      if (!std::filesystem::exists(input_pathname))
        break;
      if (!std::filesystem::is_regular_file(input_pathname))
        break;
      result = true;
    } while (0);
#endif
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}
size_t File::Size(const std::u16string &input_pathname) {
  size_t result = 0;
  try {
#ifdef _STL_HAS_CXX17
    do {
      if (input_pathname.empty())
        break;
      if (!std::filesystem::exists(input_pathname))
        break;
      result = static_cast<size_t>(std::filesystem::file_size(input_pathname));
    } while (0);
#endif
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool File::Exists(const std::u16string &input_pathname) {
  bool result = false;
  try {
#ifdef _STL_HAS_CXX17
    do {
      if (input_pathname.empty())
        break;
      if (!std::filesystem::exists(input_pathname))
        break;
      if (!std::filesystem::is_regular_file(input_pathname))
        break;
      result = true;
    } while (0);
#endif
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}
std::u16string File::Create(const std::u16string &file_path) {
  u16string result;
#ifdef _STL_HAS_CXX17
  do {
    if (file_path.empty())
      break;
    const fs::path path = file_path;
    u16string _tmp = path.lexically_normal().u16string();
    if (fs::exists(path)) {
      if (!fs::is_directory(path)) {
        result = _tmp;
        break;
      }
    }
    const fs::path parent_path = path.parent_path();
    if (!fs::exists(parent_path)) {
      if (!fs::create_directories(parent_path.lexically_normal()))
        break;
    }
    fstream of(path, static_cast<ios_base::openmode>(ios::binary | ios::out |
                                                     ios::app));
    if (!of.is_open())
      break;
    of.close();
    result = _tmp;
  } while (0);
#endif
  return result;
}
string File::Create(const string &file_path) {
  string result;
#ifdef _STL_HAS_CXX17
  do {
    if (file_path.empty())
      break;
    const fs::path path = file_path;
    string _tmp = path.lexically_normal().string();
    if (fs::exists(path)) {
      if (!fs::is_directory(path)) {
        result = _tmp;
        break;
      }
    }
    const fs::path parent_path = path.parent_path();
    if (!fs::exists(parent_path)) {
      if (!fs::create_directories(parent_path.lexically_normal()))
        break;
    }
    fstream of(_tmp, static_cast<ios_base::openmode>(ios::binary | ios::out |
                                                     ios::app));
    if (!of.is_open())
      break;
    of.close();
    result = _tmp;
  } while (0);
#endif
  return result;
}

#if 0
string
File::ReadFileW(const std::wstring& inputFile, const std::wstring& mode /*= L"rb"*/) {
	string result;
	FILE* f_handle = nullptr;
	do {
		f_handle = ::_wfopen(inputFile.c_str(), mode.c_str());
		if (!f_handle)
			break;
		if (0 != ::fseek(f_handle, 0, SEEK_END))
			break;
		long lSize = ::ftell(f_handle);
		if (lSize <= 0)
			break;
		::rewind(f_handle);
		if (0 != ::fseek(f_handle, 0, SEEK_SET))
			break;
		result.resize(lSize);
		size_t nread = ::fread(&result[0], 1, lSize, f_handle);
		if (nread <= 0)
			result.clear();
	} while (0);
	if (f_handle) {
		::fclose(f_handle);
		f_handle = nullptr;
	}
	return result;
}
#endif
string File::ReadFile(/*ios::_Nocreate | ios::_Noreplace | ios::binary*/
                      const string &file_,
                      const int &mode_ /*= ios::in | ios::binary*/) {
  string result;
  try {
    fstream of(fs::path(file_), static_cast<ios_base::openmode>(mode_));
    do {
      if (!of.is_open())
        break;
      of.seekg(0, of.end);
      size_t size = static_cast<size_t>(of.tellg());
      if (size <= 0)
        break;
      result.resize(size, 0x00);
      of.seekg(0, of.beg);
      of.read(&result[0], size);
    } while (0);
    if (of.is_open())
      of.close();
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
std::string
File::ReadFile(/*std::ios::_Nocreate | std::ios::_Noreplace | std::ios::binary*/
               const std::u16string &file_,
               const int &mode_ /*= std::ios::in | std::ios::binary*/) {
  string result;
  try {
    fstream of(fs::path(file_), static_cast<ios_base::openmode>(mode_));
    do {
      if (!of.is_open())
        break;
      of.seekg(0, of.end);
      size_t size = static_cast<size_t>(of.tellg());
      if (size <= 0)
        break;
      result.resize(size, 0x00);
      of.seekg(0, of.beg);
      of.read(&result[0], size);
    } while (0);
    if (of.is_open())
      of.close();
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
string File::ReadFile(/*ios::_Nocreate | ios::_Noreplace | ios::binary*/
                      const wstring &file_,
                      const int &mode_ /*= ios::in | ios::binary*/) {
  string result;
  try {
    fstream of(fs::path(file_), static_cast<ios_base::openmode>(mode_));
    do {
      if (!of.is_open())
        break;
      of.seekg(0, of.end);
      size_t size = static_cast<size_t>(of.tellg());
      if (size <= 0)
        break;
      result.resize(size, 0x00);
      of.seekg(0, of.beg);
      of.read(&result[0], size);
    } while (0);
    if (of.is_open())
      of.close();
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
  return result;
}
void File::ReadFile(/*ios::_Nocreate | ios::_Noreplace | ios::binary*/
                    const string &file_, vector<char> &out_,
                    const int &mode_ /*= ios::in | ios::binary*/) {
  out_.clear();
  try {
    fstream of(fs::path(file_), static_cast<ios_base::openmode>(mode_));
    do {
      if (!of.is_open())
        break;
      of.seekg(0, of.end);
      size_t size = static_cast<size_t>(of.tellg());
      if (size <= 0)
        break;
      out_.resize(size, 0x00);
      of.seekg(0, of.beg);
      of.read(&out_[0], size);
    } while (0);
    if (of.is_open())
      of.close();
  } catch (const std::filesystem::filesystem_error &e) {
    std::cout << e.what() << std::endl;
  }
}
void File::ReadFile(/*ios::_Nocreate | ios::_Noreplace | ios::binary*/
                    const wstring &file_, vector<wchar_t> &out_,
                    const int &mode_ /*= ios::in | ios::binary*/) {
  out_.clear();
  wfstream of(file_.c_str(), static_cast<ios_base::openmode>(mode_));
  do {
    if (!of.is_open())
      break;
    of.seekg(0, of.end);
    size_t size = static_cast<size_t>(of.tellg());
    if (size <= 0)
      break;
    out_.resize(size, 0x00);
    of.seekg(0, of.beg);
    of.read(&out_[0], size);
  } while (0);
  if (of.is_open())
    of.close();
}
#if 0
bool File::WriteFileW(const std::wstring& FilePathname,
	const std::string& WriteData, const std::wstring& OpenMode /*= L"wb"*/) {
	bool result = false;
	do {
		if (FilePathname.empty())
			break;
		if (WriteData.empty())
			break;
		FILE* file = _wfopen(FilePathname.c_str(), OpenMode.c_str());
		if (!file)
			break;
		size_t result = fwrite(WriteData.data(), WriteData.size(), 1, file);
		fclose(file);
	} while (0);
	return result;
}
#endif
bool File::WriteFile(const string& file_, const string& data_,
	const int& mode_ /*= static_cast<int>(ios::binary) |
																				static_cast<int>(ios::out) |
																				static_cast<int>(ios::trunc)*/)
{
  bool result = false;
  try {
    do {
      if (data_.empty())
        break;
      fstream of(fs::path(file_), static_cast<ios_base::openmode>(mode_));
      if (!of.is_open())
        break;
      of << data_;
      of.close();
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool File::WriteFile(const u16string& file_, const string& data_,
	const int& mode_ /*= static_cast<int>(ios::binary) |
																				static_cast<int>(ios::out) |
																				static_cast<int>(ios::trunc)*/)
{
  bool result = false;
  try {
    do {
      if (data_.empty())
        break;
      fstream of(fs::path(file_), static_cast<ios_base::openmode>(mode_));
      if (!of.is_open())
        break;
      of << data_;
      of.close();
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool File::WriteFile(const wstring& file_, const string& data_,
	const int& mode_ /*= static_cast<int>(ios::binary) |
																				static_cast<int>(ios::out) |
																				static_cast<int>(ios::trunc)*/)
{
  bool result = false;
  try {
    do {
      if (data_.empty())
        break;
      fstream of(fs::path(file_), static_cast<ios_base::openmode>(mode_));
      if (!of.is_open())
        break;
      of << data_;
      of.close();
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool File::WriteFileAddto(const std::u16string &file_,
                          const std::string &data_) {
  bool result = false;
  try {
    do {
      if (data_.empty())
        break;
      ofstream of(fs::path(file_), ios::binary | ios::out | ios::app);
      if (!of.is_open())
        break;
      of << data_;
      of.close();
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool File::WriteFileAddto(const std::wstring &file_, const std::string &data_) {
  bool result = false;
  try {
    do {
      if (data_.empty())
        break;
      ofstream of(fs::path(file_), ios::binary | ios::out | ios::app);
      if (!of.is_open())
        break;
      of << data_;
      of.close();
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}
bool File::WriteFileAddto(const string &file_, const string &data_) {
  bool result = false;
  try {
    do {
      if (data_.empty())
        break;
      ofstream of(fs::path(file_), ios::binary | ios::out | ios::app);
      if (!of.is_open())
        break;
      of << data_;
      of.close();
      result = true;
    } while (0);
  } catch (const std::filesystem::filesystem_error &e) {
    result = false;
    std::cout << e.what() << std::endl;
  }
  return result;
}