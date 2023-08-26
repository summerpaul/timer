/**
 * @Author: YunKai Xia
 * @Date:   2023-08-26 15:26:56
 * @Last Modified by:   YunKai Xia
 * @Last Modified time: 2023-08-26 18:06:44
 */
#include <iostream>
#include <string>

#include "timer_thread.h"
using namespace std;
using namespace timer_thread;

void foo() { std::cout << "foo" << std::endl; }

void bar(const std::string &name) { std::cout << "bar: " << name << std::endl; }

class Dog {
 public:
  void bar() { std::cout << "dog bar " << std::endl; }
};

class Cat {
 public:
  void run() {
    timer_.registerCallback(1000, std::bind(&Cat::hello, this));
    timer_.start();
  }

 private:
  void hello() { std::cout << "cat hello" << std::endl; }

 private:
  TimerThread timer_;
};

int main(int argc, char const *argv[]) {
  TimerThread t1;
  t1.registerCallback(1000, foo);
  t1.start();
  TimerThread t2;
  t2.registerCallback(1000, bar, "haha");
  t2.start();
  TimerThread t3;
  Dog dog;
  t3.registerCallback(1000, std::bind(&Dog::bar, &dog));
  t3.start();
  Cat cat;
  cat.run();

  std::getchar();
  return 0;
}
