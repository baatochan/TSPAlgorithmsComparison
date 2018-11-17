//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_BRUTEFORCE_H
#define TSPALGORITHMSCOMPARISON_BRUTEFORCE_H


#include "Algorithm.h"

class BruteForce : public Algorithm {
public:
	BruteForce(std::shared_ptr<TravellingSalesmanProblem> TSP);

	std::string showInfoBeforeRunning() override;

	std::string run() override;

protected:
	int numberOfChecks;

	int numberOfCities;

	std::vector<bool> visitedVertices;
	int startVertex;

	std::vector<int> currentRoute;
	std::vector<int> bestRoute;

	int currentDistance;
	int bestDistance;

	virtual void prepareToRun();

	virtual void enumerateSolutions(int vertex);

	std::string generateOutput();

};


#endif //TSPALGORITHMSCOMPARISON_BRUTEFORCE_H
