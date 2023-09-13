#ifndef NON_PREEMPTIVE_PRIORITY_HPP
#define NON_PREEMPTIVE_PRIORITY_HPP


#include<memory>
#include "NonPreemptiveScheduler.hpp"    

class NonPreemptivePriority : public NonPreemptiveScheduler {
  private:
    class CmpProcess {
      public:
        bool operator()(const Process *a, const Process *b) {
          return a->priority < b->priority;
        }
    };

  public:
    NonPreemptivePriority()
      :NonPreemptiveScheduler(std::make_unique<PriorityQueue<CmpProcess>>()) {}
    
};

#endif