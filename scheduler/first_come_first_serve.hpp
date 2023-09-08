#ifndef FIRST_COME_FIRST_SERVE
#define FIRST_COME_FIRST_SERVE

#include <queue>
#include "Scheduler.hpp"

class FirstComeFirstServe : public Scheduler {
  public:
    void add_process(Process *proc) { 
      this->processes.push(proc);
      proc->state = Process::State::READY;
    }
    bool empty() const { return this->processes.empty(); }
    void terminate_process(Process *proc) { 
      proc->state = Process::State::TERMINATED;
    }

    Process *get_ready_process() {
      // Assume que o processo retornado começará a ser executado

      Process *proc = this->processes.front();
      proc->state = Process::State::RUNNING;

      this->processes.pop();
      return proc;
    }

  private:
    std::queue<Process*> processes;
};

#endif
