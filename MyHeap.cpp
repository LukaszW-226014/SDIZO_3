#pragma once
#include "stdafx.h"
#include "MyHeap.h"


MyHeap::MyHeap(void) {
	baseArray = new int[0];
	valueArray = new int[0];
	size = 0;
}

MyHeap::~MyHeap(void) {
	if(baseArray != NULL) {
		delete[] baseArray;
		delete[] valueArray;
		baseArray = NULL;
	}
}

int MyHeap::pop() {
	if(size > 0) {
		int result = valueArray[0];
		size--;
		baseArray[0] = baseArray[size];
		valueArray[0] = valueArray[size];
		int* newBaseArray = new int[size];
		int* newValueArray = new int[size];
		memmove(newBaseArray, baseArray, size * sizeof(int));
		memmove(newValueArray, valueArray, size * sizeof(int));
		delete[] baseArray;
		delete[] valueArray;
		baseArray = newBaseArray;
		valueArray = newValueArray;
		fixHeapDown(0);
		return result;
	} else {
		std::cerr<<"Empty heap"<<std::endl;
		return -1;
	}
}

void MyHeap::push(int key, int value) {
	int* newBaseArray = new int[size + 1];
	int* newValueArray = new int[size + 1];
	memmove(newBaseArray, baseArray, size * sizeof(int));
	delete[] baseArray;
	baseArray = newBaseArray;
	memmove(newValueArray, valueArray, size * sizeof(int));
	delete[] valueArray;
	valueArray = newValueArray;
	int parentIndex = getParentIndex(size);
	int childIndex = size;
	size++;
	while(parentIndex != -1 && baseArray[parentIndex] > key) {
		baseArray[childIndex] = baseArray[parentIndex];
		valueArray[childIndex] = valueArray[parentIndex];
		childIndex = parentIndex;
		parentIndex = getParentIndex(parentIndex);
	}
	baseArray[childIndex] = key;
	valueArray[childIndex] = value;
}

int MyHeap::getKey(const int& value) {
	int savedSize = size;
	while(size > 0) {
		int key = baseArray[0];
		int val = valueArray[0];
		if(val == value) {
			int result = baseArray[0];
			size = savedSize;
			fixHeapUp();
			return result;
		} else {
			size--;
			baseArray[0] = baseArray[size];
			baseArray[size] = key;
			valueArray[0] = valueArray[size];
			valueArray[size] = val;
			fixHeapDown(0);
		}
	}
	size = savedSize;
	return -1; //nie znaleziono, napis wyciêto z powodu wydajnoœci cout
}

int MyHeap::getParentIndex(int index) { 
	if(index > 0) {
		return (index - 1) / 2; 
	} else {
		return -1;
	}
}

void MyHeap::fixHeapDown(const unsigned int& index) {
	unsigned int leftChildIndex = getLeftChildIndex(index);
	unsigned int rightChildIndex = getRightChildIndex(index);
	unsigned int minValueIndex = index;
	if(leftChildIndex < size && baseArray[minValueIndex] > baseArray[leftChildIndex]) {
		minValueIndex = leftChildIndex;
	}
	if(rightChildIndex < size && baseArray[minValueIndex] > baseArray[rightChildIndex]) {
		minValueIndex = rightChildIndex;
	}
	if(minValueIndex != index) {
		int temp = baseArray[index];
		baseArray[index] = baseArray[minValueIndex];
		baseArray[minValueIndex] = temp;
		temp = valueArray[index];
		valueArray[index] = valueArray[minValueIndex];
		valueArray[minValueIndex] = temp;
		return fixHeapDown(minValueIndex);
	}
}

void MyHeap::fixHeapUp(void) {
	for(int i = size / 2; i >= 0; i--) {
		fixHeapDown(i);
	}
}

void MyHeap::setKey(int value, int key) {
	for (unsigned i = 0; i < size; i++) {
		if (valueArray[i] == value) {
			baseArray[i] = key;
			fixHeapUp();
			return;
		}
	}
}