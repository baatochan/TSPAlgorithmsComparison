//
// Created by barto on 27.11.18.
//

#include <algorithm>
#include "TabuSearch.h"

TabuSearch::TabuSearch(std::shared_ptr<TravellingSalesmanProblem> TSP) : Algorithm(std::move(TSP)) {}

TabuSearch::~TabuSearch() = default;

std::string TabuSearch::showInfoBeforeRunning() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
	return std::__cxx11::string();
}

std::string TabuSearch::run() {
	prepareToRun();

	startTime = std::chrono::high_resolution_clock::now();

	generateStartRoute();

	endTime = std::chrono::high_resolution_clock::now();

	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
	return generateOutput();
}

void TabuSearch::prepareToRun() {
	Algorithm::prepareToRun();

	tabuList.clear();

	iterationWithoutChangingNeighborhood = 0;

	// load default setting TODO: take care of it in UI
	cadency = numberOfCities/2;
	timeToBreakSearch = 10; //seconds
	aspiration = true;
	iterationsToChangeNeighborhood = 10000;
}

void TabuSearch::generateStartRoute() {
	std::vector<bool> visitedVertices;

	visitedVertices.clear();
	visitedVertices.resize(numberOfCities);

	int currentVertex = startVertex;
	currentRoute.push_back(currentVertex);
	visitedVertices[currentVertex] = true;

	for (int i = 0; i < numberOfCities - 1; ++i) {
		std::vector<std::pair<int, int>> distancesFromCurrentVertex;

		for (int j = 0; j < numberOfCities; ++j) {
			if (j == currentVertex)
				continue;

			distancesFromCurrentVertex.emplace_back(std::make_pair(TSP->getDistance(currentVertex, j), j));
		}

		std::sort(distancesFromCurrentVertex.begin(), distancesFromCurrentVertex.end());

		for (auto &k : distancesFromCurrentVertex) {
			if (visitedVertices[k.second]) {
				continue;
			} else { // if not visited
				currentVertex = k.second;
				break;
			}
		}

		currentRoute.push_back(currentVertex);
		visitedVertices[currentVertex] = true;
	}
}

std::string TabuSearch::generateOutput() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
	return std::__cxx11::string();
}
