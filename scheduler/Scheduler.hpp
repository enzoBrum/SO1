#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "../process/Process.hpp"

class Scheduler {
 public:
  virtual void add_process(Process* proc) = 0;
  virtual bool empty() const = 0;
  virtual bool process_is_running(Process *proc) const = 0;
  virtual Process* get_ready_process() = 0;
  virtual int get_quantum() const {return 1e9;}; // por padrão, schedulers não têm quantum. Logo setamos ele para um valor muito alto
  virtual void terminate_process(Process* proc) = 0;
};

#endif
