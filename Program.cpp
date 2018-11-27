//
// Created by barto on 29.10.18.
//

#include "Program.h"

#include <limits>

Program::Program() : TSP(std::make_shared<TravellingSalesmanProblem>()), BF(TSP), BnB(TSP), TS(TSP) {}

void Program::start() {
	char selection = 0;
	std::string path;
	unsigned long numberOfCities = 0;
	int range = 0;
	std::string output;

	do {
		printMenu();

		std::cin >> selection;
		std::cout << std::endl;

		switch (selection) {
			case '1':
				printFileWarning();
				std::cout << "Podaj ścieżkę pliku do wczytania danych: ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				getline(std::cin, path);

				try {
					TSP->loadDataFromFile(path);
					TS.setDefaultParameters();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '2':
				do {
					std::cout << "Podaj ilość miast: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				} while (!(std::cin >> numberOfCities));
				do {
					std::cout << "Podaj zakres maksymalnej długości drogi (0 - zakres]: ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				} while (!(std::cin >> range));

				try {
					TSP->generateRandomData(numberOfCities, range);
					TS.setDefaultParameters();
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
					output = BF.showInfoBeforeRunning();
					std::cout << output << std::endl;

					output = BF.run();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '5':
				try {
					output = BnB.showInfoBeforeRunning();
					std::cout << output << std::endl;

					output = BnB.run();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '6':
				try {
					runTSSettingsMenu();
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '7':
				try {
					output = TS.showInfoBeforeRunning();
					std::cout << output << std::endl;

					output = TS.run();
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
				std::cout << "Program zostanie zamknięty!" << std::endl;
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
	std::cout << "3. Wyświetl macierz miast" << std::endl;
	std::cout << "4. Uruchom algorytm Brute-force" << std::endl;
	std::cout << "5. Uruchom algorytm Branch and bound" << std::endl;
	std::cout << "6. Zmień ustawienia algorytmu Tabu Search" << std::endl;
	std::cout << "7. Uruchom algorytm Tabu Search" << std::endl;
	std::cout << "9. Testy" << std::endl;
	std::cout << "0. Wyjście" << std::endl;
	std::cout << "Wybór: ";
}

void Program::printFileWarning() {
	std::cout << "Program nie wykonuje sprawdzania danych w pliku wejściowym!" << std::endl;
	std::cout << "Upewnij sie ze jest on napisany zgodnie z poniższym schematem:" << std::endl;
	std::cout << "Pierwsza linijka to pojedyncza liczba (całkowita, dodatnia, różna od zera) oznaczająca ilość miast."
	          << std::endl;
	std::cout
			<< "Kolejne linijki to macierz X na X (X = liczba z pierwszej linijki), kolejne liczby w linijce oddzielone spacja, zawierające odległości pomiędzy miastami (całkowite, dodatnie, różne od zera). Przekątna macierzy zawiera liczby -1."
			<< std::endl << std::endl;
	std::cout << "Przykładowy plik:" << std::endl;
	std::cout << "3" << std::endl << "-1 10 15" << std::endl << "20 -1 5" << std::endl << "25 30 -1" << std::endl
	          << std::endl << std::endl;
}

void Program::runTestMenu() {
	test.openFile();

	char selection = 0;
	std::string output;

	do {
		printTestMenu();

		std::cin >> selection;
		std::cout << std::endl;

		switch (selection) {
			case '1':
				try {
					output = test.test1();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '2':
				try {
					output = test.test2();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '3':
				try {
					output = test.test3();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '4':
				try {
					output = test.test4();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '5':
				try {
					output = test.test5();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '6':
				try {
					output = test.test6();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '7':
				try {
					output = test.test7();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '8':
				try {
					output = test.test8();
					std::cout << output << std::endl;
				} catch (const std::runtime_error &e) {
					std::cerr << e.what() << std::endl;
				}
				break;

			case '9':
				try {
					output = test.test9();
					std::cout << output << std::endl;
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
	std::cout << "0. Powrót" << std::endl;
	std::cout << "Wybór: ";
}

void Program::runTSSettingsMenu() {
	char selection = 0;
	std::string output;
	double tempDouble = 0;
	char tempChar;
	int tempInt = 0;

	do {
		printTSSettingsMenu();

		std::cin >> selection;
		std::cout << std::endl;

		switch (selection) {
			case '1':
				TS.setDefaultParameters();
				break;

			case '2':
				do {
					std::cout
							<< "Podaj mnożnik do długości kadencji, który zostanie przemnożony przez ilość miast (liczba wymierna): ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				} while (!(std::cin >> tempDouble));
				TS.setCadency(static_cast<int>(tempDouble * TSP->getNumberOfCities()));
				break;

			case '3':
				do {
					std::cout << "Podaj czas wykonywania algorytmu w sekundach (liczba wymierna): ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				} while (!(std::cin >> tempDouble));
				TS.setTimeToBreakSearch(tempDouble);
				break;

			case '4':
				do {
					do {
						std::cout << "Czy aspiracja ma być włączona [y/n]: ";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					} while (!(std::cin >> tempChar));
				} while (tempChar == 'y' || tempChar == 'Y' || tempChar == 't' || tempChar == 'T' || tempChar == 'n' ||
				         tempChar == 'N');

				if (tempChar == 'y' || tempChar == 'Y' || tempChar == 't' || tempChar == 'T') {
					TS.setAspiration(true);
				} else {
					TS.setAspiration(false);
				}
				break;

			case '5':
				do {
					do {
						std::cout << "Czy dywersyfikacja ma być włączona [y/n]: ";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					} while (!(std::cin >> tempChar));
				} while (tempChar == 'y' || tempChar == 'Y' || tempChar == 't' || tempChar == 'T' || tempChar == 'n' ||
				         tempChar == 'N');

				if (tempChar == 'y' || tempChar == 'Y' || tempChar == 't' || tempChar == 'T') {
					TS.setDiversification(true);
				} else {
					TS.setDiversification(false);
				}
				break;

			case '6':
				do {
					std::cout << "Podaj ilosc iteracji do zmiany otoczenia (liczba calkowita): ";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				} while (!(std::cin >> tempInt));
				TS.setIterationsToChangeNeighborhood(tempInt);
				break;

			case '0':
				break;

			default:
				std::cerr << "Wybrana opcja nie istnieje!" << std::endl;
				break;

		}

	} while (selection != '0');
}

void Program::printTSSettingsMenu() {
	std::cout << "--- Ustawienia algorytmu Tabu Search ---" << std::endl;
	std::cout << "Algorytm Tabu Search posiada kilka ustawień, które możesz tutaj zmienić:" << std::endl;
	std::cout
			<< "* Długość kadencji ruchu na liście tabu (przez taką ilość operacji ruch jest zabroniony); domyślnie 0.5 * ilosc_miast"
			<< std::endl;
	std::cout
			<< "* Czas wykonywania algorytmu (po takim czasie algorytm zostanie przerwany i zwróci najlepsze dotąd znalezione rozwiązanie; domyślnie 10s"
			<< std::endl;
	std::cout
			<< "* Aspiracja (czy algorytm powinien zezwolić na zakazany ruch, jeśli poprawia on najlepsze znalezione rozwiązanie; domyślnie TAK"
			<< std::endl;
	std::cout
			<< "* Dywersyfikacja (czy algorytm powinien zmienić otoczenie w którym szuka, jeśli przez jakąś ilość operacji nie znalazł lepszego wyniku; domyślnie TAK"
			<< std::endl;
	std::cout
			<< "* Ilość iteracji do zmiany otoczenia (jeśli dywersyfikacja jest aktywna to po tylu iteracjach nastąpi zmiana otoczenia na nowe, losowe); domyślnie 10 tys."
			<< std::endl;
	std::cout << std::endl;
	std::cout << "Aktualne ustawienia:" << std::endl;
	std::cout << "* Długość kadencji ruchu na liście tabu: " << TS.getCadency() << " (ilość miast: "
	          << TSP->getNumberOfCities() << ")" << std::endl;
	std::cout << "* Czas wykonywania algorytmu: " << TS.getTimeToBreakSearch() << " (s)" << std::endl;
	std::cout << "* Aspiracja: ";
	if (TS.isAspiration()) {
		std::cout << "TAK" << std::endl;
	} else {
		std::cout << "NIE" << std::endl;
	}
	std::cout << "* Dywersyfikacja: ";
	if (TS.isDiversification()) {
		std::cout << "TAK" << std::endl;
	} else {
		std::cout << "NIE" << std::endl;
	}
	std::cout << "* Ilość iteracji do zmiany otoczenia: " << TS.getIterationsToChangeNeighborhood() << std::endl;
	std::cout << std::endl;
	std::cout << "1. Wczytaj domyślne ustawienia" << std::endl;
	std::cout << "2. Zmień długość kadencji" << std::endl;
	std::cout << "3. Zmień czas wykonywania algorytmu" << std::endl;
	std::cout << "4. Zmień ustawienie aspiracji" << std::endl;
	std::cout << "5. Zmień ustawienie dywersyfikacji" << std::endl;
	std::cout << "6. Zmień ilość iteracji do zmiany otoczenia" << std::endl;
	std::cout << "0. Wyjście" << std::endl;
	std::cout << "Wybór: ";
}
