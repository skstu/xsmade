#include "config.h"
#include <zip.h>
#include <unzip.h>
#if !defined(MAX_PATH)
#define MAX_PATH 260
#endif
bool Zipcc::zipUnCompress(const std::u16string &inputZipFile,
                          const tfzipUnCompressCb &uncompress_cb, void *route) {
  bool result = false;
  unzFile zip_file = NULL;
  do {
    if (!uncompress_cb)
      break;
    if (!stl::File::Exists(inputZipFile))
      break;
    zip_file = unzOpen(stl::Path::U16PathToU8Path(inputZipFile).c_str());
    if (!zip_file)
      break;
    if (UNZ_OK != unzGoToFirstFile(zip_file))
      break;
    do {
      char filename_in_zip[MAX_PATH] = {0};
      unz_file_info file_info;
      if (UNZ_OK != unzGetCurrentFileInfo(zip_file, &file_info, filename_in_zip,
                                          MAX_PATH, nullptr, 0, nullptr, 0))
        break;
      std::u16string strfilename_in_zip = Utfpp::u8_to_u16(filename_in_zip);
      if (!(*std::prev(strfilename_in_zip.end()) == u'\\' ||
            *std::prev(strfilename_in_zip.end()) == u'/')) {
        if (UNZ_OK == unzOpenCurrentFile(zip_file)) {
          char buffer[8192] = {0};
          int read_bytes = 0;
          std::string fileBuffer;
          do {
            read_bytes = unzReadCurrentFile(zip_file, buffer, sizeof(buffer));
            if (read_bytes <= 0)
              break;
            fileBuffer.append(buffer, read_bytes);
          } while (1);
          unzCloseCurrentFile(zip_file);
          if (!uncompress_cb(strfilename_in_zip, fileBuffer, route))
            break;
        }
      }
    } while (unzGoToNextFile(zip_file) == UNZ_OK);
    result = true;
  } while (0);
  if (zip_file) {
    unzClose(zip_file);
    zip_file = NULL;
  }
  return result;
}

bool Zipcc::zipUnCompress(const std::u16string &inputZipFile,
                          const std::u16string &outputUnzipPath) {
  bool result = false;
  unzFile zip_file = NULL;
  do {
    if (!stl::File::Exists(inputZipFile))
      break;
    zip_file = unzOpen(stl::Path::U16PathToU8Path(inputZipFile).c_str());
    if (!zip_file)
      break;
    if (UNZ_OK != unzGoToFirstFile(zip_file))
      break;
    if (!stl::Directory::Create(outputUnzipPath))
      break;
    do {
      char filename_in_zip[MAX_PATH] = {0};
      unz_file_info file_info;
      if (unzGetCurrentFileInfo(zip_file, &file_info, filename_in_zip, MAX_PATH,
                                nullptr, 0, nullptr, 0) != UNZ_OK)
        break;
      const std::u16string filename_in_zip_full =
          outputUnzipPath + u"/" + Utfpp::u8_to_u16(filename_in_zip);

      if (*std::prev(filename_in_zip_full.end()) == u'\\' ||
          *std::prev(filename_in_zip_full.end()) == u'/') {
        if (!stl::Directory::Create(outputUnzipPath))
          break;
      } else {
        if (UNZ_OK != unzOpenCurrentFile(zip_file))
          break;
        char buffer[8192] = {0};
        int read_bytes = 0;
        do {
          read_bytes = unzReadCurrentFile(zip_file, buffer, sizeof(buffer));
          if (read_bytes <= 0)
            break;
          auto tmpPath = stl::Path::Parent(filename_in_zip_full);
          stl::Directory::Create(tmpPath);

          if (!stl::File::WriteFileAddto(filename_in_zip_full,
                                         std::string(&buffer[0], read_bytes)))
            break;
        } while (1);
        unzCloseCurrentFile(zip_file);
      }
    } while (unzGoToNextFile(zip_file) == UNZ_OK);
    result = true;
  } while (0);
  if (zip_file) {
    unzClose(zip_file);
    zip_file = NULL;
  }
  return result;
}
bool Zipcc::zipUnCompress(const std::u16string &inputZipFile,
                          const std::u16string &outputUnzipPath,
                          const tfzipUnCompressProgressCb &progress_cb) {
  bool result = false;
  unzFile zip_file = NULL;
  do {
    if (!progress_cb)
      break;
    if (!stl::File::Exists(inputZipFile))
      break;
    const std::size_t total = stl::File::Size(inputZipFile);
    if (total <= 0)
      break;
    std::size_t current = 0;
    zip_file = unzOpen(stl::Path::U16PathToU8Path(inputZipFile).c_str());
    if (!zip_file)
      break;
    if (UNZ_OK != unzGoToFirstFile(zip_file))
      break;
    if (!stl::Directory::Create(outputUnzipPath))
      break;
    do {
      char filename_in_zip[MAX_PATH] = {0};
      unz_file_info file_info;
      if (unzGetCurrentFileInfo(zip_file, &file_info, filename_in_zip, MAX_PATH,
                                nullptr, 0, nullptr, 0) != UNZ_OK)
        break;
      const std::u16string filename_in_zip_full =
          outputUnzipPath + u"\\" + Utfpp::u8_to_u16(filename_in_zip);

      if (*std::prev(filename_in_zip_full.end()) == u'\\' ||
          *std::prev(filename_in_zip_full.end()) == u'/') {
        if (!stl::Directory::Create(outputUnzipPath))
          break;
      } else {
        if (UNZ_OK != unzOpenCurrentFile(zip_file))
          break;
        char buffer[8192] = {0};
        int read_bytes = 0;
        do {
          read_bytes = unzReadCurrentFile(zip_file, buffer, sizeof(buffer));
          current += read_bytes;
          if (read_bytes <= 0)
            break;
          if (!progress_cb(total, current, nullptr))
            break;
          auto tmpPath = stl::Path::Parent(filename_in_zip_full);
          stl::Directory::Create(tmpPath);

          if (!stl::File::WriteFileAddto(filename_in_zip_full,
                                         std::string(&buffer[0], read_bytes)))
            break;
        } while (1);
        unzCloseCurrentFile(zip_file);
      }
    } while (unzGoToNextFile(zip_file) == UNZ_OK);
    result = true;
  } while (0);
  if (zip_file) {
    unzClose(zip_file);
    zip_file = NULL;
  }
  return result;
}
bool Zipcc::zipCompressDirectory(const std::u16string &inputDirpath,
                                 const std::u16string &outputZipfile) {
  bool result = false;
  zipFile zf = NULL;
  do {
    std::map<std::u16string, std::u16string> dirs, files;
    stl::Directory::EnumU16(inputDirpath, dirs, files, true);

    zf = zipOpen(stl::Path::U16PathToU8Path(outputZipfile).c_str(),
                 APPEND_STATUS_CREATE);
    if (zf == NULL)
      break;
    result = true;
    for (auto &node : files) {
      do {
        if (ZIP_OK != zipOpenNewFileInZip4_64(
                          zf, stl::Path::U16PathToU8Path(node.first).c_str(),
                          NULL, NULL, 0, NULL, 0, NULL, Z_DEFLATED,
                          Z_BEST_COMPRESSION, 0, -MAX_WBITS, DEF_MEM_LEVEL,
                          Z_DEFAULT_STRATEGY, NULL, 0, 36, 1 << 11, 0)) {
          result = false;
          break;
        }
        std::string buffer = stl::File::ReadFile(node.second.c_str());
        if (ZIP_OK !=
            zipWriteInFileInZip(zf, buffer.data(),
                                static_cast<unsigned int>(buffer.size()))) {
          result = false;
          break;
        }
      } while (0);
      zipCloseFileInZip(zf);
      if (!result)
        break;
    }
  } while (0);
  if (zf) {
    zipClose(zf, NULL);
    zf = NULL;
  }
  return result;
}
#if 0
bool Zipcc::zipCompressFile(const std::string& inputFile, const std::string& outputFile) {

	// 压缩包文件名
	const char* zipfile = u8R"(C:\Users\k34ub\Desktop\example.zip)";
	// 需要压缩的文件
	const char16_t* file = uR"(C:\Users\k34ub\Desktop\你好.txt)";
	const char16_t* filenameInZip = uR"(你好.txt)";  // 压缩包内的文件名

	// 打开压缩包
	zipFile zf = zipOpen(zipfile, APPEND_STATUS_CREATE);
	if (zf == NULL) {
		std::cerr << "Error creating " << zipfile << std::endl;
		return 1;
	}
	// 打开新的压缩文件
	int err = // zipOpenNewFileInZip(zf,  filenameInZip, NULL, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_BEST_COMPRESSION);
		zipOpenNewFileInZip4_64(zf,
			(const char*)filenameInZip,
			NULL,
			NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_BEST_COMPRESSION, 0,
			-MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
			NULL, 0, 36, 1 << 11, 0);
	if (err != ZIP_OK) {
		std::cerr << "Error adding " << filenameInZip << " to " << zipfile << std::endl;
		return 1;
	}

	std::string buffer = stl::File::ReadFile(file);

	int r = zipWriteInFileInZip(zf, buffer.data(), buffer.size());
	if (r < 0) {
		std::cerr << "Error writing to zip file" << std::endl;
		return 1;
	}

	// 关闭文件和压缩包
	zipCloseFileInZip(zf);
	zipClose(zf, NULL);

	std::cout << "Successfully created " << zipfile << std::endl;

	return false;
	}
#endif