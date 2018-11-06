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
	numberOfChecks = 0;

	numberOfCities = TSP->getNumberOfCities();
	if (numberOfCities < 2) {
		throw std::runtime_error("Macierz miast jest pusta, badz zawiera tylko jedno miasto!");
	}

	visitedVertices.clear();
	visitedVertices.resize(numberOfCities);
	currentRoute.clear();
	bestRoute.clear();

	currentDistance = 0;
	bestDistance = INT32_MAX;

	startVertex = 0;

	currentLowerBound = 0;

	calculateStartingLowerBound();

	enumerateSolutions(startVertex);

	std::string output;

	output += "Ilosc sprawdoznych permutacji: ";
	output += std::to_string(numberOfChecks);
	output += "\n";

	if (bestRoute.empty()) {
		output += "Nie znaleziono zadnej trasy!\n";
	} else {
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
	}

	return output;
}

void BranchAndBound::enumerateSolutions(int vertex) {
	currentRoute.push_back(vertex);

	int distanceToNext;

	if (currentRoute.size() < numberOfCities) {
		visitedVertices[vertex] = true;

		for (int i = 0; i < numberOfCities; ++i) {
			if (!visitedVertices[i]) {
				distanceToNext = TSP->getDistance(vertex, i);

				if (distanceToNext < 0) {
					continue;
				}

				int tempLowerBound = currentLowerBound;

				int temp;

				temp = lowestDistancesToVertices[vertex][1] + lowestDistancesToVertices[i][0];
				temp = (temp / 2) + (temp % 2);

				currentLowerBound -= temp;

				currentDistance += distanceToNext;

				if (currentDistance + currentLowerBound < bestDistance) {
					enumerateSolutions(i);
				}

				currentDistance -= distanceToNext;

				currentLowerBound = tempLowerBound;
			}
		}

		visitedVertices[vertex] = false;
	} else { // currentRoute.size() == numberOfCities
		numberOfChecks++;

		distanceToNext = TSP->getDistance(vertex, startVertex);

		if (distanceToNext < 0) {
			currentRoute.pop_back();
			return;
		}

		currentDistance += distanceToNext;

		if (currentDistance < bestDistance) {
			bestDistance = currentDistance;
			bestRoute = currentRoute;
		}
		currentDistance -= distanceToNext;
	}

	currentRoute.pop_back();
}

void BranchAndBound::calculateStartingLowerBound() {
	lowestDistancesToVertices.clear();
	lowestDistancesToVertices.resize(numberOfCities);

	int temp;

	for (int i = 0; i < numberOfCities; ++i) {
		temp = TSP->getMinimumDistanceTo(i);
		lowestDistancesToVertices[i].push_back(temp);
		currentLowerBound += temp;

		temp = TSP->getMinimumDistanceFrom(i);
		lowestDistancesToVertices[i].push_back(temp);
		currentLowerBound += temp;
	}

	currentLowerBound = (currentLowerBound / 2) + (currentLowerBound % 2);
}
