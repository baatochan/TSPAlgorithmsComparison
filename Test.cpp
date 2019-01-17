//
// Created by barto on 07.11.18.
//

#include "Test.h"
#include "BranchAndBound.h"

#include <sstream>
#include <chrono>
#include <utility>

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

std::string Test::testA() {
	std::stringstream outputConsole;
	outputConsole.setf(std::ios::fixed);

	outputFile << "--- " << getTestName('6') << " ---" << std::endl;
	outputConsole << "--- " << getTestName('6') << " ---" << std::endl;

	algorithm = new BranchAndBound(TSP);

	for (int i = 0; i < 10; ++i) {
		auto startTime = std::chrono::high_resolution_clock::now();
		exactTestTemplateOnFiles(7);
		auto endTime = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

		outputFile << duration << std::endl;
		outputConsole << duration << std::endl;
	}

	outputFile << "--- " << getTestName('9') << " ---" << std::endl;
	outputConsole << "--- " << getTestName('9') << " ---" << std::endl;

	for (int i = 0; i < 10; ++i) {
		auto startTime = std::chrono::high_resolution_clock::now();
		TSTestTemplateOnSmallFiles(0.01);
		auto endTime = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

		outputFile << duration << std::endl;
		outputConsole << duration << std::endl;
	}

	delete algorithm;

	return outputConsole.str();
}

std::string Test::testB() {
	return TSTestTemplateOnBigFiles("../tests/atsp/data34.txt", 'B');
}

std::string Test::testC() {
	return TSTestTemplateOnBigFiles("../tests/tsp/data58.txt", 'C');
}

std::string Test::testD() {
	return TSTestTemplateOnBigFiles("../tests/atsp/data171.txt", 'D');
}

std::string Test::testE() {
	return TSTestTemplateOnBigFiles("../tests/atsp/data443.txt", 'E');
}

std::string Test::testF() {
	std::string output;

	auto startTime = std::chrono::high_resolution_clock::now();

	output += testB();
	output += "\n";

	output += testC();
	output += "\n";

	output += testD();
	output += "\n";

	output += testE();
	output += "\n";

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::minutes>(endTime - startTime).count();

	output += "\nCZAS PRACY CAŁOŚCI: " + std::to_string(duration) + "\n";
	outputFile << std::endl << "CZAS PRACY CAŁOŚCI: " << duration << std::endl;

	return output;
}

std::string Test::testG() {
	return GenTestTemplateOnBigFiles("../tests/atsp/data34.txt", 'G');
}

std::string Test::testH() {
	return GenTestTemplateOnBigFiles("../tests/tsp/data58.txt", 'H');
}

std::string Test::testI() {
	return GenTestTemplateOnBigFiles("../tests/atsp/data171.txt", 'I');
}

std::string Test::testJ() {
	return GenTestTemplateOnBigFiles("../tests/atsp/data443.txt", 'J');
}

std::string Test::testK() {
	std::string output;

	auto startTime = std::chrono::high_resolution_clock::now();

	output += testG();
	output += "\n";

	output += testH();
	output += "\n";

	output += testI();
	output += "\n";

	output += testJ();
	output += "\n";

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::minutes>(endTime - startTime).count();

	output += "\nCZAS PRACY CAŁOŚCI: " + std::to_string(duration) + "\n";
	outputFile << std::endl << "CZAS PRACY CAŁOŚCI: " << duration << std::endl;

	return output;
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

		case 'A':
			return "(Branch and bound (test z plików) x1) vs (Tabu Search (test z małych plików) (0.01s) x1) x10";

		case 'B':
			return "Tabu Search - porównanie parametrów dla ATSP34";

		case 'C':
			return "Tabu Search - porównanie parametrów dla STSP58";

		case 'D':
			return "Tabu Search - porównanie parametrów dla ATSP171";

		case 'E':
			return "Tabu Search - porównanie parametrów dla ATSP443";

		case 'F':
			return "Testy B, C, D i E po kolei";

		case 'G':
			return "Genetic - porównanie parametrów dla ATSP34";

		case 'H':
			return "Genetic - porównanie parametrów dla STSP58";

		case 'I':
			return "Genetic - porównanie parametrów dla ATSP171";

		case 'J':
			return "Genetic - porównanie parametrów dla ATSP443";

		case 'K':
			return "Testy G, H, I i J po kolei";

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
					break;
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
					break;
				}
			}
		}

		temp.erase(temp.begin(), temp.begin() + cutPosition + 1);

		output += temp;

		output += "POPRAWNY WYNIK:                       " + std::to_string(correctValues[j]) + "\n";
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

	output += "\nIlość testów: 7, czas trwania: " + std::to_string(duration) + "\n";

	delete TS;

	return output;
}

std::string Test::TSTestTemplateOnBigFiles(std::string fileName, char testNumber) {
	std::vector<double> cadencyToTest {0.25, 0.5, 1, 2};
	std::vector<int> timeToTest {1, 5, 10, 15};
	std::vector<int> iterationsToTest {1000, 5000, 10000, 15000};

	std::stringstream outputConsole;
	outputConsole.setf(std::ios::fixed);

	outputFile << "--- " << getTestName(testNumber) << " ---" << std::endl;
	outputConsole << "--- " << getTestName(testNumber) << " ---" << std::endl;

	TSP->loadDataFromFile(std::move(fileName));

	TS = new TabuSearch(TSP);

	for (double cadencyMultiplier : cadencyToTest) {
		outputFile << "Kadencja: " << cadencyMultiplier << " * iloscMiast" << std::endl;
		outputConsole << "Kadencja: " << cadencyMultiplier << " * iloscMiast" << std::endl;

		TS->setDefaultParameters();
		TS->setCadency(static_cast<int>(cadencyMultiplier * TSP->getNumberOfCities()));

		for (int i = 0; i < 10; ++i) {
			std::string temp = TS->run();

			int numberOfNewLines = 0;
			int numberOfSpaces = 0;
			int cutPosition = 0;
			for (int k = 0; k < temp.size(); ++k) {
				if (temp[k] == '\n') {
					numberOfNewLines++;
				}
				if (numberOfNewLines == 3) {
					if (temp[k] == ' ') {
						numberOfSpaces++;
					}
				}
				if (numberOfSpaces == 4) {
					cutPosition = k + 1;
					break;
				}
			}

			temp.erase(temp.begin(), temp.begin() + cutPosition);
			temp.pop_back();

			outputFile << temp << std::endl;
			outputConsole << temp << std::endl;
		}
	}

	for (int timeToStop : timeToTest) {
		outputFile << "Czas pracy: " << timeToStop << std::endl;
		outputConsole << "Czas pracy: " << timeToStop << std::endl;

		TS->setDefaultParameters();
		TS->setTimeToBreakSearch(timeToStop);

		for (int i = 0; i < 10; ++i) {
			std::string temp = TS->run();

			int numberOfNewLines = 0;
			int numberOfSpaces = 0;
			int cutPosition = 0;
			for (int k = 0; k < temp.size(); ++k) {
				if (temp[k] == '\n') {
					numberOfNewLines++;
				}
				if (numberOfNewLines == 3) {
					if (temp[k] == ' ') {
						numberOfSpaces++;
					}
				}
				if (numberOfSpaces == 4) {
					cutPosition = k + 1;
					break;
				}
			}

			temp.erase(temp.begin(), temp.begin() + cutPosition);
			temp.pop_back();

			outputFile << temp << std::endl;
			outputConsole << temp << std::endl;
		}
	}

	for (int i = 0; i < 2; ++i) {
		outputFile << "Aspiracja: " << i << std::endl;
		outputConsole << "Aspiracja: " << i << std::endl;

		TS->setDefaultParameters();
		TS->setAspiration(i);

		for (int j = 0; j < 10; ++j) {
			std::string temp = TS->run();

			int numberOfNewLines = 0;
			int numberOfSpaces = 0;
			int cutPosition = 0;
			for (int k = 0; k < temp.size(); ++k) {
				if (temp[k] == '\n') {
					numberOfNewLines++;
				}
				if (numberOfNewLines == 3) {
					if (temp[k] == ' ') {
						numberOfSpaces++;
					}
				}
				if (numberOfSpaces == 4) {
					cutPosition = k + 1;
					break;
				}
			}

			temp.erase(temp.begin(), temp.begin() + cutPosition);
			temp.pop_back();

			outputFile << temp << std::endl;
			outputConsole << temp << std::endl;
		}
	}

	for (int i = 0; i < 2; ++i) {
		outputFile << "Dywersyfikacja: " << i << std::endl;
		outputConsole << "Dywersyfikacja: " << i << std::endl;

		TS->setDefaultParameters();
		TS->setDiversification(i);

		for (int j = 0; j < 10; ++j) {
			std::string temp = TS->run();

			int numberOfNewLines = 0;
			int numberOfSpaces = 0;
			int cutPosition = 0;
			for (int k = 0; k < temp.size(); ++k) {
				if (temp[k] == '\n') {
					numberOfNewLines++;
				}
				if (numberOfNewLines == 3) {
					if (temp[k] == ' ') {
						numberOfSpaces++;
					}
				}
				if (numberOfSpaces == 4) {
					cutPosition = k + 1;
					break;
				}
			}

			temp.erase(temp.begin(), temp.begin() + cutPosition);
			temp.pop_back();

			outputFile << temp << std::endl;
			outputConsole << temp << std::endl;
		}
	}

	for (int numberOfIterations : iterationsToTest) {
		outputFile << "Iteracje do zmiany: " << numberOfIterations << std::endl;
		outputConsole << "Iteracje do zmiany: " << numberOfIterations << std::endl;

		TS->setDefaultParameters();
		TS->setIterationsToChangeNeighborhood(numberOfIterations);

		for (int i = 0; i < 10; ++i) {
			std::string temp = TS->run();

			int numberOfNewLines = 0;
			int numberOfSpaces = 0;
			int cutPosition = 0;
			for (int k = 0; k < temp.size(); ++k) {
				if (temp[k] == '\n') {
					numberOfNewLines++;
				}
				if (numberOfNewLines == 3) {
					if (temp[k] == ' ') {
						numberOfSpaces++;
					}
				}
				if (numberOfSpaces == 4) {
					cutPosition = k + 1;
					break;
				}
			}

			temp.erase(temp.begin(), temp.begin() + cutPosition);
			temp.pop_back();

			outputFile << temp << std::endl;
			outputConsole << temp << std::endl;
		}
	}

	delete TS;

	std::string output = outputConsole.str();
	return output;
}

std::string Test::GenTestTemplateOnBigFiles(std::string fileName, char testNumber) {
	std::vector<int> timeToTest {1, 10, 30, 60};
	std::vector<int> populationToTest {10, 30, 50, 100};
	std::vector<double> crossoverToTest {0.2, 0.4, 0.8, 0.99};
	std::vector<double> mutationToTest {0.01, 0.05, 0.15, 0.50};

	std::stringstream outputConsole;
	outputConsole.setf(std::ios::fixed);

	outputFile << "--- " << getTestName(testNumber) << " ---" << std::endl;
	outputConsole << "--- " << getTestName(testNumber) << " ---" << std::endl;

	TSP->loadDataFromFile(std::move(fileName));

	Gen = new Genetic(TSP);

	for (int timeToStop : timeToTest) {
		outputFile << "Czas pracy: " << timeToStop << std::endl;
		outputConsole << "Czas pracy: " << timeToStop << std::endl;

		Gen->setDefaultParameters();
		Gen->setTimeToBreakSearch(timeToStop);

		for (int i = 0; i < 10; ++i) {
			std::string temp = Gen->run();

			int numberOfNewLines = 0;
			int numberOfSpaces = 0;
			int cutPosition = 0;
			for (int k = 0; k < temp.size(); ++k) {
				if (temp[k] == '\n') {
					numberOfNewLines++;
				}
				if (numberOfNewLines == 3) {
					if (temp[k] == ' ') {
						numberOfSpaces++;
					}
				}
				if (numberOfSpaces == 4) {
					cutPosition = k + 1;
					break;
				}
			}

			temp.erase(temp.begin(), temp.begin() + cutPosition);
			temp.pop_back();

			outputFile << temp << std::endl;
			outputConsole << temp << std::endl;
		}
	}

	for (int populationSize : populationToTest) {
		outputFile << "Wielkosc populacji: " << populationSize << std::endl;
		outputConsole << "Wielkosc populacji: " << populationSize << std::endl;

		Gen->setDefaultParameters();
		Gen->setPopulationSize(populationSize);

		for (int i = 0; i < 10; ++i) {
			std::string temp = Gen->run();

			int numberOfNewLines = 0;
			int numberOfSpaces = 0;
			int cutPosition = 0;
			for (int k = 0; k < temp.size(); ++k) {
				if (temp[k] == '\n') {
					numberOfNewLines++;
				}
				if (numberOfNewLines == 3) {
					if (temp[k] == ' ') {
						numberOfSpaces++;
					}
				}
				if (numberOfSpaces == 4) {
					cutPosition = k + 1;
					break;
				}
			}

			temp.erase(temp.begin(), temp.begin() + cutPosition);
			temp.pop_back();

			outputFile << temp << std::endl;
			outputConsole << temp << std::endl;
		}
	}

	for (double crossoverCoefficient : crossoverToTest) {
		outputFile << "Wspolczynnik krzyzowania: " << crossoverCoefficient << std::endl;
		outputConsole << "Wspolczynnik krzyzowania: " << crossoverCoefficient << std::endl;

		Gen->setDefaultParameters();
		Gen->setCrossoverCoefficient(crossoverCoefficient);

		for (int i = 0; i < 10; ++i) {
			std::string temp = Gen->run();

			int numberOfNewLines = 0;
			int numberOfSpaces = 0;
			int cutPosition = 0;
			for (int k = 0; k < temp.size(); ++k) {
				if (temp[k] == '\n') {
					numberOfNewLines++;
				}
				if (numberOfNewLines == 3) {
					if (temp[k] == ' ') {
						numberOfSpaces++;
					}
				}
				if (numberOfSpaces == 4) {
					cutPosition = k + 1;
					break;
				}
			}

			temp.erase(temp.begin(), temp.begin() + cutPosition);
			temp.pop_back();

			outputFile << temp << std::endl;
			outputConsole << temp << std::endl;
		}
	}

	for (double mutationCoefficient : mutationToTest) {
		outputFile << "Wspolczynnik mutacji: " << mutationCoefficient << std::endl;
		outputConsole << "Wspolczynnik mutacji: " << mutationCoefficient << std::endl;

		Gen->setDefaultParameters();
		Gen->setCrossoverCoefficient(mutationCoefficient);

		for (int i = 0; i < 10; ++i) {
			std::string temp = Gen->run();

			int numberOfNewLines = 0;
			int numberOfSpaces = 0;
			int cutPosition = 0;
			for (int k = 0; k < temp.size(); ++k) {
				if (temp[k] == '\n') {
					numberOfNewLines++;
				}
				if (numberOfNewLines == 3) {
					if (temp[k] == ' ') {
						numberOfSpaces++;
					}
				}
				if (numberOfSpaces == 4) {
					cutPosition = k + 1;
					break;
				}
			}

			temp.erase(temp.begin(), temp.begin() + cutPosition);
			temp.pop_back();

			outputFile << temp << std::endl;
			outputConsole << temp << std::endl;
		}
	}

	for (int i = 0; i < 2; ++i) {
		outputFile << "Rob mutacje poprzez zamiane krawedzi (0 false, 1 true): " << i << std::endl;
		outputConsole << "Rob mutacje poprzez zamiane krawedzi (0 false, 1 true): " << i << std::endl;

		Gen->setDefaultParameters();
		Gen->setUseEdgeMutation(i);

		for (int j = 0; j < 10; ++j) {
			std::string temp = Gen->run();

			int numberOfNewLines = 0;
			int numberOfSpaces = 0;
			int cutPosition = 0;
			for (int k = 0; k < temp.size(); ++k) {
				if (temp[k] == '\n') {
					numberOfNewLines++;
				}
				if (numberOfNewLines == 3) {
					if (temp[k] == ' ') {
						numberOfSpaces++;
					}
				}
				if (numberOfSpaces == 4) {
					cutPosition = k + 1;
					break;
				}
			}

			temp.erase(temp.begin(), temp.begin() + cutPosition);
			temp.pop_back();

			outputFile << temp << std::endl;
			outputConsole << temp << std::endl;
		}
	}

	delete Gen;

	std::string output = outputConsole.str();
	return output;
}
