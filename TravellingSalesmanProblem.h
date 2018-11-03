//
// Created by barto on 03.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_TRAVELLINGSALESMANPROBLEM_H
#define TSPALGORITHMSCOMPARISON_TRAVELLINGSALESMANPROBLEM_H


#include <vector>
#include <string>

class TravellingSalesmanProblem {
public:
	TravellingSalesmanProblem();

	void loadDataFromFile(std::string path);

	void generateRandomData(int numberOfCities, int range);

	std::string printData();

private:
	std::vector<std::vector<int>> TSPData;

	void clearData();
};


#endif //TSPALGORITHMSCOMPARISON_TRAVELLINGSALESMANPROBLEM_H
