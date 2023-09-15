#ifndef INE5412_CPU_HPP
#define INE5412_CPU_HPP

#include <cstdint>

#include "Cpu.hpp"
#include "context.hpp"

// #include "../kernel/Kernel.hpp"

/**
 * @tparam T indica o tipo de inteiro usado pelo processador
 * @tparam N número de registradores do processador
 */
template <typename T, std::size_t N>
class Ine5412Cpu : public CPU<T, N> {
 public:
  int run_process(Kernel<T, N>* kernel, Process* curr_process,
                  std::vector<std::unique_ptr<Process>>::iterator& next_process,
                  int curr_time) {
    int quantum = kernel->get_scheduler()->get_quantum();
    int begin = curr_time;

    do {
      int time_for_next_process =
          (next_process != kernel->get_processes().end())
              ? (*next_process)->creation_time - curr_time
              : 1e9;

      int max_duration = std::min(time_for_next_process,
                                  quantum - curr_process->execution_time);

      if (curr_process->duration <= max_duration) {
        kernel->get_scheduler()->terminate_process(curr_process);
        curr_process->end_time = curr_time + curr_process->duration;
        curr_process->duration = 0;
        curr_time = curr_process->end_time;
      } else {
        curr_process->duration -= max_duration;
        curr_process->execution_time += max_duration;
        curr_time += max_duration;
      }

      if (next_process != kernel->get_processes().end() &&
          curr_time == (*next_process)->creation_time) {
        kernel->get_scheduler()->add_process(next_process->get());
        next_process++;
      }
    } while (kernel->get_scheduler()->process_is_running(curr_process));

    curr_process->execution_intervals.emplace_back(begin, curr_time - 1);
    return curr_time;
  }

  void set_context(Context<T, N>& ctx) {
    this->ctx = ctx;
  }

  Context<T, N> get_context() {
    return this->ctx;
  }

};

#endif
