#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>

#include "cpu/INE5412_CPU.hpp"
#include "kernel/Kernel.hpp"
#include "printer/Printer.hpp"
#include "scheduler/Scheduler.hpp"
#include "scheduler/first_come_first_serve.hpp"
#include "scheduler/non_preemptive_priority.hpp"
#include "scheduler/preemptive_priority.hpp"
#include "scheduler/round_robin.hpp"
#include "scheduler/shortest_job_first.hpp"

/*
 * @brief função responsável por executar o kernel com um escalonador específico
 * @param name nome do escalonador
 * @param path caminho para o arquivo contendo os processos
 * @param scheduler ponteiro para o escalonador escolhido
 * */
void execute_kernel(const std::string& name, const std::string& path, std::unique_ptr<Scheduler>& scheduler) {
  std::unique_ptr<CPU<uint64_t, 6>> cpu = std::make_unique<Ine5412Cpu<uint64_t, 6>>();
  Kernel<uint64_t, 6> kernel(path, scheduler, cpu);
  kernel.simulate();
  Printer::print_all(kernel.get_processes(), name);
}

int main(int argc, char** argv) {
  if (argc < 2 or strcmp(argv[1], "--help") == 0) {
    std::cout << "Uso: simulador <arquivo de input>\n";
    return -1;
  }

  std::string path = argv[1];

  std::unique_ptr<Scheduler> rrobin = std::make_unique<RoundRobin>();
  std::unique_ptr<Scheduler> fcfs = std::make_unique<FirstComeFirstServe>();
  std::unique_ptr<Scheduler> sjf = std::make_unique<ShortestJobFirst>();
  std::unique_ptr<Scheduler> priority_preemptive = std::make_unique<PreemptivePriority>();
  std::unique_ptr<Scheduler> priority_non_preemptive = std::make_unique<NonPreemptivePriority>();

  execute_kernel("First Come First Served", path, fcfs);
  execute_kernel("Shortest Job First", path, sjf);
  execute_kernel("Por prioridade, sem preempção", path, priority_non_preemptive);
  execute_kernel("Por prioridade, com preempção", path, priority_preemptive);
  execute_kernel("Round-Robin", path, rrobin);

  return 0;
}
