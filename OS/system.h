#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "process.h"
using namespace std;

class System {
private:
	
	int memSize;
	vector<queue<int>> numHDD;
	vector<queue<int>> numPrinters;
	vector<Process> numMem;
	vector<Process> readQueue;
	vector<Process*> CPU;

public:
	System(int,int,int);
	~System();
	void display();
	void execPrinter();
	void termPrinter();
	void execHDD();
	void termHDD();
	void snapShot();
	vector<Process*> &returnCPU();
};
#endif