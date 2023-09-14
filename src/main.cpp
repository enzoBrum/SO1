#include <memory>
#include <cstring>
#include <iostream>

#include "kernel/Kernel.hpp"
#include "scheduler/first_come_first_serve.hpp"
#include "scheduler/shortest_job_first.hpp"
#include "scheduler/non_preemptive_priority.hpp"
#include "scheduler/preemptive_priority.hpp"
#include "scheduler/round_robin.hpp"
#include "cpu/INE5412_CPU.hpp"

/**
 * TODO:
 * - terminar trocas de contexto
 * - testar mais
 * - aceitar parâmetros definindo escalonador/usar todos os escalonadores sempre
 * - terminar e integrar Printer
 * - relatório
 * - diagrama
*/

int main(int argc, char **argv) {
    if (argc < 2 or strcmp(argv[1], "--help") == 0) {
        std::cout << "Uso: simulador <arquivo de input>\n";
        return -1;
    }

    std::string path = argv[1];
    std::unique_ptr<Scheduler> sched = std::make_unique<RoundRobin>();
    std::unique_ptr<CPU> cpu = std::make_unique<Ine5412Cpu>();

    Kernel kernel(path, sched, cpu);
    kernel.simulate(); 

    for (auto& proc : kernel.get_processes()) {
        for (auto&[b, e] : proc->execution_intervals)
            std::cout << proc->pid << '\t' << b << '\t' << e << '\n';
    }

    return 0;
}