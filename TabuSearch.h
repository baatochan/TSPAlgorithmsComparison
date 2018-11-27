//
// Created by barto on 27.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_TABUSEARCH_H
#define TSPALGORITHMSCOMPARISON_TABUSEARCH_H


#include "Algorithm.h"

class TabuSearch : public Algorithm {
public:
	explicit TabuSearch(std::shared_ptr<TravellingSalesmanProblem> TSP);

	~TabuSearch() override;

	std::string showInfoBeforeRunning() override;

	std::string run() override;

private:
	void prepareToRun() override;

	void generateStartRoute();

	int calculateRouteDistance(std::vector<int>& route);

	std::tuple<int, int, int> enumerateNeighbourSolutions();

	void updateTabuList();

	void generateRandomRoute();

	std::string generateOutput() override;

	// city 1, city 2, cadency; blocks exchanging the pair of cities
	std::vector<std::tuple<int, int, int>> tabuList;

	// TS parameters TODO: some kind of UI to change it
	int cadency;
	//int tabuSize;
	double timeToBreakSearch;
	bool aspiration;
	bool diversification;
	int iterationsToChangeNeighborhood;

	int iterationWithoutImprovement;
};


#endif //TSPALGORITHMSCOMPARISON_TABUSEARCH_H
