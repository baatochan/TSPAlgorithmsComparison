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

	double getTimeToBreakSearch() const;

	int getPopulationSize() const;

	double getCrossoverCoefficient() const;

	double getMutationCoefficient() const;

	bool isUseEdgeMutation() const;

	void setTimeToBreakSearch(double timeToBreakSearch);

	void setPopulationSize(int populationSize);

	void setCrossoverCoefficient(double crossoverCoefficient);

	void setMutationCoefficient(double mutationCoefficient);

	void setUseEdgeMutation(bool useEdgeMutation);

private:

	void prepareToRun() override;

	std::string generateOutput() override;

	void generateStartPopulation();

	void enumerateAllPossiblePairs();

	void findMissingCitiesInOffsprings(int populationPosition, std::vector<int>& offspring, int startingVertex);

	void enumerateNextGenerationForPossibleMutations();

	void doEdgeMutation(int position);

	void doVertexMutation(int position);

	void restoreStartVertexForBestSolution();

	std::vector<std::pair<int, std::vector<int>>> currentPopulation;
	std::vector<std::pair<int, std::vector<int>>> nextPopulation;
	std::vector<std::vector<int>> nextGeneration;

	double timeToBreakSearch;
	int populationSize;
	double crossoverCoefficient;
	double mutationCoefficient;
	bool useEdgeMutation;
};


#endif //TSPALGORITHMSCOMPARISON_GENETIC_H
