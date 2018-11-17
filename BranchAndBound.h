//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H
#define TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H


#include "BruteForce.h"

class BranchAndBound : public BruteForce {
public:
	explicit BranchAndBound(std::shared_ptr<TravellingSalesmanProblem> TSP);

private:
	void prepareToRun() override;

	void takeCareOfNode(int currentVertex) override;

	void calculateStartingLowerBound();

	int currentLowerBound;

	std::vector<std::vector<int>> lowestDistancesToVertices;

};


#endif //TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H
