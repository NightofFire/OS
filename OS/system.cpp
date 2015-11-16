/*******************************************************************************
Title          : cheng_pan-hwk1.cpp
Author         : Cheng Pan
Created on     : November 12, 2015
Description    : Simulate OS
Usage          : ./cheng_pan-hwk1
Build with     : g++ -o cheng_pan-hwk1 cheng_pan-hwk1.cpp system.cpp process.cpp
Created with   : Visual studio 2015
*******************************************************************************/

#include <iostream>
#include <algorithm> 
#include <string>
#include "system.h"
using namespace std;

System::System(int hdd, int printer, int mem) : vHDD(hdd), vPrinters(printer), memSize(mem)
{

}

System::~System()
{
	for (vector<Process*>::const_iterator it = processMem.begin(); it != processMem.end(); it++)
	{
		delete *it;
	}
	processMem.clear();
}

void System::display()
{
	//cout << numHDD.size() << " " << numHDD[0].size() << endl;
	//cout << numPrinters.size() << " " << numPrinters[0].size() << endl;
	//cout << memSize << endl;
	//cout << readyQueue.empty() << endl;
	/*cout << "memSize = " << processMem.size() << endl;
	for (int i = 0; i < processMem.size(); i++)
	{
		cout << processMem[i]->getStart() << " " << processMem[i]->getEnd() << endl;
	}*/
}

void System::allocateMem(Process *pro)
{
	if (processMem.empty())
	{
		//cout << "step0" << endl;
		pro->setStart(0);
		pro->setEnd(pro->getSize() - 1);
		processMem.push_back(pro);
	}
	else
	{
		for (int i = 0; i < processMem.size(); i++)
		{
			if (processMem[i]->getStart() > pro->getSize() - 1 && i == 0)//processMem.begin() + i != processMem.end() )
			{
				//cout << "step1" << endl;
				pro->setStart(0);
				pro->setEnd(pro->getSize() + pro->getStart() - 1);
				processMem.push_back(pro);
				break;
			}
			else if (processMem[i]->getStart() > pro->getSize() && i != 0 && i + 1 < processMem.size())
			{
				//cout << "step do" << endl;
				//cout << "i = " << i << endl;
				if (processMem[i]->getStart() - processMem[i - 1]->getEnd() - 1 >= pro->getSize())
				{
					//cout << "step2" << endl;
					pro->setStart(processMem[i - 1]->getEnd() + 1);
					pro->setEnd(pro->getSize() + pro->getStart() - 1);
					processMem.push_back(pro);
					break;
				}
				else if (processMem[i + 1]->getSize() - processMem[i]->getEnd() - 1 >= pro->getSize())
				{
					//cout << "step5" << endl;
					pro->setStart(processMem[i]->getEnd() + 1);
					pro->setEnd(pro->getSize() + pro->getStart() - 1);
					processMem.push_back(pro);
					break;
				}
			}
			else if (processMem[i]->getStart() > pro->getSize() && i + 1 == processMem.size())
			{
				if (processMem[i]->getStart() - processMem[i - 1]->getEnd() - 1 > pro->getSize())
				{
					//cout << "step 7" << endl;
					pro->setStart(processMem[i-1]->getEnd() + 1);
					pro->setEnd(pro->getSize() + pro->getStart() - 1);
					processMem.push_back(pro);
					break;
				}
				else
				{
					//cout << "step 6" << endl;
					pro->setStart(processMem[i]->getEnd() + 1);
					pro->setEnd(pro->getSize() + pro->getStart() - 1);
					processMem.push_back(pro);
					break;
				}
			}
			else if (processMem[i]->getStart() < pro->getSize() && i + 1 < processMem.size() && i!=0)
			{
				//cout << "step 3" << endl;
				if (processMem[i + 1]->getStart() - processMem[i]->getEnd() > pro->getSize() && i + 1 < processMem.size())
				{
					pro->setStart(processMem[i]->getEnd() + 1);
					pro->setEnd(pro->getSize() + pro->getStart() - 1);
					processMem.push_back(pro);
					break;
				}

			}
			else if (i + 1 == processMem.size())
			{
				//cout << "step 4" << endl;
				pro->setStart(processMem[i]->getEnd() + 1);
				pro->setEnd(pro->getSize() + pro->getStart() - 1);
				processMem.push_back(pro);
				break;
			}
		}
	}
	sort(processMem.begin(), processMem.end(), comp());
}

void System::termPro()
{
	//cout << "testo 1 = " << processMem[0]->getSize() << endl;
	//cout << processMem.size() << CPU.size() << endl;
	it = processMem.begin();
	for (int i = 0; i < processMem.size(); i++)
	{
		if (processMem[i]->getStart() == CPU[0]->getStart())
		{
			advance(it, i);
			delete(*it);
			// processMem[i];
			processMem.erase(processMem.begin() + i);
			returnCPU().clear();
			break;
		}
	}
	//cout << processMem.size() << CPU.size() << endl;
	//delete returnCPU()[0];


	//cout << "testo 2 " <<processMem[0]->getSize() << endl;
}

vector<Process*> &System::returnCPU()
{
	return CPU;
}

deque<Process*> &System::returnReadyQueue()
{
	return readyQueue;
}

vector<Process*> &System::returnList()
{
	return processMem;
}

void System::readyToCPU()
{
	if (!readyQueue.empty())
	{
		CPU.push_back(readyQueue.front());
		readyQueue.pop_front();
	}
}

void System::toReadyQueue(string choice, int num)
{
	if (choice == "P" && !vPrinters[num].empty())
	{
		readyQueue.push_back(vPrinters[num].front());
		vPrinters[num].pop_front();
	}
	else if (choice == "D" && !vHDD[num].empty())
	{
		readyQueue.push_back(vHDD[num].front());
		vHDD[num].pop_front();
	}
}

void System::execPrinter(int i)
{
	if (!CPU.empty())
	{
		//cout << " i === " << i << endl;
		vPrinters[i].push_back(CPU[0]);
		CPU.clear();
		readyToCPU();
		cout << "What is the file you want to write to?" << endl;
		cin.ignore();
		string fileName;
		int fileSize;
		getline(cin, fileName);
		bool valid = false;
		while (!valid)
		{
			cout << "What is the file size of the file? In bytes." << endl;
			cin >> fileSize;
			if (cin.fail())
			{
				cout << "Invalid size" << endl;
				cin.clear();
				std::cin.ignore(256, '\n');
			}
			else
			{
				valid = true;
			}
		}
		vPrinters[i].back()->setFile("W", fileName, fileSize);
		//cout << vPrinters[i].back()->returnFile();
		//cout << " " << vPrinters[i].back()->returnFileSize() << endl;
	}
	else if (vPrinters.empty())
	{
		cerr << "There are no printers" << endl;
	}
	else
	{
		cout << "There is no process in the CPU" << endl;
	}
}

void System::termPrinter(int i) 
{
	if (!vPrinters[i].empty())
	{
		readyQueue.push_back(vPrinters[i].front());
		vPrinters[i].pop_front();
	}
	else
	{
		cerr << "There're no processes in the printer queue" << endl;
	}
}
void System::execHDD(int i) 
{
	if (!CPU.empty())
	{
		vHDD[i].push_back(CPU[0]);
		readyToCPU();
		CPU.clear();
		bool valid = false;
		string mode;
		while (!valid)
		{
			cout << "Enter 'r' to read. \n"
					"Enter 'w' to write." << endl;
			cin >> mode;
			if (mode == "r" || mode == "w")
			{
				valid = true;
			}
			else
			{
				cerr << "Invalid" << endl;
			}
		}
		valid = false;
		cout << "What is the file you want to write to?" << endl;
		string fileName;
		int fileSize;
		cin.ignore();
		getline(cin, fileName);
		while (!valid)
		{
			cout << "What is the file size of the file? In bytes." << endl;
			cin >> fileSize;
			if (cin.fail())
			{
				cout << "Invalid size" << endl;
				cin.clear();
				std::cin.ignore(256, '\n');
			}
			else
			{
				valid = true;
			}
		}
		vHDD[i].front()->setFile(mode, fileName, fileSize);
	}
	else
	{
		cout << "There is no process in the CPU" << endl;
	}
}

void System::termHDD(int i)
{
	if (!vHDD[i].empty())
	{
		readyQueue.push_back(vPrinters[i].front());
		vHDD[i].pop_front();
	}
	else
	{
		cerr << "There're no processes in the HDD queue" << endl;
	}
}
void System::snapShot(string letter) 
{
	if (letter == "p")
	{
		for (int i = 0; i < vPrinters.size(); i++)
		{
			cout << "Printer " << " " << i + 1 << ":" << endl;
			for (int j = 0; j < vPrinters[i].size(); j++)
			{
				cout << "PID - " << vPrinters[i][j]->getPID() << ", " << vPrinters[i][j]->returnFile() 
					 << ", " << vPrinters[i][j]->returnFileSize() << " bytes, " <<"mode="<< vPrinters[i][j]->retrunMode() << "." << endl;
			}
		}
	}
	else if (letter == "d")
	{
		for (int i = 0; i < vHDD.size(); i++)
		{
			cout << "Printer " << " " << i + 1 << ":" << endl;
			for (int j = 0; j < vHDD[i].size(); j++)
			{
				cout << "PID - " << vHDD[i][j]->getPID() << ", " << vHDD[i][j]->returnFile() 
					 << ", " << vHDD[i][j]->returnFileSize() << " bytes, "<< "mode="<<vHDD[i][j]->retrunMode()<<"." << endl;
			}
		}
	}
	else if (letter == "m")
	{
		cout << "Memory Location: (start position, end position)" << endl;
		for (int i = 0; i < processMem.size(); i++)
		{
			cout << "(" <<processMem[i]->getStart()<<","<< processMem[i]->getEnd() << ")"<< endl;
		}
	}
	else if (letter == "r")
	{
		cout << "PIDs:" << endl;
		for (int i = 0; i < readyQueue.size(); i++)
		{
			cout << readyQueue[i]->getPID() << endl;
		}
	}
}

bool System::fitMem(int size,int maxSize)
{
	//cout << "Size of processMem = " << processMem.size() << endl;
	if (processMem.empty() && size <= maxSize)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < processMem.size(); i++)
		{
			//cout << "i = " << i << " " << endl;
			if (i == 0)
			{
				if (processMem[i]->getStart() - 0 > size - 1)
				{
					//cout << "#1" << endl;
					return true;
				}
				else if (processMem.size() == 1)
				{
					if (maxSize - processMem[i]->getEnd() > size)
					{
						return true;
					}
				}
				else if (processMem.size() == 2 && i + 1 < processMem.size())
				{
					if (processMem[i + 1]->getStart() - processMem[i]->getEnd() > size)
					{
						//cout << "#6" << endl;
						return true;
					}
				}
			}
			else if (i + 1 != processMem.size())
			{
				//cout << "#5" << endl;
				if (processMem[i]->getStart() - processMem[i - 1]->getEnd() - 1 >= size)
				{
					//cout << "#2" << endl;
					return true;
				}
				else if (processMem[i + 1]->getStart() - processMem[i]->getEnd() > size)
				{
					//cout << "#3" << endl;
					return true;
				}
			}
			//else if(process)
			else if (i + 1 == processMem.size())
			{
				if (maxSize - processMem[i]->getEnd() > size)
				{
					//cout << "4" << endl;

					return true;
				}
			}
		}
	}
	return false;
}

