#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ProcessParams
{
public:
	ProcessParams(int i, int c, int d, int p) { 
		pid = i;
		creation_time = c;
		duration = d;
		priority = p;
	}

	friend ostream &operator<<(ostream& os, const ProcessParams& p) {
		os << "Process Id: " << p.pid << "; creation time = " << p.creation_time << "; duration = " << p.duration << "; priority = " << p.priority << endl;
		return os;
	}
	
private:
	int pid;
	int creation_time;
	int duration; //seconds
	int priority;
};

class Process
{

public:
	Process() {
		myfile.open("entrada.txt");
		if (!myfile.is_open()) {
			cout << "Erro ao abrir o arquivo!\n";
		}
	}
	
	void read_file() {
	
		int a, b, c, d = 0;
		
		if (!myfile.is_open()) {
			cout << "Arquivo não está aberto!" << endl;
		}
		
		while (myfile >> a >> b >> c) {
			ProcessParams *p = new ProcessParams(d, a, b, c);
			processes.push_back(p);
			d++;
		}

		cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
	}

	void print_processes_params() {
		vector<ProcessParams *>::iterator iter = processes.begin();

		for(iter; iter < processes.end(); iter++) {
			ProcessParams *p = *iter;
			cout << *p;
		}
	}

	~Process() {
		for(int i = 0; i < processes.size(); i++) {
			ProcessParams *p = processes[i];
			delete p;
		}
	}

private:
	ifstream myfile; 
	vector<ProcessParams *> processes;
};

int main()
{
	Process f;
	f.read_file();
	f.print_processes_params();
}

