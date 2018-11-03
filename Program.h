//
// Created by barto on 29.10.18.
//

#ifndef TSPALGORITHMSCOMPARISON_PROGRAM_H
#define TSPALGORITHMSCOMPARISON_PROGRAM_H


#include <iostream>
#include <memory>
#include "TravellingSalesmanProblem.h"
#include "BruteForce.h"
#include "BranchAndBound.h"

class Program {
public:
	Program();

	void start();

private:
	std::shared_ptr<TravellingSalesmanProblem> TSP;

	BruteForce BF;
	BranchAndBound BnB;

	void printMenu();

	void printFileWarning();
};


#endif //TSPALGORITHMSCOMPARISON_PROGRAM_H
