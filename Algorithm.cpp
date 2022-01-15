//
// Created by barto on 03.11.18.
//

#include <random>
#include <stdexcept>
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

int Algorithm::calculateRouteDistance(std::vector<int> &route) {
	int currentVertex = -1;
	int nextVertex = -1;

	int distance = 0;

	for (int i = 0; i < route.size(); ++i) {
		currentVertex = route[i];
		if (i != route.size() - 1) {
			nextVertex = route[i + 1];
		} else {
			nextVertex = route[0];
		}

		distance += TSP->getDistance(currentVertex, nextVertex);
	}

	return distance;
}

std::vector<int> Algorithm::generateRandomRoute() {
	std::vector<bool> visitedVertices;
	std::vector<int> route;

	visitedVertices.clear();
	visitedVertices.resize(numberOfCities);

	route.clear();

	int currentVertex = startVertex;
	route.push_back(currentVertex);
	visitedVertices[currentVertex] = true;

	int nextVertex = -1;

	std::random_device seed;
	std::mt19937 randomGenerator(seed());
	std::uniform_int_distribution<> rangeTransformer(0, numberOfCities - 1);

	for (int i = 0; i < numberOfCities - 1; ++i) {
		do {
			nextVertex = rangeTransformer(randomGenerator);
		} while (visitedVertices[nextVertex]);

		currentVertex = nextVertex;

		route.push_back(currentVertex);
		visitedVertices[currentVertex] = true;
	}

	return route;
}
