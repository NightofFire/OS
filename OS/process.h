/*******************************************************************************
Title          : cheng_pan-hwk1.cpp
Author         : Cheng Pan
Created on     : November 12, 2015
Description    : Simulate OS
Usage          : ./cheng_pan-hwk1
Build with     : g++ -o cheng_pan-hwk1 cheng_pan-hwk1.cpp system.cpp system.h
				 process.cpp process.h
Created with   : Visual studio 2015
*******************************************************************************/

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
	string fileName;
	int fileSize;
	string state;

public:
	Process(int, int);
	~Process();
	int getPID();
	int getSize();
	int getStart();
	int getEnd();
	void setFile(string,string,int);
	string retrunMode();
	string returnFile();
	int returnFileSize();
	void setStart(int);
	void setEnd(int);
	bool operator<(Process*);
};
#endif