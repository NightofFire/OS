#ifndef PROCESS_H_
#define PROCESS_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Process {
private:
	vector<vector<int>> numHDD;
	vector<vector<int>> numPrinters;
	vector<vector<int>> numMem;

public:
	Process();
	~Process();
	void display();
};
#endif