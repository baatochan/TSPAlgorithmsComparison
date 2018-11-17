//
// Created by barto on 03.11.18.
//

#include "TravellingSalesmanProblem.h"

#include <stdexcept>
#include <random>
#include <fstream>
#include <sstream>
#include <iomanip>

void TravellingSalesmanProblem::loadDataFromFile(std::string path) {
	std::vector<int> intBuffer;

	std::fstream file(path, std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("Plik nie istnieje, bądź zablokowany dostęp!");

	std::string temp;
	file >> temp;
	unsigned long numberOfCities;
	try {
		numberOfCities = stoul(temp);
	} catch (const std::exception &e) {
		throw std::runtime_error("Błędna zawartość pliku! Upewnij sie ze podałeś odpowiedni format!");
	}

	while (file >> temp) {
		try {
			intBuffer.push_back(stoi(temp));
		} catch (const std::exception &e) {
			intBuffer.clear();
			throw std::runtime_error("Błędna zawartość pliku! Upewnij sie ze podałeś odpowiedni format!");
		}
	}

	if (intBuffer.empty())
		throw std::runtime_error("Plik pusty, bądź błędna zawartość!");

	if (numberOfCities == 0) {
		TSPData.clear();
		TSPData.resize(0);
		return;
	}

	TSPData.clear();
	TSPData.resize(numberOfCities);

	int i = 0;

	for (auto &row : TSPData) {
		for (int j = 0; j < numberOfCities; ++j) {
			if (intBuffer.size() > i) {
				row.push_back(intBuffer[i++]);
			} else {
				throw std::runtime_error("Za krotka zawartość pliku! Upewnij sie ze podałeś odpowiedni format!");
			}
		}
	}

	for (int j = 0; j < TSPData.size(); ++j) {
		TSPData[j][j] = -1;
	}
}

void TravellingSalesmanProblem::generateRandomData(unsigned long numberOfCities, int range) {
	if (numberOfCities < 0) {
		throw std::runtime_error("Liczba miast nie może byc ujemna!");
	}
	if (numberOfCities == 0) {
		TSPData.clear();
		TSPData.resize(0);
		return;
	}
	if (range < 1) {
		throw std::runtime_error("Górna granica zakresu musi byc dodatnia!");
	}

	std::random_device seed;
	std::mt19937 randomGenerator(seed());
	std::uniform_int_distribution<> rangeTransformer(1, range);

	TSPData.clear();
	TSPData.resize(numberOfCities);

	for (auto &row : TSPData) {
		for (int j = 0; j < numberOfCities; ++j) {
			row.push_back(rangeTransformer(randomGenerator));
		}
	}

	for (int i = 0; i < TSPData.size(); ++i) {
		TSPData[i][i] = -1;
	}
}

std::string TravellingSalesmanProblem::printData() {
	if (TSPData.empty())
		return "Macierz miast jest pusta!";

	std::stringstream output;

	output << "Ilość miast: " << TSPData.size() << std::endl << std::endl;

	output << "    | ";
	for (int i = 0; i < TSPData.size(); ++i) {
		output << std::setw(3) << i << " | ";
	}
	output << std::endl;

	output << "    -";
	for (int i = 0; i < TSPData.size(); ++i) {
		output << "------";
	}
	output << std::endl;

	int i = 0;
	for (auto &row : TSPData) {
		output << std::setw(3) << i++ << " |";
		for (auto &element : row) {
			output << std::setw(5) << element << " ";
		}
		output << std::endl;
	}

	return output.str();
}

unsigned long TravellingSalesmanProblem::getNumberOfCities() const {
	return TSPData.size();
}

int TravellingSalesmanProblem::getDistance(int startVertex, int endVertex) const {
	if (startVertex < 0 || endVertex < 0) {
		throw std::runtime_error("Błędny indeks wierzchołka!");
	}
	if (startVertex >= TSPData.size() || endVertex >= TSPData.size()) {
		throw std::runtime_error("Wierzchołek nie istnieje!");
	}

	return TSPData[startVertex][endVertex];
}

int TravellingSalesmanProblem::getMinimumDistanceFrom(int vertex) const {
	int min = INT32_MAX;

	for (int i = 0; i < TSPData.size(); ++i) {
		if (TSPData[vertex][i] < min && TSPData[vertex][i] >= 0) {
			min = TSPData[vertex][i];
		}
	}

	return min;
}

int TravellingSalesmanProblem::getMinimumDistanceTo(int vertex) const {
	int min = INT32_MAX;

	for (const auto &row : TSPData) {
		if (row[vertex] < min && row[vertex] >= 0) {
			min = row[vertex];
		}
	}

	return min;
}
