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


std::vector<std::unique_ptr<Process>> read_file(const std::string& path);

#endif