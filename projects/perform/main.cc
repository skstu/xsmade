#include <iostream>
#ifdef _WIN32
#elif __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#endif

int main() {
#if 0
    // 使用 AppleScript 隐藏当前应用窗口
    system("osascript -e 'tell application \"Terminal\" to close (every window whose name contains \"main\")' &> /dev/null");

    std::cout << "This is a hidden console application on macOS (ARM64)." << std::endl;
    // 模拟主程序逻辑
    for (int i = 0; i < 5; ++i) {
        std::cout << "Running in the background..." << std::endl;
        sleep(1);
    }
#endif

  return 0;
}
