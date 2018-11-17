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

	virtual std::string showInfoBeforeRunning() = 0;

	virtual std::string run() = 0;

protected:
	std::shared_ptr<TravellingSalesmanProblem> TSP;

private:
	Algorithm() = default;

};


#endif //TSPALGORITHMSCOMPARISON_ALGORITHM_H
