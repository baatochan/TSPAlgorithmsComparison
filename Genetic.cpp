//
// Created by barto on 14.01.19.
//

#include "Genetic.h"

Genetic::Genetic(std::shared_ptr<TravellingSalesmanProblem> TSP) : Algorithm(std::move(TSP)) {
	setDefaultParameters();
}

Genetic::~Genetic() = default;

std::string Genetic::showInfoBeforeRunning() {
	std::string output;

	output += "Algoryt został uruchomiony z następującymi parametrami:\n";
	output +="* Czas wykonywania algorytmu: " + std::to_string(timeToBreakSearch) + " (s)\n";
	output +="* Wielkość populacji: " + std::to_string(populationSize) + "\n";
	output +="* Współczynnik krzyżowania: " + std::to_string(crossoverCoefficient) + "\n";
	output +="* Współczynnik mutacji: " + std::to_string(mutationCoefficient) + "\n";
	output +="* Rodzaj mutacji: ";
	if (useEdgeMutation) {
		output +="zamiana krawędzi\n";
	} else {
		output +="zamiana wierzchołków\n";
	}

	return output;
}

std::string Genetic::run() {
	startTime = std::chrono::high_resolution_clock::now();

	prepareToRun();

	bool timeNotExceeded = true;

	throw std::runtime_error("Not yet implemented!");

	while (timeNotExceeded) {

	}

	endTime = std::chrono::high_resolution_clock::now();

	return generateOutput();
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

	currentPopulation.clear();
	nextPopulation.clear();
	nextGeneration.clear();

	generateStartPopulation();
}

std::string Genetic::generateOutput() {
	throw std::runtime_error("Not yet implemented!");
}

void Genetic::generateStartPopulation() {
}
