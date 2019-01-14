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

	std::vector<std::pair<int, std::vector<int>>> currentPopulation;
	std::vector<std::pair<int, std::vector<int>>> nextPopulation;
	std::vector<std::pair<int, std::vector<int>>> nextGeneration;

	double timeToBreakSearch;
	unsigned populationSize;
	float crossoverCoeficcient;
	float mutationCoeficcient;
	bool useEdgeMutation;
};


#endif //TSPALGORITHMSCOMPARISON_GENETIC_H
