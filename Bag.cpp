#pragma once
#include "stdafx.h"
#include "Bag.h"
#include "BagItem.h"

Bag::~Bag() {
	delete bagItemList;
	bagItemList = NULL;
}

void Bag::showContents() {
	bagItemList->printBag();
}

//dodaje do plecaka rzecz
void Bag::addItem(BagItem* item) {
	bagItemList->addItem(item);
	currValue += item->getValue();
	currWeight += item->getWeight();
}

void Bag::clear() {
	currWeight = 0;
	currValue = 0;
	delete bagItemList;
	bagItemList = new BagItemList();
}

Bag::Bag(unsigned maxWeight) {
	bagItemList = new BagItemList();
	currValue = 0;
	currWeight = 0;
	this->maxWeight = maxWeight;
}