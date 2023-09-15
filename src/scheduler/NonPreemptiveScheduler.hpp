#ifndef NON_PREEMPTIVE_SCHEDULER_HPP
#define NON_PREEMPTIVE_SCHEDULER_HPP

#include "Scheduler.hpp"

class NonPreemptiveScheduler : public Scheduler {
 public:
  NonPreemptiveScheduler(std::unique_ptr<Queue> q) : Scheduler(q) {}

  Process* get_ready_process() {
    Process* proc = this->processes->top();
    proc->ctx.setProcessState(ProcessState::RUNNING);

    this->processes->pop();
    return proc;
  }

  void terminate_process(Process* proc) {
    proc->ctx.setProcessState(ProcessState::TERMINATED);
  };

  bool process_is_running(Process* proc) {
    return proc->ctx.getProcessState() == ProcessState::RUNNING;
  };
};

#endif
