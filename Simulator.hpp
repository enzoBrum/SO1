#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <string>
#include <vector>
#include <memory>

#include "scheduler/Scheduler.hpp"
#include "process/Process.hpp"

class Simulator {
 public:
  Simulator(const std::string& path, std::unique_ptr<Scheduler>& sched)
    :scheduler{std::move(sched)}, processes{read_file(path)} {}

  void simulate();

  const std::vector<std::unique_ptr<Process>>& get_processes() const {
    return this->processes;
  }

 private:
  std::unique_ptr<Scheduler> scheduler;
  std::vector<std::unique_ptr<Process>> processes;

  int run_process(Process* proc, int curr_time, std::vector<std::unique_ptr<Process>>::iterator& next_process);
};

#endif
