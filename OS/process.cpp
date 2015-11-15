/*******************************************************************************
Title          : cheng_pan-hwk1.cpp
Author         : Cheng Pan
Created on     : October 10, 2015
Description    : Simulate OS
Usage          : ./cheng_Pan-hwk1
Build with     : g++ -o cheng_Pan-hwk1 cheng_Pan-hwk1.cpp system.cpp system.h
process.cpp process .h
Modifications  :
*******************************************************************************/

#include <iostream>
#include "process.h"
using namespace std;


Process::Process(int id, int size) : PID(id), memSize(size)
{}
Process::~Process() {}

int Process::getPID()
{
	return PID;
}

int Process::getSize()
{
	return memSize;
}

int Process::getStart()
{
	return startIndex;
}

int Process::getEnd()
{
	return endIndex;
}
void Process::setStart(int index)
{
	startIndex = index;
}

void Process::setEnd(int index)
{
	endIndex = index;
}

void Process::setFile(string mode, string file, int size)
{
	state = mode;
	fileName = file;
	fileSize = size;
}
string Process::retrunMode()
{
	return state;
}
string Process::returnFile()
{
	return fileName;
}
int Process::returnFileSize()
{
	return fileSize;
}
bool Process::operator<(Process *pro)
{
	return (startIndex < pro->startIndex);
}
