//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_ALGORITHM_H
#define TSPALGORITHMSCOMPARISON_ALGORITHM_H


#include "TravellingSalesmanProblem.h"

#include <utility>
#include <string>
#include <memory>
#include <chrono>

class Algorithm {
public:
	explicit Algorithm(std::shared_ptr<TravellingSalesmanProblem> TSP);

	virtual ~Algorithm();

	virtual std::string showInfoBeforeRunning() = 0;

	virtual std::string run() = 0;

protected:
	virtual void prepareToRun();

	virtual std::string generateOutput() = 0;

	std::shared_ptr<TravellingSalesmanProblem> TSP;

	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;

	int numberOfChecks;

	unsigned long numberOfCities;

	int startVertex;

	std::vector<int> currentRoute;
	int currentDistance;

	std::vector<int> bestRoute;
	int bestDistance;

private:
	Algorithm() = default;

};


#endif //TSPALGORITHMSCOMPARISON_ALGORITHM_H
