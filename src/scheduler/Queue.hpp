#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <queue>
#include <vector>

#include "../process/Process.hpp"

class Queue {
 public:
  virtual void push(Process*) = 0;
  virtual void pop() = 0;
  virtual Process* top() = 0;
  virtual bool empty() const = 0;
  virtual ~Queue(){};
};

class DefaultQueue : public Queue {
 public:
  void push(Process* obj) { q.push(obj); }

  void pop() { q.pop(); }

  Process* top() { return q.front(); }

  bool empty() const { return q.empty(); }

 private:
  std::queue<Process*> q;
};

template <typename CMP>
class PriorityQueue : public Queue {
 public:
  void push(Process* obj) { q.push(obj); }

  void pop() { q.pop(); }

  Process* top() { return q.top(); }

  bool empty() const { return q.empty(); }

 private:
  std::priority_queue<Process*, std::vector<Process*>, CMP> q;
};

#endif