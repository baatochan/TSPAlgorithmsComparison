//
// Created by barto on 27.11.18.
//

#ifndef TSPALGORITHMSCOMPARISON_TABUSEARCH_H
#define TSPALGORITHMSCOMPARISON_TABUSEARCH_H


#include "Algorithm.h"

class TabuSearch : public Algorithm {
public:
	~TabuSearch() override;

	std::string showInfoBeforeRunning() override;

	std::string run() override;

private:

};


#endif //TSPALGORITHMSCOMPARISON_TABUSEARCH_H
