#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "../cpu/context.hpp"

using namespace std;

class Process {
 public:
  Process(int i, int c, int d, int p) {
    pid = i;
    creation_time = c;
    duration = d;
    priority = p;
    execution_time = 0;
    end_time = 0;
    context_switches = 0;
  }

  friend ostream& operator<<(ostream& os, const Process& p) {
    os << "Process Id: " << p.pid << "; creation time = " << p.creation_time
       << "; duration = " << p.duration << "; priority = " << p.priority
       << endl;
    return os;
  }

  int pid;
  int creation_time;
  int duration;  // seconds
  int priority;
  int execution_time;
  int end_time;
  int context_switches;
  std::vector<std::pair<int, int>> execution_intervals;
  Context<uint64_t, 6> ctx;
};

std::vector<std::unique_ptr<Process>> read_file(const std::string& path);

#endif
