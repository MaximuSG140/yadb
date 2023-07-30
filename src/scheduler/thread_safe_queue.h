#include <condition_variable>
#include <queue>
#include <mutex>

template <typename T>
class TSQ {
  //queue
  std::queue<T> q;
  std::mutex m;
  //condition variable for signaling
  std::condition_variable cond;
  
public:
  //pushes an element to the queue
  void push(T item) {

    //acquire lock
    std::unique_lock<std::mutex> lock(m);

    //add item
    q.push(item);

    // Notify one thread that
    // is waiting
    lock.unlock();
    cond.notify_one();
  }

  //pops an element off the queue
  T pop()
  {
    //acquire lock
    std::unique_lock<std::mutex> lock(m);

      //wait until queue is not empty
    cond.wait(lock, [this]() { return !q.empty(); });
    T item = q.front();
    q.pop();
    return item;
  }
};