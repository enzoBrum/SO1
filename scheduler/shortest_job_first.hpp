#ifndef SHORTEST_JOB_FIRST_HPP
#define SHORTEST_JOB_FIRST_HPP


#include <queue>
#include <vector>
#include "Scheduler.hpp"

    

class ShortestJobFirst : public Scheduler {
  public:
    void add_process(Process *proc) { 

      if (this->running_process && proc->duration < this->running_process->duration)
        this->preempt_running_process();
      
      this->processes.push(proc);
      proc->state = Process::READY;
    }
    bool empty() const { return this->processes.empty(); }
    void terminate_process(Process *proc) { 
      proc->state = Process::State::TERMINATED;
      this->running_process = nullptr;
    }

    Process *get_ready_process() {
      // Assume que o processo retornado começará a ser executado

      Process *proc = this->processes.top();
      proc->state = Process::State::RUNNING;

      this->processes.pop();
      this->running_process = proc;
      return proc;
    }

    bool process_is_running(Process *proc) const {
      return proc->state == Process::RUNNING;
    }

  private:
    Process *running_process;

    class CmpProcess {
      public:
        bool operator()(const Process *a, const Process *b) {
          return a->duration >= b->duration;
        }
    };
    void preempt_running_process() {
      if (!running_process) return;

      running_process->state = Process::READY;
      running_process->execution_time = 0;
      this->processes.push(running_process);
      this->running_process = nullptr;
    }
    
    std::priority_queue<Process*, std::vector<Process*>, CmpProcess> processes;
};

#endif