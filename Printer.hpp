#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "process/Process.hpp"
#include <vector>
#include <memory>

class Printer {
    public:

        static void printDiagram(const std::vector<std::unique_ptr<Process>>& processes);
};
#endif PRINTER_HPP