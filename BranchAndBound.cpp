//
// Created by barto on 03.11.18.
//

#include <cmath>
#include "BranchAndBound.h"

BranchAndBound::BranchAndBound(std::shared_ptr<TravellingSalesmanProblem> TSP) : BruteForce(std::move(TSP)) {}

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

				temp = (lowestDistancesToVertices[vertex][1] + lowestDistancesToVertices[i][0]) / 2;

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

	currentLowerBound = (currentLowerBound / 2);
}

void BranchAndBound::prepareToRun() {
	BruteForce::prepareToRun();

	currentLowerBound = 0;

	calculateStartingLowerBound();
}
