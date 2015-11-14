#ifndef PROCESS_H_
#define PROCESS_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Process {
private:
	int PID;
	int memSize;
	int startIndex;
	int endIndex;

public:
	Process(int, int);
	~Process();
	int getPID();
	int getSize();
	int getStart();
	int getEnd();
	void setStart(int);
	void setEnd(int);
};
#endif