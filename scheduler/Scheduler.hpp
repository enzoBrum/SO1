#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <climits>

class Scheduler {
 public:
  virtual void add_process(Process* proc) = 0;
  virtual bool empty() const = 0;

  virtual Process* get_ready_process() = 0;
  virtual int get_quantum() {return INT_MAX;};
  virtual void terminate_process(Process* proc) = 0;
};

#endif
