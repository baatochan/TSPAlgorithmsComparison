//
// Created by barto on 14.01.19.
//

#ifndef TSPALGORITHMSCOMPARISON_GENETIC_H
#define TSPALGORITHMSCOMPARISON_GENETIC_H


#include "Algorithm.h"

class Genetic : public Algorithm {
public:
	explicit Genetic(std::shared_ptr<TravellingSalesmanProblem> TSP);

	~Genetic() override;

	std::string showInfoBeforeRunning() override;

	std::string run() override;

	void setDefaultParameters();

private:

	void prepareToRun() override;

	std::string generateOutput() override;
};


#endif //TSPALGORITHMSCOMPARISON_GENETIC_H
