//
// Created by barto on 03.11.18.
//

#include <cmath>
#include "BranchAndBound.h"

BranchAndBound::BranchAndBound(std::shared_ptr<TravellingSalesmanProblem> TSP) : Algorithm(std::move(TSP)) {}

std::string BranchAndBound::prepareToRun() {
	numberOfCities = TSP->getNumberOfCities();
	if (numberOfCities < 2) {
		throw std::runtime_error("Macierz miast jest pusta, badz zawiera tylko jedno miasto!");
	}

	std::string output;

	output += "Ilosc permitacji: ";
	output += std::to_string(static_cast<unsigned long>(round(std::tgamma(numberOfCities))));
	/**
	 * number of permutations -> (n-1)!; gamma(n) = (n-1)!
	 *
	 * gets the number of cities, calculates gamma function (explained above), result is stored as a double,
	 * rounds to int, the result of rounding is still the double, casts into int and coverts that int to string :D
	 * don't kill me, my future self xD
	 *
	 */
	output += "\n";

	return output;
}

std::string BranchAndBound::run() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
	return std::__cxx11::string();
}

void BranchAndBound::calculateStartingLowerBound() {
	lowestDistancesToVertices.clear();
	lowestDistancesToVertices.resize(numberOfCities);

	int temp;

	for (int i = 0; i < numberOfCities; ++i) {
		temp = TSP->getMinimumDistanceTo(i);
		lowestDistancesToVertices[i].push_back(temp);
		currentLowerBound += temp;

		temp = TSP->getSecondMinimumDistanceTo(i);
		lowestDistancesToVertices[i].push_back(temp);
		currentLowerBound += temp;
	}

	currentLowerBound = (currentLowerBound/2) + (currentLowerBound%2);
}
