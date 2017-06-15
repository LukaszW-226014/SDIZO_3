#ifndef Time_h
#define Time_h

#include <iostream>
#include <windows.h>

using namespace std;

class Time
{
public:
	double PCFreq;
	__int64 counter;
	double tmp;

	Time();
	~Time();

	void timeStart();

	void timeTake();
};

#endif