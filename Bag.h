#pragma once
#include "stdafx.h"
#include "BagItemList.h"

/* Klasa reprezentuj¹ca plecak */
class Bag {
public:
	unsigned getMaxWeight() { return maxWeight; }
	unsigned getCurrValue() { return currValue; }
	unsigned getCurrWeight() { return currWeight; }
	bool isOverloaded() { return maxWeight < currWeight; };
	void addItem(BagItem*);

	Bag(unsigned);
	~Bag();
	void showContents();
	bool isEmpty() { return bagItemList->getSize() == 0; }
	void clear();
public:
	unsigned maxWeight;
	unsigned currValue;
	unsigned currWeight;

	BagItemList* bagItemList;
};