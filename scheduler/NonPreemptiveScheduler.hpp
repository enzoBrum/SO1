#ifndef NON_PREEMPTIVE_SCHEDULER_HPP
#define NON_PREEMPTIVE_SCHEDULER_HPP


#include "Scheduler.hpp"

class NonPreemptiveScheduler : public Scheduler {
  public:
    NonPreemptiveScheduler(std::unique_ptr<Queue> q)
        :Scheduler(q) {}
  
    Process* get_ready_process() {
      Process *proc = this->processes->top();
      proc->state = Process::State::RUNNING;

      this->processes->pop();
      return proc;
    }
    
    void terminate_process(Process* proc) {
      proc->state = Process::TERMINATED;
    };
    
    bool process_is_running(Process *proc) {
      return proc->state == Process::RUNNING;
    };

};


#endif
