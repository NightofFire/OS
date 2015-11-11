#include <iostream>
#include "system.h"
using namespace std;

System::System(int hdd, int printer, int mem) : numHDD(hdd, vector<int>(0)), numPrinters(printer, vector<int>(0)), numMem(mem, vector<int>(0))
{

}

System::~System() 
{}

void System::display()
{
	cout << numHDD.size() << " " << numHDD[0].size() << endl;
	cout << numPrinters.size() << " " << numPrinters[0].size() << endl;
	cout << numMem.size() << " " << numMem[0].size() << endl;
}

