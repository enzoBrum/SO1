#include "Printer.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <sstream>
#include <string>
#include <tuple>

void Printer::print_all(const std::vector<std::unique_ptr<Process>>& processes,
                        const std::string& scheduler_name) {
  std::vector<Process*> copy_processes;

  for (auto& ptr : processes) copy_processes.push_back(ptr.get());

  std::sort(copy_processes.begin(), copy_processes.end(),
            [](Process* a, const Process* b) { return a->pid < b->pid; });

  std::cout << '\n'
            << std::setfill('=') << std::setw(120) << "" << std::setfill(' ')
            << '\n';
  std::cout << std::setfill('=') << std::setw(120) << "" << std::setfill(' ')
            << "\n\n";
  std::cout << "Escalonador: " + scheduler_name + "\n\n";
  printStatistics(copy_processes);
  printDiagram(copy_processes);
}

void Printer::printStatistics(const std::vector<Process*>& processes) {
  std::vector<std::string> columns = {"Processo", "Turnaround time",
                                      "Tempo médio de espera",
                                      "Trocas de context"};

  for (auto& col : columns) std::cout << std::setw(30) << std::left << col;
  std::cout << '\n';

  double total_turnaround = 0;
  for (const auto& proc : processes) {
    int tempo_espera;
    std::pair<int, int> last;

    if (proc->execution_intervals.empty()) {
      tempo_espera = 0;
    } else {
      tempo_espera = proc->execution_intervals[0].first - proc->creation_time;
      last = proc->execution_intervals[0];
    }

    for (std::size_t i = 1; i < proc->execution_intervals.size(); ++i) {
      auto interval = proc->execution_intervals[i];
      tempo_espera += (interval.first - last.second - 1);
      last = interval;
    }

    total_turnaround += (proc->end_time - proc->creation_time);
    std::cout << std::setw(30) << ("P" + std::to_string(proc->pid))
              << std::setw(30) << (proc->end_time - proc->creation_time)
              << std::setw(30) << tempo_espera 
              << std::setw(30) << proc->context_switches << '\n';
  }

  std::cout << "Turnaround médio: " << total_turnaround / processes.size()
            << "\n\n";
}

void Printer::printDiagram(const std::vector<Process*>& processes) {
  int max_execution_time = 0;

  for (const auto& proc : processes) {
    if (!proc->execution_intervals.empty()) {
      int last_interval_end = proc->execution_intervals.back().second;
      if (last_interval_end > max_execution_time) {
        max_execution_time = last_interval_end;
      }
    }
  }

  // - log10+1 da a quantidade de dígitos em um número.
  // - soma um para levar o "P" em conta
  int num_of_digits = (processes.size())
                      ? std::log10(processes.size() - 1) + 1
                      : 1; // log10(0) não existe, então atribuímos 1 diretamente

  std::cout << "tempo" << std::right;
  for (const auto& proc : processes) {
    std::stringstream line;
    line << 'P' << proc->pid;
    std::cout << std::setw(num_of_digits + 2) << line.str();
  }
  std::cout << "\n";

  for (int time = 0; time <= max_execution_time; ++time) {
    std::cout << std::setw(2) << std::right << time << std::setw(0) << '-'
              << std::setw(2) << std::left << time + 1 << std::right;
    for (const auto& proc : processes) {
      bool is_executing = false;
      for (const auto& interval : proc->execution_intervals) {
        int start = interval.first;
        int end = interval.second;
        if (time >= start && time <= end) {
          std::cout << std::setw(num_of_digits + 2) << "##";
          is_executing = true;
          break;
        }
      }
      if (!is_executing) {
        if (time < proc->creation_time || proc->end_time <= time) {
          std::cout << std::setw(num_of_digits + 2) << "  ";
        } else {
          std::cout << std::setw(num_of_digits + 2) << "--";
        }
      }
    }
    std::cout << "\n";
  }
}
