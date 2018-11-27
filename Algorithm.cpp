//
// Created by barto on 03.11.18.
//

#include "Algorithm.h"

Algorithm::Algorithm(std::shared_ptr<TravellingSalesmanProblem> TSP) : TSP(std::move(TSP)) {}

Algorithm::~Algorithm() = default;

void Algorithm::prepareToRun() {
	numberOfChecks = 0;

	numberOfCities = TSP->getNumberOfCities();
	if (numberOfCities < 2) {
		throw std::runtime_error("Macierz miast jest pusta, bądź zawiera tylko jedno miasto!");
	}

	currentRoute.clear();
	bestRoute.clear();

	currentDistance = 0;
	bestDistance = INT32_MAX;

	startVertex = 0;
}
