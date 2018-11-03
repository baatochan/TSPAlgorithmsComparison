//
// Created by barto on 29.10.18.
//

#include "Program.h"

Program::Program() : TSP(std::make_shared<TravellingSalesmanProblem>()), BF(TSP), BnB(TSP) {

}

void Program::start() {
	char selection = 0;
	std::string path;
	int numberOfCities = 0;
	int range = 0;
	std::string output;

	do {
		printMenu();

		std::cin >> selection;
		std::cout << std::endl;

		switch (selection) {
			case '1':
				std::cout << "Podaj sciezke pliku do wczytania danych: ";
				std::cin.ignore();
				getline(std::cin, path);
				TSP->loadDataFromFile(path);
				break;

			case '2':
				std::cout << "Podaj ilosc miast: ";
				std::cin >> numberOfCities;
				std::cout << "Podaj zakres maksymalnej dlugosci drogi (0 - zakres]: ";
				std::cin >> range;
				TSP->generateRandomData(numberOfCities, range);
				break;

			case '3':
				output = TSP->printData();
				std::cout << output << std::endl;
				break;

			case '4':
				output = BF.prepareToRun();
				std::cout << output << std::endl;
				output = BF.run();
				std::cout << output << std::endl;
				break;

			case '5':
				output = BnB.prepareToRun();
				std::cout << output << std::endl;
				output = BnB.run();
				std::cout << output << std::endl;
				break;

			case '9':
				std::cerr << "Not so fast xD" << std::endl;
				break;
			case '0':
				std::cout << "Program zostanie zamkniety!" << std::endl;
				break;
			default:
				std::cerr << "Wybrana opcja nie istnieje!" << std::endl;
				break;
		}
	} while (selection != '0');
}

void Program::printMenu() {
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "--- TRAVELLING SALESMAN PROBLEM ---" << std::endl;
	std::cout << "1. Wczytaj macierz miast z pliku" << std::endl;
	std::cout << "2. Generuj losowa macierz miast" << std::endl;
	std::cout << "3. Wyswietl macierz miast" << std::endl;
	std::cout << "4. Uruchom algorytm Brute-force" << std::endl;
	std::cout << "5. Uruchom algorytm Branch and bound" << std::endl;
	std::cout << "9. Testy" << std::endl;
	std::cout << "0. Wyjscie" << std::endl;
	std::cout << "Wybor: ";
}
