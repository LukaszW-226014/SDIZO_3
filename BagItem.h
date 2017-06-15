#pragma once
#include "stdafx.h"

/* Klasa odpowiadajaca za element który mo¿na wsadziæ do plecaka*/
class BagItem {
public:
	unsigned getWeight() { return weight;  }
	unsigned getValue() { return value; }
	float getValueDensity() { return valueDensity; }
	
	BagItem(unsigned weight, unsigned value) {
		this->value = value;
		this->weight = weight;
		valueDensity = (float)value / (float)weight;
	}
	BagItem() {
		this->value = 0;
		this->weight = 0;
		valueDensity = 0;
	}
	void showItem() {
		using namespace std;
		cout << " Wartosc: " << value << " Waga: " << weight << " Gestosc: " << valueDensity << endl;
	}
private:
	float valueDensity;
	unsigned weight;
	unsigned value;
};