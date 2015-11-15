#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <algorithm> 
#include "system.h"
using namespace std;



int main()
{

	isdigit('3');
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


	while (choice != "Q" || choice != "q")
	{
		choice = "";
		cout << "Enter 'A' to create a new process.\n"
			"Enter 't' to terminate the process that is currently in the CPU. \n"
			"Enter 'p<number>' to use the printer. \n"
			"Enter 'P<number>' to finish process in the printer. \n"
			"Enter 'd<number>' to use the hard disk drive. \n"
			"Enter 'D<number>' finish using the hard disk drive. \n"
			"Enter 'S' to enter snapshot mode. \n"
			"Enter 'Q' to exit." << endl;
		cin >> choice;
		int num;
		string letter;
		bool validInput = true;
		if (choice.length() > 1)
		{
			if (choice[0] == 'P' || choice[0] == 'p' || choice[0] == 'D' || choice[0] == 'd')
			{
				for (int i = 1; i < choice.length(); i++)
				{
					if (!isdigit(choice[i]))
						validInput = false;
				}
				if (!validInput)
				{
					continue;
				}
				else
				{
					num = stoi(choice.substr(1));
					letter = choice[0];
					if ((letter == "p" || letter == "P") && num <= numPrinters && num>0)
					{
					}
					else if ((letter == "d" || letter == "D") && num <= numPrinters && num > 0)
					{
					}
					else
					{
						cerr << "Invalid input" << endl;
						continue;
					}
					cout << num << endl;
				}
			}
			else
			{
				cerr << "Invalid input" << endl;
				continue;
			}
		}


		//allocate memory by subtracting process memory size by 0, process1.end and see if it fits.
		if (choice == "A")
		{
			int size;
			cout << "How much memory does the process need? In bytes." << endl;
			cin >> size;
			if (size > numMem)
			{
				cerr << "Exceeds memory limit" << endl;
				continue;
			}
			else if (size <= 0)
			{
				cerr << "Memory cannot be less than or equal to 0" << endl;
				continue;
			}
			else if (!system.fitMem(size, numMem))
			{
				cout << "Memory full" << endl;
				continue;
			}
			process = new Process(rand() % 100, size);
			system.allocateMem(process);
			//sort(system.returnList().begin(), system.returnList.end(), cmd);
			if (system.returnCPU().empty())
			{
				system.returnCPU().push_back(process);
			}
			else
			{
				system.returnReadyQueue().push(process);
			}
			system.display();
		}
		else if (choice == "t")
		{
			if (!system.returnCPU().empty())
			{
				system.termPro();
				cout << system.returnCPU().empty() << endl;
				system.readyToCPU();	//move first process in readyqueue to CPU
				cout << system.returnCPU().empty() << endl;
			}
			else
			{
				cerr << "No more processes in the system" << endl;
			}
			//system.display();
		}
		else if (letter == "p")
		{
			system.execPrinter(num - 1);	//since pos starts from 0, sub 1 from num
		}
		else if (letter == "P")
		{
			system.termPrinter(num - 1);
		}
		else if (letter == "d")
		{
		}
		else if (letter == "D")
		{
		}
		else if (choice == "Q" || choice == "q")
		{
			exit(0);
		}
		else
		{
			cerr << "Invalid input" << endl;
		}
	}


	return 0;
}