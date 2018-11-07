//
// Created by barto on 29.10.18.
//

#include <limits>
#include "Program.h"

Program::Program() : TSP(std::make_shared<TravellingSalesmanProblem>()), BF(TSP), BnB(TSP) {}

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
				printFileWarning();
				std::cout << "Podaj sciezke pliku do wczytania danych: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				getline(std::cin, path);

				try {
					TSP->loadDataFromFile(path);
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '2':
				do {
					std::cout << "Podaj ilosc miast: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				} while (!(std::cin >> numberOfCities));
				do {
					std::cout << "Podaj zakres maksymalnej dlugosci drogi (0 - zakres]: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				} while (!(std::cin >> range));

				try {
					TSP->generateRandomData(numberOfCities, range);
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '3':
				output = TSP->printData();
				std::cout << output << std::endl;
				break;

			case '4':
				try {
					output = BF.prepareToRun();
					std::cout << output << std::endl;

					output = BF.run();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '5':
				try {
					output = BnB.prepareToRun();
					std::cout << output << std::endl;

					output = BnB.run();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '9':
				try {
					runTestMenu();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
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

void Program::printFileWarning() {
	std::cout << "Program nie wykonuje sprawdzania danych w pliku wejsciowym!" << std::endl;
	std::cout << "Upewnij sie ze jest on napisany zgodnie z poniszym schematem:" << std::endl;
	std::cout << "Pierwsza linijka to pojedyncza liczba (calkowita, dodatnia, rozna od zera) oznaczajaca ilosc miast."
	          << std::endl;
	std::cout
			<< "Kolejne linijki to macierz X na X (X = liczba z pierwszej linijki), kolejne liczby w linijce oddzielone spacja, zawierajace odleglosci pomiedzy miastami (calkowite, dodatnie, rozne od zera). Przekatna macierzy zawiera liczby -1."
			<< std::endl << std::endl;
	std::cout << "Przykladowy plik:" << std::endl;
	std::cout << "3" << std::endl << "-1 10 15" << std::endl << "20 -1 5" << std::endl << "25 30 -1" << std::endl
	          << std::endl << std::endl;
}

void Program::runTestMenu() {
	test.openFile();

	char selection = 0;

	do {
		printTestMenu();

		std::cin >> selection;
		std::cout << std::endl;

		switch (selection) {
			case '1':
				try {
					test.test1();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '2':
				try {
					test.test2();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '3':
				try {
					test.test3();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '4':
				try {
					test.test4();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '5':
				try {
					test.test5();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '6':
				try {
					test.test6();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '7':
				try {
					test.test7();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '8':
				try {
					test.test8();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '9':
				try {
					test.test9();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '0':
				break;

			default:
				std::cerr << "Wybrana opcja nie istnieje!" << std::endl;
				break;
		}
	} while (selection != '0');

	test.closeFile();
}

void Program::printTestMenu() {
	std::cout << "--- TESTY ---" << std::endl;
	std::cout << "1. Test nr 1 (" << test.getTestName('1') << ")" << std::endl;
	std::cout << "2. Test nr 2 (" << test.getTestName('2') << ")" << std::endl;
	std::cout << "3. Test nr 3 (" << test.getTestName('3') << ")" << std::endl;
	std::cout << "4. Test nr 4 (" << test.getTestName('4') << ")" << std::endl;
	std::cout << "5. Test nr 5 (" << test.getTestName('5') << ")" << std::endl;
	std::cout << "6. Test nr 6 (" << test.getTestName('6') << ")" << std::endl;
	std::cout << "7. Test nr 7 (" << test.getTestName('7') << ")" << std::endl;
	std::cout << "8. Test nr 8 (" << test.getTestName('8') << ")" << std::endl;
	std::cout << "9. Test nr 9 (" << test.getTestName('9') << ")" << std::endl;
	std::cout << "0. Powrot" << std::endl;
	std::cout << "Wybor: ";
}
