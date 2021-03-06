//
// Created by barto on 29.10.18.
//

#ifndef TSPALGORITHMSCOMPARISON_PROGRAM_H
#define TSPALGORITHMSCOMPARISON_PROGRAM_H


#include "TravellingSalesmanProblem.h"
#include "BruteForce.h"
#include "BranchAndBound.h"
#include "Test.h"
#include "TabuSearch.h"
#include "Genetic.h"

#include <iostream>
#include <memory>

class Program {
public:
	Program();

	void start();

private:
	void printMenu();

	void printFileWarning();

	void runTestMenu();

	void printTestMenu();

	void runTSSettingsMenu();

	void printTSSettingsMenu();

	void runGenSettingsMenu();

	void printGenSettingsMenu();

	std::shared_ptr<TravellingSalesmanProblem> TSP;

	BruteForce BF;
	BranchAndBound BnB;
	TabuSearch TS;
	Genetic Gen;

	Test test;
};


#endif //TSPALGORITHMSCOMPARISON_PROGRAM_H
