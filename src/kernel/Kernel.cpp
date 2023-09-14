#include "Kernel.hpp"
#include "../cpu/Cpu.hpp"

#include <algorithm>
#include <climits>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

void Kernel::simulate() {
  /*
   * TODO: mudança de contexto
   * */

  int curr_time = 0;
  auto next_process = this->processes.begin();

  while (next_process != this->processes.end() || !this->scheduler->empty()) {
    if (this->scheduler->empty() || (next_process != this->processes.end() && (*next_process)->creation_time == curr_time)) {
      curr_time = (*next_process)->creation_time;
      this->scheduler->add_process(next_process->get());
      next_process++;
      continue;
    }

    Process *curr_process = this->scheduler->get_ready_process();
    curr_process->execution_time = 0;

    curr_time = this->cpu->run_process(this, curr_process, next_process, curr_time);
  }
}
