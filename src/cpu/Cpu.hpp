#ifndef CPU_HPP
#define CPU_HPP

#include <memory>
#include <vector>

#include "../process/Process.hpp"
#include "context.hpp"

/**
 * @tparam T indica o tipo de inteiro usado pelo processador
 * @tparam N número de registradores do processador
 */
template <typename T, std::size_t N>
class Kernel;

/**
 * @tparam T indica o tipo de inteiro usado pelo processador
 * @tparam N número de registradores do processador
 */
template <typename T, std::size_t N>
class CPU {
 public:
  /**
   * Função responsável por simular a execução de um processo
   * @param kernel ponteiro para o Kernel
   * @param curr_process ponteiro para o processo atual
   * @param next_process iterator para um vetor contendo ponteiros para todos os
   * processos que serão criados durante a execução do programa
   * @param curr_time tempo no qual a execução atual do processo começou
   * @returns tempo em que o a execução foi finalizada
   */
  virtual int run_process(
      Kernel<T, N>* kernel, Process* curr_process,
      std::vector<std::unique_ptr<Process>>::iterator& next_process,
      int curr_time) = 0;
  virtual ~CPU(){};

  virtual void set_context(Context<T, N>& ctx) = 0;
  virtual Context<T, N> get_context() = 0;

  Context<T,N> ctx;
};

#endif
