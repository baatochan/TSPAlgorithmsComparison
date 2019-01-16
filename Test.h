//
// Created by barto on 07.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_TEST_H
#define TSPALGORITHMSCOMPARISON_TEST_H


#include "TravellingSalesmanProblem.h"
#include "Algorithm.h"
#include "TabuSearch.h"
#include "Genetic.h"

#include <fstream>

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

	std::string testA();

	std::string testB();

	std::string testC();

	std::string testD();

	std::string testE();

	std::string testF();

	std::string testG();

	std::string testH();

	std::string testI();

	std::string testJ();

	std::string testK();

	std::string getTestName(char test);

private:
	std::string exactTestTemplateOnRandomData(int numberOfTests, int cityRange, char testNumber);

	std::string exactTestTemplateOnFiles(int cityRange);

	std::string TSTestTemplateOnSmallFiles(double runDuration);

	std::string TSTestTemplateOnBigFiles(std::string fileName, char testNumber);

	std::string GenTestTemplateOnBigFiles(std::string fileName, char testNumber);

	std::shared_ptr<TravellingSalesmanProblem> TSP;

	Algorithm* algorithm;
	TabuSearch* TS;
	Genetic* Gen;

	std::fstream outputFile;
};


#endif //TSPALGORITHMSCOMPARISON_TEST_H
