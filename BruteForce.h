//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_BRUTEFORCE_H
#define TSPALGORITHMSCOMPARISON_BRUTEFORCE_H


#include "Algorithm.h"

class BruteForce : public Algorithm {
public:
	explicit BruteForce(std::shared_ptr<TravellingSalesmanProblem> TSP);

	~BruteForce() override;

	std::string showInfoBeforeRunning() override;

	std::string run() override;

protected:
	void prepareToRun() override;

	virtual void enumerateSolutions(int vertex);

	virtual void takeCareOfNode(int currentVertex);

	virtual void takeCareOfLeaf(int currentVertex);

	std::string generateOutput() override;

	std::vector<bool> visitedVertices;

};


#endif //TSPALGORITHMSCOMPARISON_BRUTEFORCE_H
