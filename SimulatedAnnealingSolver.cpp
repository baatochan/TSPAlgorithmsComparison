//
// Created by Daniel_Krol on 23.10.2021.
//

#include "SimulatedAnnealingSolver.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

SimulatedAnnealingSolver::SimulatedAnnealingSolver(std::vector<Edge> edges, int numberOfNodes)
		: edges(edges), numberOfNodes(numberOfNodes), solutionCost(2147483647) {
	for (int i = 0; i < numberOfNodes; i++)
	{
		nodes.push_back(i);
	}
	convertToMatrix();
}

void SimulatedAnnealingSolver::convertToMatrix() {
	for (int i = 0; i < numberOfNodes; i++) {
		std::vector<int> singleVector;
		for (int j = 0; j < numberOfNodes; j++) {
			singleVector.push_back(edges.at(i * numberOfNodes + j).getCost());
		}
		matrix.push_back(singleVector);
	}
}

int SimulatedAnnealingSolver::calculateCost(std::vector<int> orderOfCities) {
	int cost = 0;
	for (int i = 0; i < orderOfCities.size() - 1; i++) {
		cost += matrix.at(orderOfCities.at(i + 1)).at(orderOfCities.at(i));
	}

	cost += matrix.at(orderOfCities.at(0)).at(orderOfCities.at(orderOfCities.size() - 1));
	return cost;
}

std::vector<int> SimulatedAnnealingSolver::getNeighbourBySwap(std::vector<int> citiesInOrder) {
	int firstCityToSwap = std::rand() % (citiesInOrder.size() - 1);
	int secondCityToSwap = std::rand() % (citiesInOrder.size() - 1);
	while (firstCityToSwap == secondCityToSwap) {
		secondCityToSwap = std::rand() % (citiesInOrder.size() - 1);
	}
	int firstCity = citiesInOrder.at(firstCityToSwap);
	int secondCity = citiesInOrder.at(secondCityToSwap);
	citiesInOrder.at(firstCityToSwap) = secondCity;
	citiesInOrder.at(secondCityToSwap) = firstCity;

	return citiesInOrder;
}

std::vector<int> SimulatedAnnealingSolver::getNeighbourByReverse(std::vector<int> citiesInOrder) {
	int startReverseCity = std::rand() % (citiesInOrder.size() - 1);
	int endReverseCity = std::rand() % (citiesInOrder.size() - 1);
	while (startReverseCity >= endReverseCity) {
		startReverseCity = std::rand() % (citiesInOrder.size() - 1);
		endReverseCity = std::rand() % (citiesInOrder.size() - 1);
	}

	std::vector<int> citiesToRevert;
	for(int i = startReverseCity ; i <= endReverseCity ; i++) {
		citiesToRevert.push_back(citiesInOrder.at(i));
	}

	std::reverse(citiesToRevert.begin(), citiesToRevert.end());
	for (int i = startReverseCity; i <= endReverseCity; i++) {
		citiesInOrder.at(i) = citiesToRevert.at(i - startReverseCity);
	}

	return citiesInOrder;
}

float SimulatedAnnealingSolver::getTemperature(float currentTemperature, float alpha) {
	return currentTemperature * alpha;
}

SimulatedAnnealingSolution SimulatedAnnealingSolver::solve(float initialTemperature, float endTemperature, float alpha, int repetitionsForOneTemperature) {
	temperature = initialTemperature;
	endingTemperature = endTemperature;

	std::random_device rd;
	std::mt19937 g(rd());
	std::vector<int> randomOrder;
	std::uniform_real_distribution<double> num(0.0, 1.0);
	randomOrder.reserve(matrix.size());
	for (int i = 0; i < matrix.size(); i++) {
		randomOrder.push_back(i);
	}
	int bestGlobalCost = INT_MAX;
	std::vector<int> bestOrder;

	SimulatedAnnealingSolution solutionA;
	solutionA.cost = this->calculateCost(randomOrder);
	solutionA.orderOfCities = randomOrder;

	while (temperature > endingTemperature) {
		int repetitionNumber = 0;
		while (repetitionNumber < repetitionsForOneTemperature) {
			SimulatedAnnealingSolution solutionB;
			solutionB.orderOfCities = getNeighbourByReverse(solutionA.orderOfCities);
			solutionB.cost = calculateCost(solutionB.orderOfCities);
			if(solutionB.cost < bestGlobalCost) {
				bestGlobalCost = solutionB.cost;
				bestOrder = solutionB.orderOfCities;
			}
			if(solutionB.cost < solutionA.cost) {
				solutionA = solutionB;
			}
			else {
				if(std::exp(((double(solutionA.cost - solutionB.cost))/temperature)) > num(g)) {
					solutionA = solutionB;
				}

			}
			repetitionNumber++;
		}
		temperature = getTemperature(temperature, alpha);
	}
	solutionA.cost = bestGlobalCost;
	solutionA.orderOfCities = bestOrder;
	return solutionA;
}
