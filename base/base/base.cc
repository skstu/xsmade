#include <base.h>

Base::Base() {
  Init();
}
Base::~Base() {
  UnInit();
}
void Base::Init() {
  loop_ = (uv_loop_t *)malloc(sizeof(uv_loop_t));
  ready_.store(true);
}
void Base::UnInit() {
  if (loop_) {
    free(loop_);
    loop_ = nullptr;
  }
  ready_.store(false);
}
bool Base::Ready() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return open_.load();
}
bool Base::Start() {
  do {
    if (!ready_.load() || open_.load())
      break;
    open_.store(true);
    threads_.emplace_back([this]() { Process(); });
  } while (0);
  return open_.load();
}
void Base::Stop() {
  do {
    if (!open_.load())
      break;
    open_.store(false);
    for (auto &t : threads_) {
      t.join();
    }
    threads_.clear();
    uv_library_shutdown();
  } while (0);
}
void Base::Process() {
  do {
    if (0 != uv_loop_init(loop_))
      break;
    loop_->data = this;
    do {
      tasks_.execute();
      uv_walk(
          loop_,
          [](uv_handle_t *handle, void *arg) { ///
            Base *base = reinterpret_cast<Base *>(handle->loop->data);
            auto sss = 0;
          },
          nullptr);
      uv_run(loop_, UV_RUN_NOWAIT);
      if (!open_.load()) {
        uv_walk(
            loop_,
            [](uv_handle_t *handle, void *arg) {
              if (!uv_is_closing(handle)) {
                uv_close(handle, nullptr);
              }
            },
            nullptr);
        uv_run(loop_, uv_run_mode::UV_RUN_DEFAULT);
        uv_loop_close(loop_);
        break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    } while (1);

  } while (0);
}
////////////////////////////////////////////////////////////////////
static Base *g_instance = nullptr;
Base *Base::GetOrCreate() {
  if (g_instance == nullptr) {
    g_instance = new Base();
  }
  return g_instance;
}
void Base::Destroy() {
  if (g_instance) {
    g_instance->Stop();
    delete g_instance;
    g_instance = nullptr;
  }
}
uv_loop_t *Base::GetLoop() {
  if (g_instance) {
    return g_instance->loop_;
  }
  return nullptr;
}
