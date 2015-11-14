#include <iostream>
#include <vector>
#include "system.h"
using namespace std;

int main()
{
	int numHDD, numPrinters, numMem;
	string choice;
	cout << "How many HDD system has?" << endl;
	cin >> numHDD;
	cout << "How many printers system have?" << endl;
	cin >> numPrinters;
	cout << "How many memory system have? In bytes" << endl;
	cin >> numMem;

	System system(numHDD, numPrinters, numMem);
	Process *process;
	system.display();

	Menu:
	cout << "Enter 'A' to create a new process.\n"
			"Enter 't' to terminate the process that is currently in the CPU. \n"
			"Enter 'p <number>' to use the printer. \n"
			"Enter 'P <number>' to finish process in the printer. \n"
			"Enter 'd <number>' to use the hard disk drive. \n"
			"Enter 'D <number>' finish using the hard disk drive. \n"
			"Enter 'S' to display all information about the printer."<< endl;
	cin >> choice;

	if (choice == "A")
	{
		int size;
		cout << "How much memory does the process need? In bytes." << endl;
		cin >> size;
		//process = new Process();
	}
	else if (choice == "t")
	{
		delete system.returnCPU()[0];
		system.returnCPU().erase(system.returnCPU().begin());
	}
	else if (choice == "p")
	{
	}
	else if (choice == "P")
	{ }
	else if (choice == "d")
	{ }
	else if (choice == "D")
	{ }
	else
	{
		cerr << "Invalid input" << endl;
		goto Menu;
	}


	return 0;
}