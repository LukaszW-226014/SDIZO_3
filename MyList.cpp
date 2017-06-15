#pragma once
#include "stdafx.h"
#include "MyList.h"

MyList::MyList() {
	head = NULL;
	tail = NULL;
	size = 0;
}

MyList::~MyList() {
	if(head != NULL) {
		removeList();
		head = NULL;
		tail = NULL;
	}
}

/*Sprawdza, czy element jest bli¿ej lewego czy prawego koñca listy a nastêpnie iteruje*/
MyList::ListElement *MyList::getElementAt(const unsigned int index) {
	MyList::ListElement* element;
	if(index < size) {
		if(index > size / 2) {
			element = tail;
			for(unsigned int i = size - 1; i > index; i--) {
				element = element->previous;
			}
		} else {
			element = head;
			for(unsigned int i = 0; i < index; i++) {
				element = element->next;
			}
		}
		return element;
	} else {
		std::cerr<<"Bad index!"<<std::endl;
		return NULL;
	}
}
/* Osobne przypadki dla pierwszego elementu, koñca i pocz¹tku */
void MyList::add(const unsigned int index, const int value) {
	if(index > size) {
		std::cerr<<"Bad index!"<<std::endl;
	} else {
		ListElement* newElement = new ListElement(value);
		if (index == size) {
			if(tail == NULL) {
				tail = newElement;
				head = newElement;
			} else {
				tail->next = newElement;
				newElement->previous = tail;
				tail = newElement;
			}
		} else if (index == 0) {
			head->previous = newElement;
			newElement->next = head;
			head = newElement;
		} else {
			ListElement* element = getElementAt(index);
			newElement->next = element;
			newElement->previous = element->previous;
			element->previous->next = newElement;
			element->previous = newElement;
		}
		size++;
	}
}

int MyList::removeAt(const int index) {
	ListElement* element = getElementAt(index);
	return remove(element);
}

/* Osobne przypadki dla ostatniego elementu, koñca i pocz¹tku */

int MyList::remove(ListElement* element) {
	int result = INT_MIN;
	if(element != NULL) {
		result = element->value;
		if(element == tail) {
			ListElement* oldElement = tail;
			if(head != tail) {
				tail = tail->previous;
				tail->next = NULL;
			} else {
				tail = NULL;
				head = NULL;
			}
			delete oldElement;
		} else if(element == head) {
			head = element->next;
			delete head->previous;
			head->previous = NULL;
		} else {
			element->previous->next = element->next;
			element->next->previous = element->previous;
			delete element;
		}
		size--;
	}
	return result;
}


int MyList::findFirstOccurence(const int& value) {
	ListElement* element = head;
	for(unsigned int i = 0; i < size; i++) {
		if(element->value == value) {
			return i;
		}
		element = element->next;
	}
	return -1;
}

void MyList::removeList(void) {
	ListElement* element = head;
	while(element != NULL) {
		ListElement* oldElement = element;
		element = element->next;
		delete oldElement;
	}
}

int MyList::removeFirstOccurence(const int& value) {
	ListElement* element = head;
	for(unsigned int i = 0; i < size; i++) {
		if(element->value == value) {
			return i;
		}
		element = element->next;
	}
	std::cerr<<"Not found!"<<std::endl;
	return -1;
}