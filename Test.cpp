//
// Created by barto on 07.11.18.
//

#include "Test.h"
#include "BranchAndBound.h"

#include <sstream>
#include <chrono>

Test::Test() : TSP(std::make_shared<TravellingSalesmanProblem>()) {}

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
	int maxCityNumber = 12;
	char testNumber = '1';

	algorithm = new BruteForce(TSP);

	std::string output = testTemplate(numberOfTests, maxCityNumber, testNumber);

	delete algorithm;

	return output;
}

std::string Test::test2() {
	int numberOfTests = 10;
	int maxCityNumber = 20;
	char testNumber = '2';

	algorithm = new BranchAndBound(TSP);

	std::string output = testTemplate(numberOfTests, maxCityNumber, testNumber);

	delete algorithm;

	return output;
}

std::string Test::test3() {
	int numberOfTests = 1;
	int maxCityNumber = 13;
	char testNumber = '3';

	algorithm = new BruteForce(TSP);

	std::string output = testTemplate(numberOfTests, maxCityNumber, testNumber);

	delete algorithm;

	return output;
}

std::string Test::test4() {
	int numberOfTests = 1;
	int maxCityNumber = 25;
	char testNumber = '4';

	algorithm = new BranchAndBound(TSP);

	std::string output = testTemplate(numberOfTests, maxCityNumber, testNumber);

	delete algorithm;

	return output;
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
			return "Brute force (3-12 miast) x10";

		case '2':
			return "Branch and bound (3-20 miast) x10";

		case '3':
			return "Brute force (3-13 miast) x1";

		case '4':
			return "Branch and bound (3-25 miast) x1";

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

std::string Test::testTemplate(int numberOfTests, int cityRange, char testNumber) {
	std::stringstream outputConsole;
	outputConsole.setf(std::ios::fixed);

	outputFile << "--- " << getTestName(testNumber) << " ---" << std::endl;
	outputConsole << "--- " << getTestName(testNumber) << " ---" << std::endl;

	for (unsigned long numberOfCities = 3; numberOfCities <= cityRange; ++numberOfCities) {
		outputFile << "Ilość miast: " << numberOfCities << std::endl;
		outputConsole << "Ilość miast: " << numberOfCities << std::endl;

		int sumOfResults = 0;

		for (int i = 0; i < numberOfTests; ++i) {
			try {
				TSP->generateRandomData(numberOfCities, 30);

				outputConsole << "Test " << i << " - ";

				std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
				algorithm->run();
				std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();

				auto result = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

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
