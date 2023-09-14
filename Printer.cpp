#include "Printer.hpp"

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