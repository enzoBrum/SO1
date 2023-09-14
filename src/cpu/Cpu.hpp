#ifndef CPU_HPP
#define CPU_HPP


#include<vector>
#include<memory>
#include "../process/Process.hpp"

class Kernel;
class CPU {
    public:
        /**
         * Função responsável por simular a execução de um processo
         * @param kernel ponteiro para o Kernel
         * @param curr_process ponteiro para o processo atual
         * @param next_process iterator para um vetor contendo ponteiros para todos os processos que serão criados durante a execução do programa
         * @param curr_time tempo no qual a execução atual do processo começou
         * @returns tempo em que o a execução foi finalizada
        */
        virtual int run_process(Kernel *kernel, Process *curr_process, std::vector<std::unique_ptr<Process>>::iterator& next_process, int curr_time) = 0;
        virtual ~CPU() {};
};

#endif