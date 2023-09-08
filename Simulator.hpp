#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <string>
#include <vector>

#include "scheduler/Scheduler.hpp"

class Simulator {
 public:
  Simulator(const std::string& path, Scheduler& sched)
      : scheduler{sched}, processes{read_file(path)} {}

  const std::vector<Process>& simulate();

  std::vector<Process> read_file(const std::string& path);

 private:
  Scheduler &scheduler;
  std::vector<Process> processes;

  int run_process(Process* proc, int curr_time,
                  std::vector<Process>::iterator& next_process);
};

#endif
