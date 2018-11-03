//
// Created by barto on 29.10.18.
//

#include "Program.h"

void Program::start() {
	char selection = 0;

	do {
		printMenu();

		std::cin>>selection;
		std::cout<<std::endl;

		switch (selection) {
			case '1':
				// TSP.loadFile();
				break;
			case '2':
				// TSP.generate;
				break;
			case '3':
				// TSP.print;
				break;
			case '4':
				// BF.start();
				break;
			case '5':
				//BnB.start();
				break;
			case '9':
				std::cout<<"Not so fast xD"<<std::endl;
				break;
			case '0':
				std::cout<<"Program zostanie zamkniety!"<<std::endl;
				break;
			default:
				std::cerr<<"Wybrana opcja nie istnieje!"<<std::endl;
				break;
		}
	} while (selection != '0');
}

void Program::printMenu() {
	std::cout<<std::endl<<std::endl<<std::endl;
	std::cout<<"--- TRAVELLING SALESMAN PROBLEM ---"<<std::endl;
	std::cout<<"1. Wczytaj macierz miast z pliku"<<std::endl;
	std::cout<<"2. Generuj losowa macierz miast"<<std::endl;
	std::cout<<"3. Wyswietl macierz miast"<<std::endl;
	std::cout<<"4. Uruchom algorytm Brute-force"<<std::endl;
	std::cout<<"5. Uruchom algorytm Branch and bound"<<std::endl;
	std::cout<<"9. Testy"<<std::endl;
	std::cout<<"0. Wyjscie"<<std::endl;
	std::cout<<"Wybor: ";
}
