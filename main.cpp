#include <memory>
#include <cstring>
#include <iostream>

#include "Kernel.hpp"
#include "scheduler/first_come_first_serve.hpp"
#include "scheduler/shortest_job_first.hpp"
#include "scheduler/non_preemptive_priority.hpp"
#include "scheduler/preemptive_priority.hpp"
#include "scheduler/round_robin.hpp"

int main(int argc, char **argv) {
    /*
    TODO: aceitar argumentos de linha de comando iindicando que escalonador usar
    remover preempção do shortest job first
    */
    if (argc < 2 or strcmp(argv[1], "--help") == 0) {
        std::cout << "Uso: simulador <arquivo de input>\n";
        return -1;
    }

    std::string path = argv[1];
    std::unique_ptr<Scheduler> sched = std::make_unique<RoundRobin>();

    Kernel kernel(path, sched);
    kernel.simulate(); 

    for (auto& proc : kernel.get_processes()) {
        for (auto&[b, e] : proc->execution_intervals)
            std::cout << proc->pid << '\t' << b << '\t' << e << '\n';
    }

    return 0;
}