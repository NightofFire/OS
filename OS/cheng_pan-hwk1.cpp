/*******************************************************************************
Title          : cheng_pan-hwk1.cpp
Author         : Cheng Pan
Created on     : November 12, 2015
Description    : Simulate OS
Usage          : ./cheng_Pan-hwk1
Build with     : g++ -o cheng_Pan-hwk1 cheng_Pan-hwk1.cpp system.cpp system.h
				 process.cpp process .h
Created with   : Visual studio 2015
*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h> 
#include <algorithm> 
#include "system.h"
using namespace std;

int main()
{

	isdigit('3');
	int numHDD, numPrinters, numMem;
	string choice;
	bool valid = false;
	while (!valid)
	{
		while (!valid)
		{
			cout << "How many HDDs does the system have?" << endl;
			cin >> numHDD;
			if (cin.fail())
			{
				cout << "Invalid number" << endl;
				cin.clear();
				std::cin.ignore(256, '\n');
			}
			else
			{
				valid = true;
			}
		}
		valid = false;
		while (!valid)
		{
			cout << "How many printers does the system have?" << endl;
			cin >> numPrinters;
			if (cin.fail())
			{
				cout << "Invalid number" << endl;
				cin.clear();
				std::cin.ignore(256, '\n');
			}
			else
			{
				valid = true;
			}
		}
		valid = false;
		while (!valid)
		{
			cout << "How much memory does the system have? In bytes" << endl;
			cin >> numMem;
			if (cin.fail() || numMem > 2147483647 || numMem < 0)
			{
				cout << "Invalid number" << endl;
				cin.clear();
				std::cin.ignore(256, '\n');
			}
			else
			{
				valid = true;
			}
		}
	}

	System system(numHDD, numPrinters, numMem);
	Process *process;
	int pid = 0;
	string snapMode;

	while (choice != "Q" || choice != "q")
	{
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
					if ((letter == "p" || letter == "P") && num <= numPrinters && num >= 0)
					{
					}
					else if ((letter == "d" || letter == "D") && num <= numPrinters && num >= 0)
					{
					}
					else
					{
						cin.clear();
						std::cin.ignore(256, '\n');
						cerr << "Invalid input" << endl;
						continue;
					}
					cout << num << endl;
				}
			}
			else
			{
				cin.clear();
				std::cin.ignore(256, '\n');
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
			process = new Process(pid, size);
			system.allocateMem(process);
			pid++;
			//sort(system.returnList().begin(), system.returnList.end(), cmd);
			if (system.returnCPU().empty())
			{
				system.returnCPU().push_back(process);
			}
			else
			{
				system.returnReadyQueue().push_back(process);
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
				cerr << "No more processes in the ReadyQueue/CPU" << endl;
			}
			//system.display();
		}
		else if (letter == "p")
		{
			if (numPrinters == 0)
			{
				cerr << "There are no printers" << endl;
			}
			else
			{
				system.execPrinter(num - 1);	//since pos starts from 0, sub 1 from num
			}
		}
		else if (letter == "P")
		{
			if (numPrinters == 0)
			{
				cerr << "There are no printers" << endl;
			}
			else
			{
				system.termPrinter(num - 1);
				system.toReadyQueue(letter, num - 1);
			}
		}
		else if (letter == "d")
		{
			if (numHDD == 0)
			{
				cerr << "There are no HDDs" << endl;
			}
			else
			{
				system.execHDD(num - 1);
			}
		}
		else if (letter == "D")
		{
			if (numHDD == 0)
			{
				cerr << "There are no HDDs" << endl;
			}
			else
			{
				system.termHDD(num - 1);
				system.toReadyQueue(letter, num - 1);
			}
		}
		else if (choice == "S")
		{
			cout << "You entered snapshot mode! \n"
				"Enter 'r' to show the PIDs of the process in the readyQueue. \n"
				"Enter 'p' to show the PIDs and printers information. \n"
				"Enter 'd' to show the PIDs and disks information. \n"
				"Enter 'm' to show the position of each process in memory." << endl;
			cin >> snapMode;
			if (snapMode == "r" || snapMode == "p" || snapMode == "d" || snapMode == "m")
			{
				system.snapShot(snapMode);
			}
			else
			{
				cerr << "Invalid snapshot mode" << endl;
				continue;
			}
		}
		else if (choice == "Q" || choice == "q")
		{
			exit(0);
		}
		else
		{
			cin.clear();
			std::cin.ignore(256, '\n');
			cerr << "Invalid input" << endl;
		}
	}


	return 0;
}