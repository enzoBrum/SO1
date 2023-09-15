#ifndef PREEMPTIVE_SCHEDULER_HPP
#define PREEMPTIVE_SCHEDULER_HPP

#include <memory>

#include "Scheduler.hpp"

class PreemptiveScheduler : public Scheduler {
 public:
  PreemptiveScheduler(std::unique_ptr<Queue> ptr) : Scheduler{ptr} {}

  Process* get_ready_process() {
    Process* proc = this->processes->top();
    proc->ctx.setProcessState(ProcessState::RUNNING);

    this->processes->pop();
    this->running_process = proc;
    return proc;
  }

  void terminate_process(Process* proc) {
    proc->ctx.setProcessState(ProcessState::TERMINATED);
    this->running_process = nullptr;
  };

 protected:
  Process* running_process;
  void preempt_running_process() {
    if (!this->running_process) return;

    this->running_process->ctx.setProcessState(ProcessState::READY);
    this->running_process->execution_time = 0;
    this->processes->push(this->running_process);
    this->running_process = nullptr;
  }
};

#endif
