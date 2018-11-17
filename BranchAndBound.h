//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H
#define TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H


#include "BruteForce.h"

class BranchAndBound : public BruteForce {
public:
	BranchAndBound(std::shared_ptr<TravellingSalesmanProblem> TSP);

private:
	int currentLowerBound;

	std::vector<std::vector<int>> lowestDistancesToVertices;

	void prepareToRun() override;

	void enumerateSolutions(int vertex) override;

	void calculateStartingLowerBound();

};


#endif //TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H
