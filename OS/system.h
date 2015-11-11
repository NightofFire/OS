#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class System {
private:
	vector<vector<int>> numHDD;
	vector<vector<int>> numPrinters;
	vector<vector<int>> numMem;

public:
	System(int,int,int);
	~System();
	void display();
};
#endif