#pragma once
#include "stdafx.h"
/** Klasa mierz¹ca czasy wykonania algorytmów*/
class Timer {
private:
	LARGE_INTEGER performanceCountStart;
	LARGE_INTEGER performanceCountEnd;
	LARGE_INTEGER cumulativeSum;
	int count;
	double freq;
	void setFreq();
public:
	Timer(void);
	~Timer(void);
	void startTimer(void);
	void stopTimer(void);
	void nextMeasure(void);
	void printTime(void);
	void printAvgTime(void);
	double getAvgTime(void);
};