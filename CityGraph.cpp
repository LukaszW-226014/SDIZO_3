#pragma once
#include "stdafx.h"
#include "CityGraph.h"

CityGraph::CityGraph(CityGraph* source) {
	copyFrom(source);
}

void CityGraph::copyFrom(CityGraph* source) {
	this->vertexCount = source->vertexCount;
	this->edgeCount = source->edgeCount;
	matrix = new int*[vertexCount];
	for (unsigned i = 0; i < vertexCount; i++) {
		matrix[i] = new int[vertexCount];
		for (unsigned j = 0; j < vertexCount; j++) {
			matrix[i][j] = source->matrix[i][j];
		}
	}
}

//szybsza wersja dla zaincjalizowanych
void CityGraph::vertexSameCopy(CityGraph* source) {
	for (unsigned i = 0; i < vertexCount; i++) {
		memcpy(this->matrix, source->matrix, sizeof(int) * vertexCount);
	}
}

//Zwraca pierwszy napotkany wierzcholek z którym ³aczy siê podany
int CityGraph::getVertexAdj(unsigned vertex) {
	for (unsigned j = 0; j < vertexCount; j++) {
		if (matrix[vertex][j] > -1) {
			return j;
		}
	}
	return -1;
}

//sumuje nieujemne wagi
unsigned CityGraph::getDistance() {
	unsigned result = 0;
	for (unsigned i = 0; i < vertexCount; i++) {
		for (unsigned j = 0; j < vertexCount; j++) {
			if (matrix[i][j] > 0) {
				result += matrix[i][j];
			}
		}
	}
	return result;
}

void CityGraph::printMatrixGraph() {
	using namespace std;
	cout << endl;
	cout << "Macierz sasiedztwa:" << endl << endl;

	for (unsigned i = 0; i < vertexCount; i++) {
		cout << '\t';
		for (unsigned j = 0; j < vertexCount; j++) {
			cout << setw(3);
			cout << searchEdge(i, j) << "  ";
		}
		cout << endl;
	}
}

void CityGraph::printListGraph() {

	using namespace std;
	int totalLength = 0;
	cout << endl;
	cout << "Lista: " << endl;
	for (unsigned i = 0; i < vertexCount; i++) {
		cout << "Miasto "<<  i << ": \t";
		for (unsigned j = 0; j < vertexCount; j++) {
			int weight = searchEdge(i, j);
			if (weight >= 0) {
				cout << j << " (" << weight << ") ";
				totalLength += weight;
			}
		}
		cout << endl;
		
	}cout  << endl << "Laczna dlugosc drogi: " << totalLength;
}




CityGraph::CityGraph(unsigned int vertexCount) {
	this->vertexCount = vertexCount;
	edgeCount = 0;
	createMatrix();
}

CityGraph::~CityGraph() {
	deleteMatrix();
}

void CityGraph::createMatrix() {
	matrix = new int*[vertexCount];
	for (unsigned i = 0; i < vertexCount; i++) {
		matrix[i] = new int[vertexCount];
		for (unsigned j = 0; j < vertexCount; j++) {
			matrix[i][j] = -1;
		}
	}
}

void CityGraph::deleteMatrix() {
	for (unsigned i = 0; i < vertexCount; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = NULL;
}

void CityGraph::clear(unsigned vc) {
	if (matrix != NULL) {
		deleteMatrix();
	}
	edgeCount = 0;
	vertexCount = vc;
	createMatrix();
}

bool CityGraph::insertEdge(unsigned v, unsigned u, int weight) {
	if (v < vertexCount && u < vertexCount) {
		bool exist = this->exist(v, u);
		if (!exist) {
			matrix[v][u] = weight;
			edgeCount++;
		}
		return exist;
	}
	else {
		printf("zla krawedz");
		return false;
	}
}

bool CityGraph::deleteEdge(unsigned v, unsigned u) {
	if (v < vertexCount && u < vertexCount) {
		bool exist = this->exist(v, u);
		if (exist) {
			matrix[v][u] = -1;
			edgeCount--;
		}
		return exist;
	}
	else {
		printf("zla krawedz");
		return false;
	}
}

unsigned CityGraph::vertexDegree(unsigned vertex) {
	if (vertex < vertexCount) {
		int result = 0;
		for (unsigned i = 0; i < vertexCount; i++) {
			if (exist(vertex, i)) {
				result++;
			}
		}
		return result;
	}
	else {
		return -1;
	}
}

bool CityGraph::exist(unsigned v, unsigned u) {
	if (v < vertexCount && u < vertexCount) {
		return matrix[v][u] > -1;
	}
	else {
		printf("zla krawedz");
		return false;
	}
}

int CityGraph::searchEdge(unsigned v, unsigned u) {
	if (v < vertexCount && u < vertexCount) {
		return matrix[v][u];
	}
	else {
		printf("err");
		return-2;
	}

}

EdgeList* CityGraph::getSimpleAdjFor(unsigned v) {
	if (v < vertexCount) {
		EdgeList *result = new EdgeList();
		for (unsigned i = 0; i < vertexCount; i++) {
			if (matrix[v][i] > -1) {
				result->addAtBeginning(new Edge(v, i, matrix[v][i]));
			}
		}
		return result;
	}
	else {
		printf("err");
		return NULL;
	}
}

Edge* CityGraph::getAllEdges() {
	Edge* result = new Edge[edgeCount];
	int count = 0;
	for (unsigned i = 0; i < vertexCount; i++) {
		for (unsigned j = 0; j < vertexCount; j++) {
			if (matrix[i][j] > -1) {
				Edge e = Edge(i, j, matrix[i][j]);
				result[count] = e;
				count++;
			}
		}
	}
	return result;
}

//uzywane do algrytmu 2 opt
void CityGraph::twoOptSwap(unsigned v1, unsigned v2, CityGraph *source, CityGraph* map) {
	int *route = new int[vertexCount];
	route[0] = 0;
	for (unsigned i = 1; i < vertexCount; i++) { //tablica kolejnych wierzcho³ków
		route[i] = getVertexAdj(route[i - 1]);
	}
	for (unsigned i = v1, j = 0; i <= v2/2; i++, j++) { //odwracamy kolejnosc od v1 do v2
		int tmp = route[i];
		route[i] = route[v2 - j];
		route[v2 - j] = tmp;
	}
	clear(vertexCount);

	//przepisujemy na graf
	for (unsigned i = 0; i < vertexCount - 1; i++) {
		matrix[route[i]][route[i + 1]] = map->matrix[route[i]][route[i + 1]];
	}
	matrix[route[vertexCount - 1]][route[0]] = map->matrix[route[vertexCount - 1]][route[0]];

	delete[] route;
}