#pragma once
#include "stdafx.h"
#include "EdgeList.h"

//wariacja listy
EdgeList::EdgeList(int vertex) {
	this->vertex = vertex;
	head = NULL;
}

EdgeList::EdgeList(EdgeList* copy) {
	EdgeNode* tmp = copy->head;
	while (tmp != NULL) {
		add(tmp->value->v2, tmp->value->weight);
		tmp = tmp->next;
	}
}

EdgeList::~EdgeList() {
	removeList();
	head = NULL;
}

void EdgeList::removeList() {
	while (head != NULL) {
		EdgeNode* tmp = head;
		head = head->next;
		delete tmp;
	}
}

void EdgeList::add(unsigned int vertex, int weight) {
	EdgeNode *newNode = new EdgeNode(vertex, weight);
	EdgeNode *tmp = head;
	EdgeNode *prev = NULL;
	while (tmp != NULL) {
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev == NULL) {
		head = newNode;
	} else {
		prev->next = newNode;
	}
	size++;
}

void EdgeList::addAtBeginning(Edge* edge) {
	EdgeNode *newNode = new EdgeNode(edge);
	newNode->next = head;
	head = newNode;
	size++;
}

void EdgeList::add(Edge* edge) {
	EdgeNode *newNode = new EdgeNode(edge);
	EdgeNode *tmp = head;
	EdgeNode *prev = NULL;
	while (tmp != NULL) {
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev == NULL) {
		head = newNode;
	}
	else {
		prev->next = newNode;
	}
	size++;
}

Edge* EdgeList::getAt(unsigned v) {
	if (v < size) {
		EdgeNode* tmp = head;
		for (unsigned i = 0; i < v; i++)  {
			tmp = tmp->next;
		}
		return tmp->value;
	} else {
		return NULL;
	}
}

Edge* EdgeList::getVal(unsigned vertex) {
	EdgeNode *tmp = head;
	while (tmp != NULL) {
		if (tmp->value->v2 != vertex) {
			tmp = tmp->next;
		} else {
			return tmp->value;
			break;
		}
	}
	return NULL;
}

bool EdgeList::remove(unsigned vertex) {
	bool result = false;
	EdgeNode *tmp = head;
	EdgeNode *prev = NULL;
	while (tmp != NULL) {
		if (tmp->value->v2 != vertex) {
			prev = tmp;
			tmp = tmp->next;
		} else {
			result = true;
			if (prev == NULL) {
				head = tmp->next;
			} else {
				prev->next = tmp->next;
			}
			delete tmp;
			size--;
			break;
		}
	}
	return result;
}

Edge* EdgeList::pop(unsigned pos) {
	EdgeNode *tmp = head;
	EdgeNode *prev = NULL;
	if (pos >= size) {
		return NULL;
	}
	for (unsigned i = 0; i < pos; i++) {
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev != NULL) {
	prev->next = tmp->next;
	} else {
		head = tmp->next;
	}
	size--;
	Edge* result = tmp->value;
	tmp->value = NULL;
	delete tmp;
	return result;
}

bool EdgeList::exist(unsigned vertex) {
	bool result = false;
	EdgeNode *tmp = head;
	while (tmp != NULL) {
		if (tmp->value->v2 != vertex) {
			tmp = tmp->next;
		} else {
			result = true;
			break;
		}
	}
	return result;
}