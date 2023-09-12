#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include <algorithm>
#include <utility>

using namespace std;

class Process
{
public:
    enum State {
        NOT_STARTED, READY, RUNNING, TERMINATED
    };

	Process(int i, int c, int d, int p) { 
		pid = i;
		creation_time = c;
		duration = d;
		priority = p;
        execution_time = 0;
        state = NOT_STARTED;
        end_time;
	}

	
    friend ostream &operator<<(ostream& os, const Process& p) {
		os << "Process Id: " << p.pid << "; creation time = " << p.creation_time << "; duration = " << p.duration << "; priority = " << p.priority << endl;
		return os;
	}
	


	int pid;
	int creation_time;
	int duration; //seconds
	int priority;
    int execution_time;
    State state;
    int end_time;
    std::vector<std::pair<int,int>> execution_intervals;
};


std::vector<std::unique_ptr<Process>> read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Erro ao abrir o arquivo!\n");
    }

    int creation_time, duration, priority;
    
    std::vector<std::tuple<int, int, int>> processes_params;

    while (file >> creation_time >> duration >> priority)
        processes_params.emplace_back(creation_time, duration, priority);
    
    /*
    "Note que a ordem dos processos não precisa estar ordenada por data de criação de cada processo."

    O enunciado do trabalho indica que os processos não estão ordenados por data de criação, logo precisamos
    ordená-los aqui para que o Simulator funcione corretamente.
    */
    std::sort(processes_params.begin(), processes_params.end());

    std::vector<std::unique_ptr<Process>> processes;
    int pid = 0;
    for (auto[creation_time, duration, priority] : processes_params) {
        auto ptr = std::make_unique<Process>(pid++, creation_time, duration, priority);
        processes.push_back(std::move(ptr));
    }

    return processes;
}

#endif