/**
 * @Author: YunKai Xia
 * @Date:   2023-08-26 16:20:53
 * @Last Modified by:   YunKai Xia
 * @Last Modified time: 2023-08-26 20:32:34
 */
#include <iostream>
#include <thread>

#include "singleton.h"
#include "timer_manager.h"
#include "timer_thread.h"
using namespace std;
using namespace time_namager;
using namespace timer_thread;
void foo() { std::cout << "foo" << std::endl; }

void bar(const std::string &name) { std::cout << "bar: " << name << std::endl; }

class Dog {
 public:
  void bar() { std::cout << "dog bar " << std::endl; }
};

int main(int argc, char const *argv[]) {
  auto mgr1 = Singleton<TimerManager>();
  mgr1->schedule(1000, foo);
  auto mgr2 = Singleton<TimerManager>();
  mgr2->schedule(1000, bar, "haha");
  auto mgr3 = Singleton<TimerManager>();
  Dog dog;
  mgr3->schedule(1000, std::bind(&Dog::bar, &dog));
  auto mgr4 = Singleton<TimerManager>();
  TimerThread t1;
  t1.registerCallback(100, [&]() { mgr4->update(); });
  t1.start();
  std::getchar();

  return 0;
}
