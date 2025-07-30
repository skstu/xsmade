#include "config.h"

IModel::IModel() {
}
IModel::~IModel() {
}
bool IModel::Ready() const {
  std::lock_guard<std::mutex> lck(*mtx_);
  return ready_.load();
}
bool IModel::LoadModelParts() {
  bool result = false;
  std::lock_guard<std::mutex> lck(*mtx_);
  do {
    const std::string modelPartsDir =
        Config::CreateOrGet()->GetProjectModelPartsDir();
    if (!stl::Directory::Exists(modelPartsDir))
      break;
    if (stl::Directory::Empty(modelPartsDir))
      break;
    std::map<std::string, std::string> dirs, files;
    stl::Directory::Enum(modelPartsDir, dirs, files, false);
    for (const auto &f : files) {
      std::string part_buffer = stl::File::ReadFile(f.second);
      if (part_buffer.empty())
        continue;
      rapidjson::Document doc;
      if (doc.Parse(part_buffer.data(), part_buffer.size()).HasParseError())
        continue;
      if (!doc.HasMember(chromium::xsiumio::kObjectKey) ||
          !doc[chromium::xsiumio::kObjectKey].IsObject())
        continue;
      chromium::xsiumio::IXSiumio node;
      node << doc[chromium::xsiumio::kObjectKey];
      if (node.identify <= 0)
        continue;
      xsiumios_.emplace(node.identify, node);
    }
    result = true;
  } while (0);
  LOG_INFO("Load model parts total {}", xsiumios_.size());
  std::cout << "Load model parts total " << xsiumios_.size() << std::endl;
  ready_.store(true);
  return result;
}
bool IModel::GenModel() {
  bool result = false;
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (xsiumios_.empty())
      break;
    for (const auto &node : xsiumios_) {
      model_.canvas.emplace_back(node.second.fps.canvas);
      model_.webgl.emplace_back(node.second.fps.webgl);
      model_.audio.emplace_back(node.second.fps.audio);
      model_.font.emplace_back(node.second.fps.font);
      model_.cpu_cores.emplace_back(node.second.fps.hardwareConcurrency);
      model_.device_memory.emplace_back(node.second.fps.deviceMemory);
    }
    result = true;
  } while (0);
  return result;
}