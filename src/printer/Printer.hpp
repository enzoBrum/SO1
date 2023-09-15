#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <memory>
#include <vector>

#include "../process/Process.hpp"

class Printer {
 public:
  static void print_all(const std::vector<std::unique_ptr<Process>>& processes,
                        const std::string& scheduler_name);

 private:
  static void printDiagram(const std::vector<Process*>& processes);
  static void printStatistics(const std::vector<Process*>& processes);
};
#endif
