#include "sys.h"
#if 0
#include <sys/shm.h>
#include <sys/ipc.h>
#include <iostream>
#include <cstring>

int main() {
    key_t key = ftok("/tmp", 'R');  // 创建唯一的键值
    if (key == -1) {
        std::cerr << "ftok failed" << std::endl;
        return 1;
    }

    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);  // 创建共享内存
    if (shmid == -1) {
        std::cerr << "shmget failed" << std::endl;
        return 1;
    }

    // 映射共享内存
    char* shmPtr = (char*)shmat(shmid, nullptr, 0);
    if (shmPtr == (char*)-1) {
        std::cerr << "shmat failed" << std::endl;
        return 1;
    }

    // 向共享内存写入数据
    strcpy(shmPtr, "Hello from shared memory!");

    // 等待其他进程读取共享内存
    std::cout << "Press any key to exit..." << std::endl;
    std::cin.get();

    // 分离共享内存
    shmdt(shmPtr);

    return 0;
}

#include <sys/shm.h>
#include <sys/ipc.h>
#include <iostream>

int main() {
    key_t key = ftok("/tmp", 'R');  // 使用与第一个进程相同的键值
    if (key == -1) {
        std::cerr << "ftok failed" << std::endl;
        return 1;
    }

    int shmid = shmget(key, 1024, 0666);  // 获取共享内存
    if (shmid == -1) {
        std::cerr << "shmget failed" << std::endl;
        return 1;
    }

    // 映射共享内存
    char* shmPtr = (char*)shmat(shmid, nullptr, 0);
    if (shmPtr == (char*)-1) {
        std::cerr << "shmat failed" << std::endl;
        return 1;
    }

    // 读取共享内存中的数据
    std::cout << "Data from shared memory: " << shmPtr << std::endl;

    // 分离共享内存
    shmdt(shmPtr);

    return 0;
}
#endif
XS_EXTERN int xs_sys_shared_memory_create(const char *name, size_t size,
                                          void **base) {
  return 0;
}
XS_EXTERN int xs_sys_shared_memory_destroy(const char *name) {
  return 0;
}
XS_EXTERN int xs_sys_shared_memory_open(const char *name, void **base) {
  return 0;
}