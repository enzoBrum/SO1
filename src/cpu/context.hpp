#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <array>

enum class ProcessState {
  NEW,        // Novo processo
  READY,      // Pronto para execução
  RUNNING,    // Em execução
  WAITING,    // Em espera
  TERMINATED  // Terminado
};
/**
 * @brief Representa o contexto de algum processador genérico
 * @tparam T indica o tipo de inteiro usado pelo processador
 * @tparam N número de registradores do processador
 */
template <typename T, std::size_t N>
class Context {
 public:
  Context() : sp(0), pc(0), st(0), processState(ProcessState::NEW) {}

  // Configurar valores do contexto
  void setSP(T value) { sp = value; }
  void setPC(T value) { pc = value; }
  void setST(T value) { st = value; }
  void setReg(T value, int num_register) { registers[num_register] = value; }
  void setProcessState(ProcessState state) { processState = state; }

  // Obter valores do contexto
  T getSP() const { return sp; }
  T getPC() const { return pc; }
  T getST() const { return st; }
  T getReg(int num_register) const { return registers[num_register]; }
  ProcessState getProcessState() const { return processState; }

 private:
  T sp;                        // Stack PoTer
  T pc;                        // Program Counter
  T st;                        // Status Register
  ProcessState processState;   // Estado do processo
  std::array<T, N> registers;  // Registradores
};

#endif
