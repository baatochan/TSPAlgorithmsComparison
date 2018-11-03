//
// Created by barto on 03.11.18.
//

#include <stdexcept>
#include <random>
#include "TravellingSalesmanProblem.h"

TravellingSalesmanProblem::TravellingSalesmanProblem() {}

void TravellingSalesmanProblem::loadDataFromFile(std::string path) {
	throw std::runtime_error("Not yet implemented!");
}

void TravellingSalesmanProblem::generateRandomData(int numberOfCities, int range) {
	if (numberOfCities < 0) {
		throw std::runtime_error("Liczba miast nie moze byc ujemna!");
	}
	if (numberOfCities == 0) {
		TSPData.clear();
		TSPData.resize(0);
		return;
	}
	if (range < 1) {
		throw std::runtime_error("Gorna granica zakresu musi byc dodatnia!");
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

	std::string output;

	output += "Ilosc miast: " + std::to_string(TSPData.size()) + "\n";

	for (auto &row : TSPData) {
		for (auto &element : row) {
			std::string temp = std::to_string(element);
			while (temp.length() < 4)
				temp = " " + temp;
			output += temp + " ";
		}
		output += "\n";
	}

	return output;
}

void TravellingSalesmanProblem::clearData() {

}
