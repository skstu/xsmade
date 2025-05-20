#include <xs.h>
#include <system.hpp>
#include <fmt/format.h>

#include "win.hpp"
//!@ 获取CPU核心数
static void Win_GetCpuCoreInfo(unsigned long *logicalCores,
                               unsigned long *physicalCores);
//!@ 获取亲和掩码和优先级
static void Win_GetProcessAffinityAndPriority(
    HANDLE process, unsigned long long *lProcessAffinityMask,
    unsigned long long *lSystemAffinityMask, unsigned long *priorityClass);
//!@ 设置进程亲和掩码
static bool Win_SetProcessAffinity(HANDLE process,
                                   std::initializer_list<int> coreIndices);
//!@ 设置进程优先级
static bool Win_SetProcessPriority(HANDLE process, int p);
static bool Win_CreateMemoryLimitJobObject(
    HANDLE process,
    unsigned long long memory_limit_bytes /*2ULL * 1024 * 1024 * 1024*/,
    HANDLE *job);
int main(int argc, char **argv) {
  ISystem *sys = new ISystem();
  sys->SetProcessAffinity(GetCurrentProcess(), {1, 3, 6, 7});
  unsigned long logicalCores = 0;
  unsigned long physicalCores = 0;
  Win_GetCpuCoreInfo(&logicalCores, &physicalCores);

  HANDLE curProcess = GetCurrentProcess();
  unsigned long priorityClass = 0;
  unsigned long long lProcessAffinityMask = 0;
  unsigned long long lSystemAffinityMask = 0;
  Win_GetProcessAffinityAndPriority(curProcess, &lProcessAffinityMask,
                                    &lSystemAffinityMask, &priorityClass);

  Win_SetProcessAffinity(curProcess, {1, 3, 6, 7});

  HANDLE job = nullptr;
  Win_CreateMemoryLimitJobObject(curProcess, 200ULL * 1024 * 1024, &job);
  AssignProcessToJobObject(job, curProcess);
#if 0
  std::cout << "当前进程已加入带 200MB 内存限制的 Job。\n";
  // 分配内存：250MB，超限尝试触发 Job 终止
  std::cout << "尝试分配 250MB 内存...\n";
  try {
    void *bigMem = malloc(250 * 1024 * 1024);
    if (bigMem == nullptr) {
      std::cout << "内存分配失败。\n";
    } else {
      memset(bigMem, 0, 250 * 1024 * 1024);
      std::cout << "分配成功，未被限制（说明 Job 设置无效或未触发）。\n";
    }
  } catch (...) {
    std::cerr << "分配时异常（未必能捕获）。\n";
  }
#endif
  std::string input;
  do {
    input.clear();
    std::getline(std::cin, input);
    if (input == "q" || std::cin.eof()) {
      break;
    }
  } while (1);

  return 0;
}
bool Win_SetProcessAffinity(HANDLE process,
                            std::initializer_list<int> coreIndices) {
  bool result = false;
  unsigned long logicalCores = 0;
  unsigned long physicalCores = 0;
  Win_GetCpuCoreInfo(&logicalCores, &physicalCores);
  do {
    DWORD_PTR affinityMask = 0;
    for (int core : coreIndices) {
      if (core >= 0 && core < sizeof(DWORD_PTR) * logicalCores) {
        affinityMask |= (1ULL << core);
      } /*else {
        return false;
      }*/
    }
    if (!SetProcessAffinityMask(process, affinityMask))
      break;
    result = true;
  } while (0);
  return result;
}
bool Win_SetProcessPriority(HANDLE process, int p) {
  return false;
}
void Win_GetProcessAffinityAndPriority(HANDLE process,
                                       unsigned long long *lProcessAffinityMask,
                                       unsigned long long *lSystemAffinityMask,
                                       unsigned long *priorityClass) {
  GetProcessAffinityMask(process, lProcessAffinityMask, lSystemAffinityMask);
  *priorityClass = GetPriorityClass(process);
}

void Win_GetCpuCoreInfo(unsigned long *logicalCores,
                        unsigned long *physicalCores) {
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
}
bool Win_CreateMemoryLimitJobObject(HANDLE process,
                                    unsigned long long memory_limit_bytes,
                                    HANDLE *job) {
  bool result = false;
  *job = CreateJobObject(nullptr, nullptr);
  do {
    if (!(*job))
      break;
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION job_info = {0};
    job_info.BasicLimitInformation.LimitFlags =
        JOB_OBJECT_LIMIT_PROCESS_MEMORY | JOB_OBJECT_LIMIT_JOB_MEMORY;

    job_info.ProcessMemoryLimit = memory_limit_bytes;
    job_info.JobMemoryLimit = memory_limit_bytes;

    if (!SetInformationJobObject(*job, JobObjectExtendedLimitInformation,
                                 &job_info, sizeof(job_info))) {
      int err = GetLastError();
      break;
    }
    result = true;
  } while (0);
  // // 2. 设置 Job 限制：总进程内存不得超过 memory_limit_bytes

  // // 3. 把当前进程加入 Job（你可以改为 Add Chromium 子进程）
  // if (!AssignProcessToJobObject(hJob, GetCurrentProcess())) {
  //   std::cerr << "AssignProcessToJobObject failed\n";
  //   return;
  // }
  return result;
}
