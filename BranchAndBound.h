//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H
#define TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H


#include "Algorithm.h"

class BranchAndBound : public Algorithm {
public:
	BranchAndBound(std::shared_ptr<TravellingSalesmanProblem> TSP);

	std::string prepareToRun() override;

	std::string run() override;

private:
	int numberOfChecks;

	int numberOfCities;

	std::vector<bool> visitedVertices;
	int startVertex;

	std::vector<int> currentRoute;
	std::vector<int> bestRoute;

	int currentDistance;
	int bestDistance;

	int currentLowerBound;

	std::vector<std::vector<int>> lowestDistancesToVertices;

	void enumerateSolutions(int vertex);

	void calculateStartingLowerBound();

};


#endif //TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H
