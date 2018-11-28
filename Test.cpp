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

	std::string output = exactTestTemplateOnRandomData(numberOfTests, maxCityNumber, testNumber);

	delete algorithm;

	return output;
}

std::string Test::test2() {
	int numberOfTests = 10;
	int maxCityNumber = 20;
	char testNumber = '2';

	algorithm = new BranchAndBound(TSP);

	std::string output = exactTestTemplateOnRandomData(numberOfTests, maxCityNumber, testNumber);

	delete algorithm;

	return output;
}

std::string Test::test3() {
	int numberOfTests = 1;
	int maxCityNumber = 13;
	char testNumber = '3';

	algorithm = new BruteForce(TSP);

	std::string output = exactTestTemplateOnRandomData(numberOfTests, maxCityNumber, testNumber);

	delete algorithm;

	return output;
}

std::string Test::test4() {
	int numberOfTests = 1;
	int maxCityNumber = 25;
	char testNumber = '4';

	algorithm = new BranchAndBound(TSP);

	std::string output = exactTestTemplateOnRandomData(numberOfTests, maxCityNumber, testNumber);

	delete algorithm;

	return output;
}

std::string Test::test5() {
	algorithm = new BruteForce(TSP);

	std::string output = exactTestTemplateOnFiles(4);

	delete algorithm;

	return output;
}

std::string Test::test6() {
	algorithm = new BranchAndBound(TSP);

	std::string output = exactTestTemplateOnFiles(7);

	delete algorithm;

	return output;
}

std::string Test::test7() {
	return TSTestTemplateOnSmallFiles(10);
}

std::string Test::test8() {
	return TSTestTemplateOnSmallFiles(1);
}

std::string Test::test9() {
	return TSTestTemplateOnSmallFiles(0.01);
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
			return "Brute force (test z plików) x1";

		case '6':
			return "Branch and bound (test z plików) x1";

		case '7':
			return "Tabu Search (test z małych plików) (10s) x1";

		case '8':
			return "Tabu Search (test z małych plików) (1s) x1";

		case '9':
			return "Tabu Search (test z małych plików) (0.01s) x1";

		default:
			return "";
	}
}

std::string Test::exactTestTemplateOnRandomData(int numberOfTests, int cityRange, char testNumber) {
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

std::string Test::exactTestTemplateOnFiles(int cityRange) {
	std::vector<std::string> filePaths {"6-1.txt", "6-2.txt", "10.txt", "12.txt", "13.txt", "14.txt", "15.txt"};
	std::string pathToDir = "../tests/small/";

	std::vector<int> correctValues {132, 80, 212, 264, 269, 282, 291};

	std::string output;

	auto startTime = std::chrono::high_resolution_clock::now();

	for (int j = 0; j < cityRange; ++j) {
		TSP->loadDataFromFile(pathToDir + filePaths[j]);

		output += "\n";

		std::string temp = algorithm->run();

		int numberOfNewLines = 0;
		int cutPosition = 0;
		for (int k = 0; k < temp.size(); ++k) {
			if (temp[k] == '\n') {
				numberOfNewLines++;
				if (numberOfNewLines == 3) {
					cutPosition = k;
				}
			}
		}

		temp.erase(temp.begin(), temp.begin() + cutPosition + 1);

		output += temp;

		output += "POPRAWNY WYNIK:           " + std::to_string(correctValues[j]) + "\n";
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

	output += "\nIlość testów: " + std::to_string(cityRange) + ", czas trwania: " + std::to_string(duration) + "\n";

	return output;
}

std::string Test::TSTestTemplateOnSmallFiles(double runDuration) {
	std::vector<std::string> filePaths {"6-1.txt", "6-2.txt", "10.txt", "12.txt", "13.txt", "14.txt", "15.txt"};
	std::string pathToDir = "../tests/small/";

	std::vector<int> correctValues {132, 80, 212, 264, 269, 282, 291};

	std::string output;

	TS = new TabuSearch(TSP);

	auto startTime = std::chrono::high_resolution_clock::now();

	for (int j = 0; j < 7; ++j) {
		TSP->loadDataFromFile(pathToDir + filePaths[j]);

		TS->setDefaultParameters();
		TS->setTimeToBreakSearch(runDuration);

		output += "\n";

		std::string temp = TS->run();

		int numberOfNewLines = 0;
		int cutPosition = 0;
		for (int k = 0; k < temp.size(); ++k) {
			if (temp[k] == '\n') {
				numberOfNewLines++;
				if (numberOfNewLines == 3) {
					cutPosition = k;
				}
			}
		}

		temp.erase(temp.begin(), temp.begin() + cutPosition + 1);

		output += temp;

		output += "POPRAWNY WYNIK:           " + std::to_string(correctValues[j]) + "\n";
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

	output += "\nIlość testów: 7, czas trwania: " + std::to_string(duration) + "\n";

	delete TS;

	return output;
}
