#include <memory>
#include <cstring>
#include <iostream>

#include "Kernel.hpp"
#include "scheduler/first_come_first_serve.hpp"
#include "scheduler/shortest_job_first.hpp"
#include "scheduler/non_preemptive_priority.hpp"
#include "scheduler/preemptive_priority.hpp"
#include "scheduler/round_robin.hpp"

class Printer {
public:
    static void printDiagram(const std::vector<std::unique_ptr<Process>>& processes) {
        int max_execution_time = 0;

        for (const auto& proc : processes) {
            if (!proc->execution_intervals.empty()) {
                int last_interval_end = proc->execution_intervals.back().second;
                if (last_interval_end > max_execution_time) {
                    max_execution_time = last_interval_end;
                }
            }
        }

        std::cout << "tempo";
        for (const auto& proc : processes) {
            std::cout << " P" << proc->pid;
        }
        std::cout << "\n";

        for (int time = 0; time <= max_execution_time; ++time) {
            std::cout << time << "-";
            for (const auto& proc : processes) {
                bool is_executing = false;
                for (const auto& interval : proc->execution_intervals) {
                    int start = interval.first;
                    int end = interval.second;
                    if (time >= start && time <= end) {
                        std::cout << " ##";
                        is_executing = true;
                        break;
                    }
                }
                if (!is_executing) {
                    if (time < proc->creation_time) {
                        std::cout << "  ";
                    } else {
                        std::cout << " --";
                    }
                }
            }
            std::cout << "\n";
        }
    }
};

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

    Printer::printDiagram(kernel.get_processes());

    return 0;
}