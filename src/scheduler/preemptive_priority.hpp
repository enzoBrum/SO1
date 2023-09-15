#ifndef PREEMPTIVE_PRIORITY_HPP
#define PREEMPTIVE_PRIORITY_HPP

#include "PreemptiveScheduler.hpp"

class PreemptivePriority : public PreemptiveScheduler {
 private:
  class CmpProcess {
   public:
    bool operator()(const Process *a, const Process *b) {
      return a->priority < b->priority;
    }
  };

 public:
  bool process_is_running(Process *proc) {
    if (!this->processes->empty() &&
        this->processes->top()->priority > proc->priority &&
        proc->ctx.getProcessState() == ProcessState::RUNNING) {
      this->preempt_running_process();
      return false;
    }

    return proc->ctx.getProcessState() == ProcessState::RUNNING;
  }

  PreemptivePriority()
      : PreemptiveScheduler(std::make_unique<PriorityQueue<CmpProcess>>()) {}
};

#endif
