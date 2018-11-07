//
// Created by barto on 07.11.18.
//

#include "Test.h"

Test::Test() : TSP(std::make_shared<TravellingSalesmanProblem>()), BF(TSP), BnB(TSP) {}

void Test::openFile() {
	std::string path = "../wyniki/";
	path += "test-";
	path += std::to_string(time(0));
	path += ".txt";

	outputFile.open(path, std::fstream::out);

	if (!outputFile.is_open()) {
		throw std::runtime_error("Nie mozna otworzyc pliku (sprawdz czy istnieje katalog wyniki)!");
	}

	outputFile.setf(std::ios::fixed);
}

void Test::closeFile() {
	outputFile.close();
}

std::string Test::test1() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
}

std::string Test::test2() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
}

std::string Test::test3() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
}

std::string Test::test4() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
}

std::string Test::test5() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
}

std::string Test::test6() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
}

std::string Test::test7() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
}

std::string Test::test8() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
}

std::string Test::test9() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
}

std::string Test::getTestName(char test) {
	switch (test) {
		case '1':
			return "Not yet implemented!";

		case '2':
			return "Not yet implemented!";

		case '3':
			return "Not yet implemented!";

		case '4':
			return "Not yet implemented!";

		case '5':
			return "Not yet implemented!";

		case '6':
			return "Not yet implemented!";

		case '7':
			return "Not yet implemented!";

		case '8':
			return "Not yet implemented!";

		case '9':
			return "Not yet implemented!";

		default:
			return "";
	}
}
