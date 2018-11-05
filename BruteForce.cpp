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
	output += "\n";

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

	output += "Najlepsza droga: ";

	for (auto city : bestRoute) {
		output += std::to_string(city);
		output += " - ";
	}

	output += std::to_string(bestRoute[0]);
	output += "\n";

	output += "Dlugosc najlepszej drogi: ";
	output += std::to_string(bestDistance);
	output += "\n";

	return output;
}

void BruteForce::enumerateSolutions(int vertex) {
	currentRoute.push_back(vertex);

	int distanceToNext;

	if (currentRoute.size() < numberOfCities) {
		visitedVertices[vertex] = true;

		for (int i = 0; i < numberOfCities; ++i) {
			if (!visitedVertices[i]) {
				distanceToNext = TSP->getDistance(vertex, i);

				if (distanceToNext < 1) {
					continue;
				}

				curresntDistance += distanceToNext;

				enumerateSolutions(i);

				curresntDistance -= distanceToNext;
			}
		}

		visitedVertices[vertex] = false;
	} else { // currentRoute.size() == numberOfCities
		distanceToNext = TSP->getDistance(vertex, startVertex);

		if (distanceToNext < 1) {
			currentRoute.pop_back();
			return;
		}

		curresntDistance += distanceToNext;

		if (curresntDistance < bestDistance) {
			bestDistance = curresntDistance;
			bestRoute = currentRoute;
		}
		curresntDistance -= distanceToNext;
	}

	currentRoute.pop_back();
}
