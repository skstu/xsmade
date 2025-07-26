#include "config.h"

Model::Model() {
}
Model::~Model() {
}
void Model::Release() const {
  delete this;
}
bool Model::LoadModelParts() {
  bool result = false;
  do {
    const std::string modelPartsDir =
        Config::CreateOrGet()->GetProjectModelPartsDir();
    if (!stl::Directory::Exists(modelPartsDir))
      break;
    if (stl::Directory::Empty(modelPartsDir))
      break;
    std::map<std::string, std::string> dirs, files;
    stl::Directory::Enum(modelPartsDir, dirs, files, false);
    result = true;
  } while (0);
  return result;
}