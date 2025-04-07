#if !defined(__13250ED2_2B9D_47DC_A232_9332E099E4AB__)
#define __13250ED2_2B9D_47DC_A232_9332E099E4AB__

class ITask {
public:
  virtual ~ITask() = default;
  virtual void execute() = 0;
};

template <typename ReturnType, typename... Args> class Task : public ITask {
private:
  std::function<ReturnType(Args...)> func_;
  std::tuple<Args...> args_;

public:
  Task(std::function<ReturnType(Args...)> func, Args &&...args)
      : func_(std::move(func)), args_(std::forward<Args>(args)...) {
  }
  void execute() override {
    execute(std::index_sequence_for<Args...>{});
  }

private:
  template <std::size_t... I> void execute(std::index_sequence<I...>) {
    func_(std::get<I>(args_)...);
  }
};

class Tasks {
private:
  std::queue<std::shared_ptr<ITask>> task_queue;
  std::shared_ptr<std::mutex> mtx_ = std::make_shared<std::mutex>();

public:
  template <typename ReturnType, typename... Args>
  void add(std::function<ReturnType(Args...)> func, Args &&...args) {
    std::lock_guard<std::mutex> lock(*mtx_);
    task_queue.push(std::make_shared<Task<ReturnType, Args...>>(
        std::move(func), std::forward<Args>(args)...));
  }
  void execute() {
    std::lock_guard<std::mutex> lock(*mtx_);
    while (!task_queue.empty()) {
      auto task = task_queue.front();
      task_queue.pop();
      task->execute();
    }
  }
};
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 06 Apr 2025 01:26:30 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__13250ED2_2B9D_47DC_A232_9332E099E4AB__