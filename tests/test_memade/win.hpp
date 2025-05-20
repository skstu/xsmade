#if !defined(__E132B784_2FBB_4A74_8DB1_FC4906A54464__)
#define __E132B784_2FBB_4A74_8DB1_FC4906A54464__
// #ifdef __OSWIN__
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif /// WIN32_LEAN_AND_MEAN
class ISystem final {
public:
  inline ISystem();
  inline ~ISystem();

private:
  inline void Init();
  inline void UnInit();

private:
  inline void GetCpuCoreInfo(size_t *logicalCores, size_t *physicalCores) const;

public:
  inline bool SetProcessAffinity(HANDLE process,
                                 const std::vector<size_t> &coreIndices);
  inline bool CreateMemoryLimitJobObject(HANDLE process,
                                         size_t memory_limit_bytes,
                                         HANDLE *job) const;

public:
  inline size_t GetLogicalCores() const;
  inline size_t GetPhysicalCores() const;
  inline const std::vector<size_t> &GetInitCoreIndices() const;
  inline void SetInitCoreIndices(const std::vector<size_t> &coreIndices);

private:
  size_t logical_cores_ = 0;
  size_t physical_cores_ = 0;
  std::vector<size_t> init_core_indices_cache_;
};

inline ISystem::ISystem() {
  Init();
}
inline ISystem::~ISystem() {
  UnInit();
}
inline void ISystem::Init() {
  GetCpuCoreInfo(&logical_cores_, &physical_cores_);
}
inline void ISystem::UnInit() {
}
inline size_t ISystem::GetLogicalCores() const {
  return logical_cores_;
}
inline size_t ISystem::GetPhysicalCores() const {
  return physical_cores_;
}
inline void
ISystem::SetInitCoreIndices(const std::vector<size_t> &coreIndices) {
  init_core_indices_cache_ = coreIndices;
}
inline const std::vector<size_t> &ISystem::GetInitCoreIndices() const {
  return init_core_indices_cache_;
}
inline void ISystem::GetCpuCoreInfo(size_t *logicalCores,
                                    size_t *physicalCores) const {
  do {
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    *logicalCores = sys_info.dwNumberOfProcessors;
    *physicalCores = 0;
    DWORD len = 0;
    GetLogicalProcessorInformation(nullptr, &len);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer =
        (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(len);
    GetLogicalProcessorInformation(buffer, &len);
    DWORD count = len / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    for (DWORD i = 0; i < count; ++i) {
      if (buffer[i].Relationship == RelationProcessorCore)
        *physicalCores += 1;
    }
    free(buffer);
  } while (0);
}
inline bool ISystem::CreateMemoryLimitJobObject(
    HANDLE process, size_t memory_limit_bytes /*byte*/, HANDLE *job) const {
  bool result = false;
  do {
    if (!process || memory_limit_bytes <= 0)
      break;
    *job = CreateJobObject(nullptr, nullptr);
    if (!(*job))
      break;
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION job_info = {};
    job_info.BasicLimitInformation.LimitFlags =
        JOB_OBJECT_LIMIT_PROCESS_MEMORY | JOB_OBJECT_LIMIT_JOB_MEMORY;

    job_info.ProcessMemoryLimit = memory_limit_bytes;
    job_info.JobMemoryLimit = memory_limit_bytes;

    if (!SetInformationJobObject(*job, JobObjectExtendedLimitInformation,
                                 &job_info, sizeof(job_info)))
      break;
    result = true;
  } while (0);
  return result;
}
inline bool
ISystem::SetProcessAffinity(HANDLE process,
                            const std::vector<size_t> &coreIndices) {
  bool result = false;
  SetInitCoreIndices(coreIndices);
  do {
    DWORD_PTR affinityMask = 0;
    for (size_t core : coreIndices) {
      if (core < sizeof(DWORD_PTR) * GetLogicalCores()) {
        affinityMask |= (1ULL << core);
      } /*else {
                      return false;
      }*/
    }
    if (affinityMask == 0)
      break;
    if (!SetProcessAffinityMask(process, affinityMask))
      break;
    result = true;
  } while (0);
  return result;
}
// #endif ///__OSWIN__
/// /*_ Memade®（新生™） _**/
/// /*_ Fri, 16 May 2025 03:34:55 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__E132B784_2FBB_4A74_8DB1_FC4906A54464__
