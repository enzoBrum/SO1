#include "Process.hpp"

std::vector<std::unique_ptr<Process>> read_file(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Erro ao abrir o arquivo!\n");
  }

  int creation_time, duration, priority, pid = 0;

  std::vector<std::unique_ptr<Process>> processes;
  while (file >> creation_time >> duration >> priority) {
    auto ptr =
        std::make_unique<Process>(pid++, creation_time, duration, priority);
    processes.push_back(std::move(ptr));
  }

  /*
  "Note que a ordem dos processos não precisa estar ordenada por data de criação
  de cada processo."

  O enunciado do trabalho indica que os processos não estão ordenados por data
  de criação, logo precisamos ordená-los aqui para que o Simulator funcione
  corretamente.
  */
  std::sort(
      processes.begin(), processes.end(),
      [](const std::unique_ptr<Process>& a, const std::unique_ptr<Process>& b) {
        return a->creation_time < b->creation_time;
      });

  return processes;
}