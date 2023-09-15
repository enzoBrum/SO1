#ifndef ROUND_ROBIN_HPP
#define ROUND_ROBIN_HPP

#include <memory>

#include "./PreemptiveScheduler.hpp"

class RoundRobin : public PreemptiveScheduler {
 public:
  int get_quantum() { return 2; }

  bool process_is_running(Process *proc) {
    if (!this->processes->empty() &&
        proc->ctx.getProcessState() == ProcessState::RUNNING &&
        proc->execution_time >= this->get_quantum()) {
      this->preempt_running_process();
      return false;
    }

    return proc->ctx.getProcessState() == ProcessState::RUNNING;
  }

  RoundRobin() : PreemptiveScheduler(std::make_unique<DefaultQueue>()) {}
};

#endif
