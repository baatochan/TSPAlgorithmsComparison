//
// Created by Daniel_Krol on 23.10.2021.
//

#ifndef TSPALGORITHMSCOMPARISON_SIMULATEDANNEALINGSOLVER_H
#define TSPALGORITHMSCOMPARISON_SIMULATEDANNEALINGSOLVER_H

#pragma once
#include <vector>
#include <string>
#include "Edge.h"
#include "SimulatedAnnealingSolution.h"

class SimulatedAnnealingSolver
{
public:

	std::string showInfoBeforeRunning();
	std::vector<std::vector<int>> matrix;
	std::string caseName;
	int numberOfNodes;
	int solutionCost;
	std::vector<Edge> edges;
	std::vector<int> nodes;

	SimulatedAnnealingSolver(std::vector<Edge> edges, int numberOfNodes);
	void convertToMatrix();
	void printEdges(std::string caseName);
	int calculateCost(std::vector<int> orderOfCities);

	float temperature;
	float endingTemperature;

	SimulatedAnnealingSolution solve(float initialTemperature, float endingTemperature, float alpha, int repetitionsForOneTemperature);
	std::vector<int> getNeighbourBySwap(std::vector<int> citiesInOrder);
	std::vector<int> getNeighbourByReverse(std::vector<int> citiesInOrder);
	float getTemperature(float currentTemperature, float alpha);

};


#endif //TSPALGORITHMSCOMPARISON_SIMULATEDANNEALINGSOLVER_H
