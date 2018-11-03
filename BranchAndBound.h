//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H
#define TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H


#include "Algorithm.h"

class BranchAndBound : public Algorithm {
public:
	BranchAndBound(std::shared_ptr<TravellingSalesmanProblem> TSP);

	std::string run();

};


#endif //TSPALGORITHMSCOMPARISON_BRANCHANDBOUND_H
