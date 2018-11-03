//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_BRUTEFORCE_H
#define TSPALGORITHMSCOMPARISON_BRUTEFORCE_H


#include "Algorithm.h"

class BruteForce : public Algorithm {
public:
	BruteForce(std::shared_ptr<TravellingSalesmanProblem> TSP);

	std::string run();


};


#endif //TSPALGORITHMSCOMPARISON_BRUTEFORCE_H
