#ifndef INE5412_CPU_HPP
#define INE5412_CPU_HPP

#include "Cpu.hpp"
#include "context.hpp"

#include<cstdint>

class Ine5412Cpu : public CPU {
    public:
        int run_process(Kernel *kernel, Process *curr_process, std::vector<std::unique_ptr<Process>>::iterator& next_process, int curr_time);

    private:
        Context<uint64_t, 6> ctx;
};

#endif