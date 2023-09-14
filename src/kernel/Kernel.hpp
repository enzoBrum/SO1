#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <string>
#include <vector>
#include <memory>

#include "../scheduler/Scheduler.hpp"
#include "../process/Process.hpp"

class CPU;
class Kernel {
 public:
  Kernel(const std::string& path, std::unique_ptr<Scheduler>& sched, std::unique_ptr<CPU>& cpu)
    :scheduler{std::move(sched)}, processes{read_file(path)}, cpu{std::move(cpu)} {}

  
  /**
   * Método responsável por realizar a simulação do escalonamento e da execução
   * dos processos
  */
  void simulate();

  Scheduler *get_scheduler() {
    return this->scheduler.get();
  }

  const std::vector<std::unique_ptr<Process>>& get_processes() const {
    return this->processes;
  }


 private:
  std::unique_ptr<Scheduler> scheduler;
  std::vector<std::unique_ptr<Process>> processes;
  std::unique_ptr<CPU> cpu;
};

#endif
