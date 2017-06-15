#pragma once
#include "stdafx.h"
#include "Timer.h"

Timer::Timer(void) {
	count = 0;
	freq = 0;
	cumulativeSum.QuadPart = 0;
	setFreq();
}

void Timer::setFreq() {
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "Problem z licznikiem!\n";

	freq = double(li.QuadPart);
}

Timer::~Timer(void) {

}
void Timer::startTimer(void) {
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&performanceCountStart);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
}
void Timer::stopTimer(void) {
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&performanceCountEnd);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
}

void Timer::nextMeasure(void) {
	cumulativeSum.QuadPart += performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
	count++;
}

void Timer::printTime(void)
{
	using namespace std;
	double tm = cumulativeSum.QuadPart;
	//tm /= freq;
	cout << endl << "Time:" << tm << endl;
}

void Timer::printAvgTime(void) {
	using namespace std;
	double tm = cumulativeSum.QuadPart / (double) count;
	tm /= freq;
	cout <<endl<<"Time:"<<tm <<endl;
}

double Timer::getAvgTime(void) {
	double result = double(cumulativeSum.QuadPart / (double)count);
	result /= freq;
	return  result;
}