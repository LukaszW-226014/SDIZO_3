#pragma once
#include "stdafx.h"
/** W³asna lisa z 1. proektu*/
class MyList {
private:
	struct ListElement {
		ListElement* next;
		ListElement* previous;
		int value;
		ListElement(int newValue) {
			value = newValue;
			previous = NULL;
			next = NULL;
		}
	};
	ListElement* head;
	ListElement* tail;
	unsigned int size;

	ListElement* getElementAt(const unsigned int);
	int remove(ListElement* element);
public:
	MyList();
	~MyList();

	
	void removeList(void);
	int removeAt(const int);
	void add(const unsigned int, const int);
	int removeFirstOccurence(const int&);
	int findFirstOccurence(const int&);
	void printStructure(void) const;
	inline int getValueAt(const unsigned int index) { return getElementAt(index)->value; }

	inline void addAtBeginning(const int value) { return add(0, value); }
	inline void addAtEnd(const int value) { return add(size, value); }
	inline int removeAtBeginning() { return removeAt(0); }
	inline int removeAtEnd() { return removeAt(size - 1); }
	inline unsigned int getSize(void) const { return size; }
};