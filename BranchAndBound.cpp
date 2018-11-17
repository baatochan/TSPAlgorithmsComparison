//
// Created by barto on 03.11.18.
//

#include "BranchAndBound.h"

BranchAndBound::BranchAndBound(std::shared_ptr<TravellingSalesmanProblem> TSP) : BruteForce(std::move(TSP)) {}

BranchAndBound::~BranchAndBound() = default;

void BranchAndBound::prepareToRun() {
	BruteForce::prepareToRun();

	currentLowerBound = 0;

	calculateStartingLowerBound();
}

void BranchAndBound::takeCareOfNode(int currentVertex) {
	for (int i = 0; i < numberOfCities; ++i) {
		if (!visitedVertices[i]) {
			int distanceToNext = TSP->getDistance(currentVertex, i);

			if (distanceToNext < 0) {
				continue;
			}

			int tempLowerBound = currentLowerBound;

			currentLowerBound -= (lowestDistancesToVertices[currentVertex][1] + lowestDistancesToVertices[i][0]) / 2;

			currentDistance += distanceToNext;

			if (currentDistance + currentLowerBound < bestDistance) {
				enumerateSolutions(i);
			}

			currentDistance -= distanceToNext;

			currentLowerBound = tempLowerBound;
		}
	}
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
