//
// Created by barto on 14.01.19.
//

#include "Genetic.h"

Genetic::Genetic(std::shared_ptr<TravellingSalesmanProblem> TSP) : Algorithm(std::move(TSP)) {
	setDefaultParameters();
}

Genetic::~Genetic() = default;

std::string Genetic::showInfoBeforeRunning() {
	return std::__cxx11::string();
}

std::string Genetic::run() {
	return std::__cxx11::string();
}

void Genetic::setDefaultParameters() {
	timeToBreakSearch = 30;
	populationSize = 50;
	crossoverCoeficcient = 0.8;
	mutationCoeficcient = 0.01;
	useEdgeMutation = false;
}

void Genetic::prepareToRun() {
	Algorithm::prepareToRun();
}

std::string Genetic::generateOutput() {
	return std::__cxx11::string();
}
