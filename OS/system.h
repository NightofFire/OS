/*******************************************************************************
Title          : cheng_pan-hwk1.cpp
Author         : Cheng Pan
Created on     : November 12, 2015
Description    : Simulate OS
Usage          : ./cheng_Pan-hwk1
Build with     : g++ -o cheng_Pan-hwk1 cheng_Pan-hwk1.cpp system.cpp system.h
				 process.cpp process.h
Created with   : Visual studio 2015
*******************************************************************************/

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
	vector<deque<Process*>> vHDD;
	vector<deque<Process*>> vPrinters;
	vector<Process*> processMem;
	deque<Process*> readyQueue;
	vector<Process*> CPU;
	vector<Process*>::iterator it;

public:
	System(int,int,int);
	~System();
	void display();
	void termPro();
	void execPrinter(int);
	void termPrinter(int);
	void execHDD(int);
	void termHDD(int);
	bool fitMem(int,int);
	void allocateMem(Process *pro);
	void readyToCPU();
	void toReadyQueue(string,int);
	void snapShot(string);
	vector<Process*> &returnCPU();
	vector<Process*> &returnList();
	deque<Process*> &returnReadyQueue();
	//bool cmd(Process*, Process*);
	
};

struct comp {
	bool operator()(Process * s1, Process * s2)
	{
		return s1->getStart() < s2->getStart();
	}
};
#endif