//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_ALGORITHM_H
#define TSPALGORITHMSCOMPARISON_ALGORITHM_H


#include <utility>
#include <string>
#include <memory>
#include "TravellingSalesmanProblem.h"

class Algorithm {
public:
	Algorithm(std::shared_ptr<TravellingSalesmanProblem> TSP);

	virtual std::string run() = 0;

private:
	Algorithm() = default;

	std::shared_ptr<TravellingSalesmanProblem> TSP;
};


#endif //TSPALGORITHMSCOMPARISON_ALGORITHM_H
