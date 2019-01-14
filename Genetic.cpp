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
	crossoverCoefficient = 0.8;
	mutationCoefficient = 0.01;
	useEdgeMutation = false;
}

double Genetic::getTimeToBreakSearch() const {
	return timeToBreakSearch;
}

int Genetic::getPopulationSize() const {
	return populationSize;
}

double Genetic::getCrossoverCoefficient() const {
	return crossoverCoefficient;
}

double Genetic::getMutationCoefficient() const {
	return mutationCoefficient;
}

bool Genetic::isUseEdgeMutation() const {
	return useEdgeMutation;
}

void Genetic::setTimeToBreakSearch(double timeToBreakSearch) {
	Genetic::timeToBreakSearch = timeToBreakSearch;
}

void Genetic::setPopulationSize(int populationSize) {
	Genetic::populationSize = populationSize;
}

void Genetic::setCrossoverCoefficient(double crossoverCoefficient) {
	Genetic::crossoverCoefficient = crossoverCoefficient;
}

void Genetic::setMutationCoefficient(double mutationCoefficient) {
	Genetic::mutationCoefficient = mutationCoefficient;
}

void Genetic::setUseEdgeMutation(bool useEdgeMutation) {
	Genetic::useEdgeMutation = useEdgeMutation;
}

void Genetic::prepareToRun() {
	Algorithm::prepareToRun();
}

std::string Genetic::generateOutput() {
	return std::__cxx11::string();
}
