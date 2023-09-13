#ifndef FIRST_COME_FIRST_SERVE
#define FIRST_COME_FIRST_SERVE

#include <queue>
#include "NonPreemptiveScheduler.hpp"

class FirstComeFirstServe : public NonPreemptiveScheduler {
  public:
    FirstComeFirstServe()
      :NonPreemptiveScheduler{std::make_unique<DefaultQueue>()} {}
};

#endif
