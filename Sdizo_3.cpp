#pragma once
#include "stdafx.h"
#include "TspProblem.h"
#include "KnapsackProblem.h"
#include "Timer.h"
#include "Time.h"

void testKnapsack() {
	using namespace std;
	//int items[] = { 1000, 2000, 5000, 10000, 12000 };
	int items[] = { 5,10,15,17,20,22,25,30 };
	//int sizes[] = { 100, 500, 1000 };
	int sizes[] = { 10,20,30 };
	int times[] = { 10, 10, 10, 10, 10, 10, 10, 10 };
	int itemsLength = sizeof(items)/sizeof(int);
	int sizesLegth = sizeof(sizes) / sizeof(int);
	fstream fileF("knapsackFull.txt", ios_base::app);
	fstream fileG("knapsackGreedy.txt", ios_base::app);
	KnapsackProblem *knapsack = new KnapsackProblem();
	Bag* result = NULL;
	for (int i = 0; i < itemsLength; i++) {
		for (int j = 0; j < sizesLegth; j++) {
			knapsack->generateBagItems(items[i], sizes[j], 50, 20);
			Timer *timerF = new Timer();
			Timer *timerG = new Timer();
			for (int k = 0; k < times[i]; k++) {
				timerG->startTimer();
				knapsack->doGreedyAlgoritm();
				timerG->stopTimer();
				result = knapsack->getKnapsack();

				timerG->nextMeasure();
				cout << items[i] << " - " << sizes[j] << " - " << k << endl;
			}

			fileG << items[i] << " - " << sizes[j] << " - " << timerG->getAvgTime() << endl;
			fileG.flush();
			delete timerG;
		}
	}
	fileG.close();
	delete knapsack;
	knapsack = new KnapsackProblem();
	result = NULL;
	for (int i = 0; i < itemsLength; i++) {
		for (int j = 0; j < sizesLegth; j++) {
			knapsack->generateBagItems(items[i], sizes[j], 50, 20);
			Timer *timerF = new Timer();
			for (int k = 0; k < times[i]; k++) {
				timerF->startTimer();
				knapsack->doFullCheckAlgoritm();
				timerF->stopTimer();
				result = knapsack->getKnapsack();


				timerF->nextMeasure();
				cout << items[i] << " - " << sizes[j] << " - " << k << endl;
			}

			fileF << items[i] << " - " << sizes[j] << " - " << timerF->getAvgTime() << endl;
			fileF.flush();
			delete timerF;
		}
	}
	delete knapsack;
	fileF.close();
}

void testTsp() {
	using namespace std;
	//int cities[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	//int times[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	//int cities[] = {20,50,100,1000};
	int cities[] = { 5,6,7,8,9,10,11,12 };
	//int times[] = {10, 10, 10, 10, 10};
	//int cities[] = { 10, 50, 75, 100, 200,  500, 1000 };
	int times[] = { 10,10,10,10,10,10,10,10 };
	int citiesLength = sizeof(cities) / sizeof(int);


	fstream fileF("tspFull.txt", ios_base::app);
	fstream fileG("tspGreedy.txt", ios_base::app);
	TspProblem *tsp = new TspProblem();
	CityGraph *graph = NULL;
	for (int i = 0; i < citiesLength; i++) {
		tsp->generateCityGraph(cities[i], 100);
		Timer *timerG = new Timer();
		for (int k = 0; k < times[i]; k++) {
			timerG->startTimer();
			tsp->doGreedyAlgoritm();
			timerG->stopTimer();
			graph = tsp->getWay();
;
			timerG->nextMeasure();
			cout << cities[i] << " - " << k << " Time: " << timerG->getAvgTime() << "s " << endl;
		}
		fileG << cities[i] << '\t' << timerG->getAvgTime() << endl;

		fileG.flush();
		delete timerG;
	}
	fileG.close();
	delete tsp;
	tsp = new TspProblem();
	graph = NULL;
	for (int i = 0; i < citiesLength; i++) {
		tsp->generateCityGraph(cities[i], 100);
		Timer *timerF = new Timer();
		for (int k = 0; k < times[i]; k++) {
			timerF->startTimer();
			tsp->doFullCheckAlgoritm();
			timerF->stopTimer();
			graph = tsp->getWay();
		

			timerF->nextMeasure();
			cout << cities[i] << " - " << k << " Time: " << timerF->getAvgTime() << "s " << endl;
		}
		fileF << cities[i] << '\t' << timerF->getAvgTime() << endl;
		fileF.flush();
		delete timerF;
	}
	delete tsp;
	fileF.close();
}

void presentation() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int problem = -1;
	using namespace std;

	char ch;
	int tmp, tmp2, tmp3, tmp4;
	Time timeOfOperation;
	TspProblem *tsp = new TspProblem();
	KnapsackProblem *knapsack = new KnapsackProblem();

	do {
		Timer *timer = new Timer();
		if(problem == 1) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout <<endl <<  "[PROBLEM KOMIWOJAZERA]" << endl << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "OPCJE:" << endl;
			SetConsoleTextAttribute(hConsole, 7);
				cout << "1. Wczytaj z pliku" << endl
				<< "2. Generowanie miast" << endl
				<< "3. Pokaz miasta i odleglosci" << endl << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "ALGORYTMY:" << endl;
			SetConsoleTextAttribute(hConsole, 7);
					cout << "4. Przeglad zupelny" << endl
					<< "5. Algorytm zachlanny" << endl
					<< "6. Wyjscie" << endl;
			cin >> ch;

			switch(ch) {
				case'1':
					tsp->loadCityGraph();
					system("cls");
					break;
				case'2':
					cout << "Ilosc miast: " << endl;
					cin >> tmp;
					cout << "Max odleglosc: " << endl;
					cin >> tmp2;
					tsp->generateCityGraph(tmp, tmp2);
					system("cls");
					break;
				case'3':
					tsp->getCitiesMap()->printMatrixGraph();
					tsp->getCitiesMap()->printListGraph();
					break;
				case'4':
					timeOfOperation.counter = 0;
					timeOfOperation.timeStart();
					tsp->doFullCheckAlgoritm();
					tsp->getWay()->printMatrixGraph();
					tsp->getWay()->printListGraph();
					timeOfOperation.timeTake();
					break;
				case'5':
					timeOfOperation.counter = 0;
					timeOfOperation.timeStart();
					tsp->doGreedyAlgoritm();
					tsp->getWay()->printMatrixGraph();
					tsp->getWay()->printListGraph();
					timeOfOperation.timeTake();
					break;
				case'6':
					problem = -1;
					system("cls");
					break;
				default:
					cout << "Zly wybor!" << endl;
					continue;
			}
		} else if(problem == 2) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << endl << "[Problem Plecakowy]" << endl << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "OPCJE:" << endl;
			SetConsoleTextAttribute(hConsole, 7);
				cout << "1. Wczytaj z pliku" << endl
				<< "2. Generowanie przedmiotów" << endl
				<< "3. Pokaz przedmioty" << endl << endl;
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "ALGORYTMY:" << endl;
				SetConsoleTextAttribute(hConsole, 7);
				cout << "4. Przeglad zupelny" << endl
				<< "5. Algorytm zachlanny" << endl
				<< "6. Wyjscie" << endl;

			cin >> ch;
			switch(ch) {
				case'1':
					knapsack->loadBagItems();
					system("cls");
					break;
				case'2':
					cout << "Ilosc rzeczy: " << endl;
					cin >> tmp;
					cout << "Pojemnosc plecaka: " << endl;
					cin >> tmp2;
					cout << "Max ciezar: " << endl;
					cin >> tmp3;
					cout << "Max wartosc: " << endl;
					cin >> tmp4;
					knapsack->generateBagItems(tmp, tmp2, tmp3, tmp4);
					system("cls");
					break;
				case'3':
					knapsack->printItems();
					break;
				case'4':
					timeOfOperation.counter = 0;
					timeOfOperation.timeStart();
					knapsack->doFullCheckAlgoritm();
					knapsack->printKnapsack();
					timeOfOperation.timeTake();
					break;
				case'5':
					timeOfOperation.counter = 0;
					timeOfOperation.timeStart();
					knapsack->doGreedyAlgoritm();
					knapsack->printKnapsack();
					timeOfOperation.timeTake();
					break;
				case'6':
					problem = -1;
					system("cls");
					break;
				default:
					cout << "Zly wybor!" << endl;
					continue;
			}
		} else {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << endl<<"PROBLEMY:" << endl <<endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "1. Problem komiwojazera" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "2. Problem plecakowy" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "3. Testy" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "4. Wyjscie" << endl;
			SetConsoleTextAttribute(hConsole, 7);
			cin >> ch;
			system("cls");
			switch(ch) {
				case '1':
					problem = 1;
					break;
				case '2':
					problem = 2;
					break;
				/*case '3':
					cout << "1. Plecakowy" << endl
						<< "2. Komiwojazer" << endl;
					cin >> ch;
					switch (ch)
					{
					case 1:
						testKnapsack();
						break;
					case 2:
						testTsp();
						break;
					default:
						break;
					}

					break;*/
				case '4':
					problem = -2;
					break;
				default:
					cout << "Zly wybor!" << endl;
					continue;
			}
		}
	} while(problem > -2);
	delete knapsack;
	delete tsp;
}




int _tmain(int argc, _TCHAR* argv[]) {
	presentation();
	//testTsp();
	//testKnapsack();
	return 0;
}
