#ifndef SHORTEST_JOB_FIRST_HPP
#define SHORTEST_JOB_FIRST_HPP

#include <memory>

#include "NonPreemptiveScheduler.hpp"

class ShortestJobFirst : public NonPreemptiveScheduler {
 private:
  class CmpProcess {
   public:
    bool operator()(const Process *a, const Process *b) {
      return a->duration >= b->duration;
    }
  };

 public:
  ShortestJobFirst()
      : NonPreemptiveScheduler{std::make_unique<PriorityQueue<CmpProcess>>()} {}
};

#endif
