/**
 * @Author: YunKai Xia
 * @Date:   2023-08-26 14:59:01
 * @Last Modified by:   YunKai Xia
 * @Last Modified time: 2023-08-26 20:27:34
 */
#include <stdint.h>

#ifndef __TIMER_THREAD_H__
#define __TIMER_THREAD_H__
// 单线程形式的计时器
#include <atomic>
#include <functional>
#include <thread>

namespace timer_thread {
class TimerThread {
 public:
  TimerThread() : repeat_(-1), active_(false), period_(0) {}
  TimerThread(int repeat) : repeat_(repeat), active_(false), period_(0) {}
  ~TimerThread() { stop(); }

  template <typename F, typename... Args>
  void registerCallback(int milliseconds, F&& f, Args&&... args) {
    period_ = milliseconds;

    callback_ = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
  }

  void start() {
    if (active_.load()) {
      // 已经激活，不需要重新设置
      return;
    }

    active_.store(true);

    thread_ = std::thread([&]() {
      if (repeat_ < 0) {
        while (active_.load()) {
          std::this_thread::sleep_for(std::chrono::milliseconds(period_));
          if (!active_.load()) return;

          callback_();
        }
      } else {
        while (repeat_ > 0) {
          if (!active_.load()) return;

          std::this_thread::sleep_for(std::chrono::milliseconds(period_));
          if (!active_.load()) return;
          callback_();
          repeat_--;
        }
      }
    });
  }

  void stop() {
    active_.store(false);
    if (thread_.joinable()) {
      thread_.join();
      std::cout << "clear thread " << std::endl;
    }
    std::cout << "stop timer " << std::endl;
  }

 private:
  std::thread thread_;
  std::atomic<bool> active_;
  std::function<void()> callback_;//定时器的回调函数
  int period_;  //定时器的时间间隔
  int repeat_;  // 触发的次数 -1表示永久执行
};
}  // namespace timer_thread
#endif /* __TIMER_THREAD_H__ */
