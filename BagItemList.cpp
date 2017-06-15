#pragma once
#include "stdafx.h"
#include "BagItemList.h"
#include "Bag.h"


void BagItemList::addItem(BagItem* item) {
	if (head == NULL) {
		head = new BagItemNode(item);
	} else {
		BagItemNode* tmp = head;
		head = new BagItemNode(item);
		head->next = tmp;
	}
	size++;
}

BagItemList::~BagItemList() {
	while (head != NULL) {
		BagItemNode *tmp = head;
		head = head->next;
		delete tmp;
	}
	head = NULL;
}

void BagItemList::printBag() {
	using namespace std;
	int fullWeight = 0;
	int fullValue = 0;
	BagItemNode *tmp = head;
	cout << endl << "Lista rzeczy:" << endl;
	while (tmp != NULL) {
		tmp->value->showItem();
		fullValue += tmp->value->getValue();
		fullWeight += tmp->value->getWeight();
		tmp = tmp->next;
	}
	cout << endl << "Laczna waga przedmiotow: " << fullWeight << ", Laczna wartosc: " << fullValue << endl;
}