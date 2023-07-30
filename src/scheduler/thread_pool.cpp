#include <atomic>
#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include "thread_safe_queue.h"

class Thread_pool {
  TSQ<std::function<void()>> work_queue;
  std::vector<std::thread> threads;

  void worker() {
    while(1) {
      std::function<void()> task;
      task = work_queue.pop();
      task();
    }
  };

public:
  Thread_pool() {
    //auto const thread_count = std::thread::hardware_concurrency();
    int thread_count = 4;
    for (int i = 0; i < thread_count; ++i) {
      threads.push_back(std::thread(&Thread_pool::worker, this));
    }
  }
  template<typename F>
  void submit(F f) {
    work_queue.push(std::function<void()>(f));
  }
};

int main() {
  Thread_pool pool;

  for (int i = 0; i < 10; ++i) {
    pool.submit([=] {std::cout << i;});
  }
  return 0;
}