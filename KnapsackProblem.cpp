#pragma once
#include "stdafx.h"
#include "KnapsackProblem.h"
#include <random>
#include <stdint.h>

KnapsackProblem::KnapsackProblem() {
	knapsack = NULL;
	itemsList = NULL;
	itemsListSize = 0;
}
KnapsackProblem::~KnapsackProblem() {
	if (knapsack != NULL) {
		delete knapsack;
		knapsack = NULL;
	}
	if (itemsList != NULL) {
		delete itemsList;
		itemsList = NULL;
	}
}

void KnapsackProblem::printKnapsack() {
	using namespace std;
	cout << endl;
	cout << "Zawartosc plecaka:" << endl;
	knapsack->showContents();
	cout << endl << "Pojemnosc plecaka:" <<
		knapsack->getMaxWeight() << endl;
}

void KnapsackProblem::printItems() {
	using namespace std;
	cout << endl;
	for (unsigned i = 0; i < itemsListSize; i++){
		cout << "P[" << i << "]: ";
		itemsList[i].showItem();
	}
}

//Algorytm typu "Brute force"
void KnapsackProblem::doFullCheckAlgoritm() {
	if (!knapsack->isEmpty()) {
		knapsack->clear();
	}
	uint64_t table = 1;
	uint64_t bestTable = 0; //zapisuje na 64 bitowym polu - 1 bit reprezentuje 1 rzecz
	uint64_t endOfTable = (table << itemsListSize);
	unsigned bestValue = 0;
	while (table < endOfTable) { //dopoki mamy mozliwosc
		uint64_t tmp = 1;
		unsigned tmpValue = 0;
		unsigned tmpWeight = 0; //dodajemy rzeczy, gdy ich bity sa w stanei wysokim
		for (unsigned i = 0; i < itemsListSize; i++) {
			bool isSet = table & tmp;
			if (isSet) {
				tmpWeight += itemsList[i].getWeight();
				tmpValue += itemsList[i].getValue();
			}
			tmp = tmp << 1;
		}
		//sprawdzamy czy lepszy
		if (tmpWeight <= knapsack->getMaxWeight() && tmpValue > bestValue) {
			bestTable = table;
			bestValue = tmpValue;
		}
		table += 1;
	}
	//przepisujemy graf
	uint64_t tmp = 1;
	for (unsigned i = 0; i < itemsListSize; i++) {
		bool isSet = bestTable & tmp;
		if (isSet) {
			knapsack->addItem(&itemsList[i]);
		}
		tmp = tmp << 1; //przesuwamy maske
	}
}

void KnapsackProblem::doGreedyAlgoritm() {

	if (!knapsack->isEmpty()) {
		knapsack->clear();
	}

	sortItems();
	//rzeczy jest zawsze wiecej niz pojemnosc plecaka
	for (unsigned i = 0; i < itemsListSize; i++) {
		if (itemsList[i].getWeight() + knapsack->getCurrWeight() < knapsack->getMaxWeight()) {
			knapsack->addItem(&itemsList[i]);
		}
	}
}

// Zamiana rzeczy
void swap(BagItem &first, BagItem &second) {
	BagItem tmp = first;
	first = second;
	second = tmp;
}
//Insertion sort
void KnapsackProblem::sortItems() {
	for (unsigned i = 0; i < itemsListSize; i++) {
		unsigned j = i + 1;
		while (j > 0) {
			if (itemsList[j].getValueDensity() > itemsList[j - 1].getValueDensity()) {
				swap(itemsList[j], itemsList[j - 1]);
			}
			j--;
		}
	}
}

unsigned maximum(unsigned a, unsigned b) {
	unsigned result = a;
	if (b > a) { 
		result = b; 
	} 
	return result;
}

//³aduje z pliku
void KnapsackProblem::loadBagItems() {
	using namespace std;
	char patch[64];
	cout << "Sciezka: ";
	cin >> patch;
	fstream file(patch, ios_base::in);
	int pojemnosc, liczba;
	file >> pojemnosc;
	file >> liczba;
	if (itemsList != NULL) {
		delete[] itemsList;
	}
	itemsList = new BagItem[liczba];
	itemsListSize = liczba;
	if (knapsack != NULL) {
		delete knapsack;
	}
	knapsack = new Bag(pojemnosc);
	unsigned waga, wartosc, i = 0;
	while (file >> waga) {
		file >> wartosc;
		itemsList[i] = BagItem(waga, wartosc);
		i++;
	}
	file.close();
}

//generuje
void KnapsackProblem::generateBagItems(unsigned liczba, unsigned pojemnosc, unsigned maxWaga, unsigned maxWartosc) {
	using namespace std;
	if (itemsList != NULL) {
		delete[] itemsList;
	}
	itemsList = new BagItem[liczba];
	itemsListSize = liczba;
	if (knapsack != NULL) {
		delete knapsack;
	}
	knapsack = new Bag(pojemnosc);
	random_device rand_dev;
	mt19937 generator(rand_dev());
	uniform_int_distribution<int> weightDistr(1, maxWaga);
	uniform_int_distribution<int> valueDistr(1, maxWartosc);
	for (unsigned i = 0; i < liczba; i++) {
		itemsList[i] = BagItem(weightDistr(generator), valueDistr(generator));
	}
}