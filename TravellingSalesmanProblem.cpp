//
// Created by barto on 03.11.18.
//

#include <stdexcept>
#include "TravellingSalesmanProblem.h"

TravellingSalesmanProblem::TravellingSalesmanProblem() {

}

void TravellingSalesmanProblem::loadDataFromFile(std::string path) {
	throw std::runtime_error("Not yet implemented!");
}

void TravellingSalesmanProblem::generateRandomData(int numberOfCities, int range) {
	throw std::runtime_error("Not yet implemented!");
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
