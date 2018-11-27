//
// Created by barto on 27.11.18.
//

#include <algorithm>
#include <random>
#include "TabuSearch.h"

TabuSearch::TabuSearch(std::shared_ptr<TravellingSalesmanProblem> TSP) : Algorithm(std::move(TSP)) {}

TabuSearch::~TabuSearch() = default;

std::string TabuSearch::showInfoBeforeRunning() {
	return "";
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
}

std::string TabuSearch::run() {
	startTime = std::chrono::high_resolution_clock::now();

	prepareToRun();

	bool timeNotExceeded = true;

	while (timeNotExceeded) {
		std::tuple<int, int, int> nextTabuElement = enumerateNeighbourSolutions();

		currentDistance = calculateRouteDistance(currentRoute);

		iterationWithoutImprovement++;

		if (currentDistance < bestDistance) {
			bestDistance = currentDistance;
			bestRoute = currentRoute;

			iterationWithoutImprovement = 0;
		}

		updateTabuList();
		tabuList.push_back(nextTabuElement);

		if (diversification && iterationWithoutImprovement >= iterationsToChangeNeighborhood) {
			generateRandomRoute();
			currentDistance = calculateRouteDistance(currentRoute);
			iterationWithoutImprovement = 0;
		}

		endTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

		if (duration > timeToBreakSearch) {
			timeNotExceeded = false;
		}
	}

	endTime = std::chrono::high_resolution_clock::now();

	return generateOutput();
}

void TabuSearch::setDefaultParameters() {
	cadency = TSP->getNumberOfCities() / 2;
	timeToBreakSearch = 10; //seconds
	aspiration = true;
	diversification = true;
	iterationsToChangeNeighborhood = 10000;
}

int TabuSearch::getCadency() const {
	return cadency;
}

double TabuSearch::getTimeToBreakSearch() const {
	return timeToBreakSearch;
}

bool TabuSearch::isAspiration() const {
	return aspiration;
}

bool TabuSearch::isDiversification() const {
	return diversification;
}

int TabuSearch::getIterationsToChangeNeighborhood() const {
	return iterationsToChangeNeighborhood;
}

void TabuSearch::setCadency(int cadency) {
	TabuSearch::cadency = cadency;
}

void TabuSearch::setTimeToBreakSearch(double timeToBreakSearch) {
	TabuSearch::timeToBreakSearch = timeToBreakSearch;
}

void TabuSearch::setAspiration(bool aspiration) {
	TabuSearch::aspiration = aspiration;
}

void TabuSearch::setDiversification(bool diversification) {
	TabuSearch::diversification = diversification;
}

void TabuSearch::setIterationsToChangeNeighborhood(int iterationsToChangeNeighborhood) {
	TabuSearch::iterationsToChangeNeighborhood = iterationsToChangeNeighborhood;
}

void TabuSearch::prepareToRun() {
	Algorithm::prepareToRun();

	tabuList.clear();

	iterationWithoutImprovement = 0;

	generateStartRoute();
	currentDistance = calculateRouteDistance(currentRoute);

	bestRoute = currentRoute;
	bestDistance = currentDistance;
}

void TabuSearch::generateStartRoute() {
	std::vector<bool> visitedVertices;

	visitedVertices.clear();
	visitedVertices.resize(numberOfCities);

	currentRoute.clear();

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

int TabuSearch::calculateRouteDistance(std::vector<int> &route) {
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

std::tuple<int, int, int> TabuSearch::enumerateNeighbourSolutions() {
	std::vector<int> nextRoute;
	int nextRouteDistance = INT32_MAX;

	std::tuple<int, int, int> nextTabuElement = std::make_tuple(-1, -1, cadency);

	for (int i = 1; i < numberOfCities; ++i) {
		for (int j = i + 1; j < numberOfCities; ++j) {
			std::vector<int> neighbourRoute = currentRoute;

			bool moveInTabu = false;
			for (auto &tabuElement : tabuList) {
				if (std::get<0>(tabuElement) == i && std::get<1>(tabuElement) == j) {
					moveInTabu = true;
				}
				if (std::get<1>(tabuElement) == i && std::get<0>(tabuElement) == j) {
					moveInTabu = true;
				}
			}

			if (!aspiration && moveInTabu) {
				continue;
			}

			numberOfChecks++;

			std::swap(neighbourRoute[i], neighbourRoute[j]);

			int neighbourRouteDistance = calculateRouteDistance(neighbourRoute);

			if (aspiration && moveInTabu && neighbourRouteDistance >= bestDistance) {
				continue;
			}

			if (nextRouteDistance > neighbourRouteDistance) {
				nextRoute = neighbourRoute;
				nextRouteDistance = neighbourRouteDistance;

				std::get<0>(nextTabuElement) = i;
				std::get<1>(nextTabuElement) = j;
			}

		}
	}

	currentRoute = nextRoute;
	currentDistance = nextRouteDistance;

	return nextTabuElement;
}

void TabuSearch::updateTabuList() {
	for (auto &tabuElement : tabuList) {
		std::get<2>(tabuElement)--;
	}

	tabuList.erase(std::remove_if(tabuList.begin(),
	                              tabuList.end(),
	                              [&](const std::tuple<int,int,int> element) -> bool { return std::get<2>(element) <= 0; }),
	               tabuList.end());
}

void TabuSearch::generateRandomRoute() {
	std::vector<bool> visitedVertices;

	visitedVertices.clear();
	visitedVertices.resize(numberOfCities);

	currentRoute.clear();

	int currentVertex = startVertex;
	currentRoute.push_back(currentVertex);
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

		currentRoute.push_back(currentVertex);
		visitedVertices[currentVertex] = true;
	}

}

std::string TabuSearch::generateOutput() {
	std::string output;

	output += "Ilość sprawdzonych rozwiązań: ";
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
