#pragma once
#include "stdafx.h"
#include "Edge.h"
/** Struktura reprezentuj¹ca list krawêdzy*/
class EdgeList {
private:
	struct EdgeNode {
		Edge *value;
		EdgeNode* next;
		EdgeNode(int vertex2, int weight) {
			value = new Edge(-1, vertex2, weight); //-1 oznacza krawêdŸ podan¹ w polu vertex
			next = NULL;
		}
		EdgeNode(Edge *e) {
			value = e;
			next = NULL;
		}
		~EdgeNode() {
			if (value != NULL) {
				delete value;
				value = NULL;
			}
		}
	};
	EdgeNode* head;
	int vertex;
	unsigned int size;
public:
	inline unsigned getSize() { return size; }
	Edge *pop(unsigned);
	EdgeList() {}
	EdgeList(int);
	EdgeList(EdgeList*);
	~EdgeList();
	void removeList(void);
	void add(unsigned int, int);
	void add(Edge *edge);
	void addAtBeginning(Edge *edge);
	bool exist(unsigned);
	bool remove(unsigned);
	Edge* getVal(unsigned);
	Edge* getAt(unsigned);
};