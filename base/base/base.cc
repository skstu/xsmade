#include <base.h>

static uv_loop_t *g_uv_default_loop = nullptr;
Base::Base() {
  Init();
}
Base::~Base() {
  UnInit();
}
void Base::Init() {
  g_uv_default_loop = uv_default_loop();
  ready_.store(true);
}
void Base::UnInit() {
  uv_loop_close(g_uv_default_loop);
  ready_.store(false);
}
bool Base::Ready() const {
  std::lock_guard<std::mutex> lock(*mtx_);
  return open_.load();
}
bool Base::Start() {
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (!ready_.load() || open_.load())
      break;
    open_.store(true);
    uv_thread_create(
        &thread_,
        [](void *arg) {
          auto *self = static_cast<Base *>(arg);
          self->Process();
        },
        this);
  } while (0);
  return open_.load();
}
void Base::Stop() {
  std::lock_guard<std::mutex> lock(*mtx_);
  do {
    if (!open_.load())
      break;
    uv_stop(g_uv_default_loop);
    open_.store(false);
    uv_thread_join(&thread_);
    uv_library_shutdown();
  } while (0);
}
void Base::Process() {
  do {
    tasks_.execute();
    uv_run(g_uv_default_loop, UV_RUN_NOWAIT);
    if (!open_.load()) {

      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  } while (1);
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
