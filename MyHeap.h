#pragma once
#include "stdafx.h"

/*Kopiec typu min z kluczem i wartoœci¹*/
class MyHeap {
private:
	int* baseArray; //tablica kluczy
	int* valueArray;
	unsigned size;
	int getParentIndex(int);
	int getLeftChildIndex(int index) { return 2*index+1; }
	int getRightChildIndex(int index) { return 2*index+2; }
	void fixHeapDown(const unsigned int&);
public:
	MyHeap(void);
	~MyHeap(void);
	int seekKey() { return baseArray[0]; }
	inline unsigned int getSize(void) { return size; }
	void fixHeapUp(void);
	int pop(void);
	void push(int key, int value);
	int getKey(const int&);
	void setKey(int, int);
};