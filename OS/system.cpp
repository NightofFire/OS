#include <iostream>
#include "system.h"
using namespace std;

System::System(int hdd, int printer, int mem) : numHDD(hdd), numPrinters(printer), memSize(mem)
{

}

System::~System() 
{}

void System::display()
{
	cout << numHDD.size() << " " << numHDD[0].size() << endl;
	cout << numPrinters.size() << " " << numPrinters[0].size() << endl;
	cout << memSize << endl;
	cout << readQueue.empty() << endl;
}

vector<Process*> &System::returnCPU()
{
	return CPU;
}

void System::execPrinter(){}
void System::termPrinter(){}
void System::execHDD(){}
void System::termHDD(){}
void System::snapShot(){}

