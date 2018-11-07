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
#include "Test.h"

class Program {
public:
	Program();

	void start();

private:
	std::shared_ptr<TravellingSalesmanProblem> TSP;

	BruteForce BF;
	BranchAndBound BnB;

	Test test;

	void printMenu();

	void printFileWarning();

	void runTestMenu();

	void printTestMenu();
};


#endif //TSPALGORITHMSCOMPARISON_PROGRAM_H
