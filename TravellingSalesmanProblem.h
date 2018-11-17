//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_TRAVELLINGSALESMANPROBLEM_H
#define TSPALGORITHMSCOMPARISON_TRAVELLINGSALESMANPROBLEM_H


#include <vector>
#include <string>

class TravellingSalesmanProblem {
public:
	void loadDataFromFile(std::string path);

	void generateRandomData(unsigned long numberOfCities, int range);

	std::string printData();

	unsigned long getNumberOfCities() const;

	int getDistance(int startVertex, int endVertex) const;

	int getMinimumDistanceFrom(int vertex) const;

	int getMinimumDistanceTo(int vertex) const;

private:
	std::vector<std::vector<int>> TSPData;

};


#endif //TSPALGORITHMSCOMPARISON_TRAVELLINGSALESMANPROBLEM_H
