//
// Created by barto on 03.11.18.
//

#include <cmath>
#include "BruteForce.h"

BruteForce::BruteForce(std::shared_ptr<TravellingSalesmanProblem> TSP) : Algorithm(std::move(TSP)) {

}

std::string BruteForce::prepareToRun() {
	numberOfCities = TSP->getNumberOfCities();
	if (numberOfCities < 2) {
		throw std::runtime_error("Macierz miast jest pusta, badz zawiera tylko jedno miasto!");
	}

	std::string output;

	output += "Ilosc permitacji: ";
	output += std::to_string(static_cast<int>(round(std::tgamma(numberOfCities))));
	/**
	 * number of permutations -> (n-1)!; gamma(n) = (n-1)!
	 *
	 * gets the number of cities, calculates gamma function (explained above), result is stored as a double,
	 * rounds to int, the result of rounding is still the double, casts into int and coverts that int to string :D
	 * don't kill me, my future self xD
	 *
	 */

	return output;
}

std::string BruteForce::run() {
	numberOfCities = TSP->getNumberOfCities();
	if (numberOfCities < 2) {
		throw std::runtime_error("Macierz miast jest pusta, badz zawiera tylko jedno miasto!");
	}

	visitedVertices.clear();
	visitedVertices.resize(numberOfCities);
	currentRoute.clear();
	bestRoute.clear();

	curresntDistance = 0;
	bestDistance = INT32_MAX;

	startVertex = 0;

	enumerateSolutions(startVertex);

	if (bestRoute.empty()) {
		return "Nie znaleziono zadnej trasy!";
	}

	std::string output;


	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
	return std::__cxx11::string();
}

void BruteForce::enumerateSolutions(int vertex) {

}
