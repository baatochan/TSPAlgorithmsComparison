//
// Created by barto on 03.11.18.
//

#include <stdexcept>
#include <random>
#include <fstream>
#include "TravellingSalesmanProblem.h"

TravellingSalesmanProblem::TravellingSalesmanProblem() {}

void TravellingSalesmanProblem::loadDataFromFile(std::string path) {
	std::vector<int> intBuffer;

	std::fstream file(path, std::ios::in);

	if (!file.is_open())
		throw std::runtime_error("Plik nie istnieje, badz zablokowany dostep!");

	std::string temp;
	while (file >> temp) {
		try {
			intBuffer.push_back(stoi(temp));
		} catch (const std::exception &e) {
			intBuffer.clear();
			throw std::runtime_error("Bledna zawartosc pliku! Upewnij sie ze podales odpowiedni format!");
		}
	}

	if (intBuffer.empty())
		throw std::runtime_error("Plik pusty, badz bledna zawartosc!");

	int i = 0;
	int numberOfCities = intBuffer[i++];

	if (numberOfCities == 0) {
		TSPData.clear();
		TSPData.resize(0);
		return;
	}

	TSPData.clear();
	TSPData.resize(numberOfCities);

	for (auto &row : TSPData) {
		for (int j = 0; j < numberOfCities; ++j) {
			if (intBuffer.size() > i) {
				row.push_back(intBuffer[i++]);
			} else {
				throw std::runtime_error("Za krotka zawartosc pliku! Upewnij sie ze podales odpowiedni format!");
			}
		}
	}

	for (int i = 0; i < TSPData.size(); ++i) {
		TSPData[i][i] = -1;
	}
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

int TravellingSalesmanProblem::getNumberOfCities() const {
	return TSPData.size();
}

int TravellingSalesmanProblem::getDistance(int startVertex, int endVertex) const {
	if (startVertex < 0 || endVertex < 0) {
		throw std::runtime_error("Bledny indeks wierzcholka!");
	}
	if (startVertex >= TSPData.size() || endVertex >= TSPData.size()) {
		throw std::runtime_error("Wierzcholek nie istnieje!");
	}

	return TSPData[startVertex][endVertex];
}
