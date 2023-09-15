#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <memory>
#include <string>
#include <vector>

#include "../cpu/Cpu.hpp"
#include "../process/Process.hpp"
#include "../scheduler/Scheduler.hpp"

/**
 * @tparam T indica o tipo de inteiro usado pelo processador
 * @tparam N número de registradores do processador
 */
template <typename T, std::size_t N>
class Kernel {
 public:
  Kernel(const std::string& path, std::unique_ptr<Scheduler>& sched,
         std::unique_ptr<CPU<T, N>>& cpu)
      : scheduler{std::move(sched)},
        processes{read_file(path)},
        cpu{std::move(cpu)} {}

  /**
   * Método responsável por realizar a simulação do escalonamento e da execução
   * dos processos
   */
  void simulate() {
    int curr_time = 0;
    auto next_process = this->processes.begin();

    while (next_process != this->processes.end() || !this->scheduler->empty()) {
      if (this->scheduler->empty() ||
          (next_process != this->processes.end() &&
           (*next_process)->creation_time == curr_time)) {
        curr_time = (*next_process)->creation_time;
        this->scheduler->add_process(next_process->get());
        next_process++;
        continue;
      }

      Process* curr_process = this->scheduler->get_ready_process();
      curr_process->execution_time = 0;

      

      this->cpu->set_context(curr_process->ctx);
      curr_process->context_switches++;
      curr_time =
          this->cpu->run_process(this, curr_process, next_process, curr_time);
      curr_process->ctx = this->cpu->get_context();
    }
  }

  Scheduler* get_scheduler() { return this->scheduler.get(); }

  const std::vector<std::unique_ptr<Process>>& get_processes() const {
    return this->processes;
  }

 private:
  std::unique_ptr<Scheduler> scheduler;
  std::vector<std::unique_ptr<Process>> processes;
  std::unique_ptr<CPU<T, N>> cpu;
};

#endif
