//
// Created by barto on 07.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_TEST_H
#define TSPALGORITHMSCOMPARISON_TEST_H


#include <fstream>
#include "TravellingSalesmanProblem.h"
#include "BruteForce.h"
#include "BranchAndBound.h"

class Test {
public:
	Test();

	void openFile();

	void closeFile();

	std::string test1();

	std::string test2();

	std::string test3();

	std::string test4();

	std::string test5();

	std::string test6();

	std::string test7();

	std::string test8();

	std::string test9();

	std::string getTestName(char test);

private:
	std::shared_ptr<TravellingSalesmanProblem> TSP;

	BruteForce BF;
	BranchAndBound BnB;

	std::fstream outputFile;
};


#endif //TSPALGORITHMSCOMPARISON_TEST_H
