// 修复后的 RequestAnimationFrame FPS 扰动代码
// 需要添加的头文件包含：
#include "base/task/single_thread_task_runner.h"
#include "base/threading/platform_thread.h"
#include "base/time/time.h"
#include "base/functional/bind.h"
#include "base/location.h"

// 在相应的函数中：
int raf_id = RequestAnimationFrame(document(), callback, /*legacy=*/false);
int val = 0;
if (chromium::fps::FPS::LocalDOMWindow_requestAnimationFrame(raf_id, &val) && val > 0) {
    // FPS 扰动：偶尔延迟或跳过帧
    static std::atomic<int> raf_counter{0};  // 使用原子变量确保线程安全
    int current_counter = raf_counter.fetch_add(1) + 1;
    
    if (current_counter % val == 0) { // 质数周期
        // 延迟这一帧 - 修复 lambda 捕获和执行逻辑
        base::SingleThreadTaskRunner::GetCurrentDefault()->PostDelayedTask(
            FROM_HERE,
            base::BindOnce([](scoped_refptr<base::SingleThreadTaskRunner> task_runner, 
                             int counter) {
                // 延迟 1-3ms 执行
                auto delay_ms = 1 + (counter % 3);
                base::PlatformThread::Sleep(base::Milliseconds(delay_ms));
            }, 
            base::SingleThreadTaskRunner::GetCurrentDefault(),
            current_counter),
            base::Milliseconds(1)
        );
    }
}
return raf_id;
