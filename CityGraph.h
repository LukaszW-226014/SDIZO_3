#pragma once
#include "stdafx.h"
#include "Edge.h"
#include "EdgeList.h"

/** implementacja grafu jako macierz s¹siedztwa dla komiwojazera*/
class CityGraph {
public:
	unsigned getVertexCount(void) { return vertexCount; }
	unsigned getEdgeCount(void) { return edgeCount; }

	void printListGraph(void);
	void printMatrixGraph(void);
	void generateGraph(const unsigned int, float, const int, const int);
	void twoOptSwap(unsigned, unsigned, CityGraph*, CityGraph*);
	CityGraph(unsigned int);
	CityGraph(CityGraph*);
	~CityGraph();
	bool insertEdge(unsigned int, unsigned int, int);
	void clear(unsigned);
	void createMatrix(void);
	void deleteMatrix(void);
	Edge* getAllEdges(void);
	bool deleteEdge(unsigned, unsigned);
	unsigned vertexDegree(unsigned);
	int searchEdge(unsigned, unsigned);
	EdgeList* getSimpleAdjFor(unsigned);
	bool exist(unsigned, unsigned);
	unsigned getDistance();
	void copyFrom(CityGraph*); 
	void vertexSameCopy(CityGraph*);
	int getVertexAdj(unsigned);
private:
	unsigned int vertexCount;
	unsigned int edgeCount;
	int** matrix;
};