#include "Simulator.hpp"

#include <algorithm>
#include <climits>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "process/Process.hpp"

const std::vector<Process> &Simulator::simulate() {
  /*
   * TODO: mudança de contexto
   * Preempção
   * */

  int curr_time = 0;
  auto next_process = this->processes.begin();

  while (next_process != this->processes.end() || !this->scheduler.empty()) {
    if (this->scheduler.empty()) {
      curr_time = next_process->begin;
      this->scheduler.add_process( &(*next_process ));
      next_process++;
      continue;
    }

    Process *curr_process = this->scheduler.get_ready_process();
    curr_process->execution_time = 0;

    curr_time = this->run_process(curr_process, curr_time, next_process);
  }

  return this->processes;
}

int Simulator::run_process(Process *curr_process, int curr_time,
                           std::vector<Process>::iterator &next_process) {


  int quantum = this->scheduler.get_quantum();
  int begin = curr_time;
  do {
    int time_for_next_process = (next_process != this->processes.end())
                                    ? next_process->begin - curr_time
                                    : INT_MAX;

    int max_duration = std::min(time_for_next_process, curr_time + quantum);

    if (curr_process->duration <= max_duration) {
      this->scheduler.terminate_process(curr_process);
      curr_process->end = curr_time + curr_process->duration;
      curr_process->duration = 0;
      curr_time = curr_process->end;
    } else {
      curr_process->duration -= max_duration;
      curr_process->execution_time += max_duration;
      curr_time += max_duration;
    }

    if (next_process != this->processes.end() &&
        curr_time == next_process->begin) {
      this->scheduler.add_process(&( *next_process ));
      next_process++;
    }
  } while (curr_process->state == Process::State::RUNNING);

  curr_process->execution_intervals.emplace_back(begin, curr_time);
  return curr_time;
}

std::vector<Process> Simulator::read_file(const std::string &path) {
  std::ifstream file(path);

  if (!file.is_open()) {
    throw std::runtime_error("Não foi possível abrir o arquivo " + path);
  }

  std::vector<Process> processes;

  int creation_date, duration, priority, id = 0;
  while (file >> creation_date >> duration >> priority) {
    std::string identifier = "P" + std::to_string(id++);
    processes.emplace_back(creation_date, duration, priority, identifier);
  }

  std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
      return a.begin < b.begin;
  });

  return processes;
}
