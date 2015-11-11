#include <iostream>
#include <vector>
#include "system.h"
using namespace std;

int main()
{
	int numHDD, numPrinters, numMem;
	cout << "How many HDD system has?" << endl;
	cin >> numHDD;
	cout << "How many printers system have?" << endl;
	cin >> numPrinters;
	cout << "How many memory system have? In bytes" << endl;
	cin >> numMem;

	System system(numHDD, numPrinters, numMem);
	system.display();


	return 0;
}