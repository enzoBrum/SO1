#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "../process/Process.hpp"
#include <vector>
#include <memory>

class Printer {
    public:
        static void print_all(const std::vector<std::unique_ptr<Process>>& processes, const std::string& scheduler_name);

    private:
        static void printDiagram(const std::vector<Process*>& processes);
        static void printStatistics(const std::vector<Process*>& processes);
};
#endif 
