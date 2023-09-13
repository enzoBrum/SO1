#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include<memory>

#include "../process/Process.hpp"
#include "./Queue.hpp"

class Scheduler {
  public:
    Scheduler(std::unique_ptr<Queue>& ptr)
      :processes{std::move(ptr)} {}
  
    virtual ~Scheduler() {}
    
    virtual void add_process(Process* proc) {
      this->processes->push(proc);
      proc->state = Process::READY;
    };
  
    bool empty() const {
      return this->processes->empty();
    }
    
    virtual Process* get_ready_process() = 0;
    
    virtual int get_quantum() {
      return 1e9;
    };
    
    virtual void terminate_process(Process* proc) = 0;
    
    virtual bool process_is_running(Process *proc) = 0;


  protected:
    std::unique_ptr<Queue> processes;

};


#endif
