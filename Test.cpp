//
// Created by barto on 07.11.18.
//

#include <sstream>
#include <chrono>
#include "Test.h"

Test::Test() : TSP(std::make_shared<TravellingSalesmanProblem>()), BF(TSP), BnB(TSP) {}

void Test::openFile() {
	std::string path = "../wyniki/";
	path += "test-";
	path += std::to_string(time(nullptr));
	path += ".txt";

	outputFile.open(path, std::fstream::out);

	if (!outputFile.is_open()) {
		throw std::runtime_error("Nie można otworzyć pliku (sprawdź, czy istnieje katalog wyniki)!");
	}

	outputFile.setf(std::ios::fixed);
}

void Test::closeFile() {
	outputFile.close();
}

std::string Test::test1() {
	int numberOfTests = 10;

	std::ostringstream outputConsole;
	outputConsole.setf(std::ios::fixed);

	outputFile << "--- " << getTestName('1') << " ---" << std::endl;
	outputConsole << "--- " << getTestName('1') << " ---" << std::endl;

	for (int numberOfCities = 3; numberOfCities <= 12; ++numberOfCities) {
		outputFile << "BF " << numberOfCities << std::endl;
		outputConsole << "BF " << numberOfCities << std::endl;

		int sumOfResults = 0;

		for (int i = 0; i < numberOfTests; ++i) {
			try {
				TSP->generateRandomData(numberOfCities, 30);

				outputConsole << "Test: " << i << " - ";

				auto start_time = std::chrono::high_resolution_clock::now();
				BF.run();
				auto end_time = std::chrono::high_resolution_clock::now();

				auto result = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

				outputFile << result << std::endl;
				outputConsole << result << std::endl;

				sumOfResults += result;
			} catch (const std::runtime_error &e) {
				i--;
				outputConsole << e.what() << std::endl;
			}
		}

		sumOfResults /= numberOfTests;

		outputFile << sumOfResults << std::endl;
		outputConsole << "Średnia: " << sumOfResults << std::endl;
	}

	std::string output = outputConsole.str();
	return output;
}

std::string Test::test2() {
	int numberOfTests = 10;

	std::ostringstream outputConsole;
	outputConsole.setf(std::ios::fixed);

	outputFile << "--- " << getTestName('2') << " ---" << std::endl;
	outputConsole << "--- " << getTestName('2') << " ---" << std::endl;

	for (int numberOfCities = 3; numberOfCities <= 20; ++numberOfCities) {
		outputFile << "BnB " << numberOfCities << std::endl;
		outputConsole << "BnB " << numberOfCities << std::endl;

		int sumOfResults = 0;

		for (int i = 0; i < numberOfTests; ++i) {
			try {
				TSP->generateRandomData(numberOfCities, 30);

				outputConsole << "Test: " << i << " - ";

				auto start_time = std::chrono::high_resolution_clock::now();
				BnB.run();
				auto end_time = std::chrono::high_resolution_clock::now();

				auto result = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

				outputFile << result << std::endl;
				outputConsole << result << std::endl;

				sumOfResults += result;
			} catch (const std::runtime_error &e) {
				i--;
				outputConsole << e.what() << std::endl;
			}
		}

		sumOfResults /= numberOfTests;

		outputFile << sumOfResults << std::endl;
		outputConsole << "Średnia: " << sumOfResults << std::endl;
	}

	std::string output = outputConsole.str();
	return output;
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
			return "Brute force (3-12 miast)";

		case '2':
			return "Branch and bound (3-20 miast)";

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
