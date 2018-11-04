//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_BRUTEFORCE_H
#define TSPALGORITHMSCOMPARISON_BRUTEFORCE_H


#include "Algorithm.h"

class BruteForce : public Algorithm {
public:
	BruteForce(std::shared_ptr<TravellingSalesmanProblem> TSP);

	std::string prepareToRun() override;

	std::string run() override;

private:
	std::vector<bool> visitedVertices;

	std::vector<int> currentRoute;
	std::vector<int> bestRoute;

	int curresntDistance;
	int bestDistance;

	void enumerateSolutions(int vertex);

};


#endif //TSPALGORITHMSCOMPARISON_BRUTEFORCE_H
