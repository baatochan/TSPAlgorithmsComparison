//
// Created by barto on 03.11.18.
//

#include "BruteForce.h"

#include <cmath>

BruteForce::BruteForce(std::shared_ptr<TravellingSalesmanProblem> TSP) : Algorithm(std::move(TSP)) {}

std::string BruteForce::showInfoBeforeRunning() {
	numberOfCities = TSP->getNumberOfCities();
	if (numberOfCities < 2) {
		throw std::runtime_error("Macierz miast jest pusta, bądź zawiera tylko jedno miasto!");
	}

	std::string output;

	output += "Ilość permutacji: ";
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

std::string BruteForce::run() {
	prepareToRun();

	startTime = std::chrono::high_resolution_clock::now();

	enumerateSolutions(startVertex);

	endTime = std::chrono::high_resolution_clock::now();

	return generateOutput();
}

void BruteForce::prepareToRun() {
	numberOfChecks = 0;

	numberOfCities = TSP->getNumberOfCities();
	if (numberOfCities < 2) {
		throw std::runtime_error("Macierz miast jest pusta, bądź zawiera tylko jedno miasto!");
	}

	visitedVertices.clear();
	visitedVertices.resize(numberOfCities);
	currentRoute.clear();
	bestRoute.clear();

	currentDistance = 0;
	bestDistance = INT32_MAX;

	startVertex = 0;
}

void BruteForce::enumerateSolutions(int vertex) {
	currentRoute.push_back(vertex);
	visitedVertices[vertex] = true;

	if (currentRoute.size() < numberOfCities) {
		takeCareOfNode(vertex);
	} else { // currentRoute.size() == numberOfCities
		takeCareOfLeaf(vertex);
	}

	visitedVertices[vertex] = false;
	currentRoute.pop_back();
}

void BruteForce::takeCareOfNode(int currentVertex) {
	for (int i = 0; i < numberOfCities; ++i) {
		if (!visitedVertices[i]) {
			int distanceToNext = TSP->getDistance(currentVertex, i);

			if (distanceToNext < 0) {
				continue;
			}

			currentDistance += distanceToNext;

			enumerateSolutions(i);

			currentDistance -= distanceToNext;
		}
	}
}

void BruteForce::takeCareOfLeaf(int currentVertex) {
	numberOfChecks++;

	int distanceToNext = TSP->getDistance(currentVertex, startVertex);

	if (distanceToNext < 0) {
		return;
	}

	currentDistance += distanceToNext;

	if (currentDistance < bestDistance) {
		bestDistance = currentDistance;
		bestRoute = currentRoute;
	}
	currentDistance -= distanceToNext;
}

std::string BruteForce::generateOutput() {
	std::string output;

	output += "Ilość sprawdzonych permutacji: ";
	output += std::to_string(numberOfChecks);
	output += "\n";

	output += "Długość pracy algorytmu: ";
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	output += std::to_string(duration);
	output += "µs";
	output += "\n";

	if (bestRoute.empty()) {
		output += "Nie znaleziono żadnej trasy!\n";
	} else {
		output += "Najlepsza droga: ";

		for (auto city : bestRoute) {
			output += std::to_string(city);
			output += " - ";
		}

		output += std::to_string(bestRoute[0]);
		output += "\n";

		output += "Długość najlepszej drogi: ";
		output += std::to_string(bestDistance);
		output += "\n";
	}

	return output;
}
