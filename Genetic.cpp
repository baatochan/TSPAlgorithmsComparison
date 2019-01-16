//
// Created by barto on 14.01.19.
//

#include <algorithm>
#include <random>
#include "Genetic.h"

Genetic::Genetic(std::shared_ptr<TravellingSalesmanProblem> TSP) : Algorithm(std::move(TSP)) {
	setDefaultParameters();
	this->TSP->generateRandomData(20,40);
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

	while (timeNotExceeded) {
		enumerateAllPossiblePairs();

		enumerateNextGenerationForPossibleMutations();

		for (auto &offspring : nextGeneration) {
			int distance = calculateRouteDistance(offspring);
			currentPopulation.emplace_back(distance, offspring);
		}

		std::sort(currentPopulation.begin(), currentPopulation.end());

		if(currentPopulation[0].first < bestDistance) {
			bestDistance = currentPopulation[0].first;
			bestRoute = currentPopulation[0].second;
		}

		currentPopulation.resize(populationSize);

		endTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

		if (duration > timeToBreakSearch) {
			timeNotExceeded = false;
		}
	}

	restoreStartVertexForBestSolution();

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
	std::string output;

	output += "Ilość sprawdzonych rozwiązań: ";
	output += std::to_string(numberOfChecks);
	output += "\n";

	output += "Długość pracy algorytmu: ";
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	output += std::to_string(duration);
	output += "µs";
	output += "\n";

	if (bestRoute.empty()) {
		output += "Nie znaleziono żadnej trasy!\n";
	} else {
		output += "Najlepsza znaleziona droga: ";

		for (auto city : bestRoute) {
			output += std::to_string(city);
			output += " - ";
		}

		output += std::to_string(bestRoute[0]);
		output += "\n";

		output += "Długość najlepszej znalezionej drogi: ";
		output += std::to_string(bestDistance);
		output += "\n";
	}

	return output;
}

void Genetic::generateStartPopulation() {
	for (int i = 0; i < populationSize; ++i) {
		std::vector<int> route = generateRandomRoute();
		int distance = calculateRouteDistance(route);

		currentPopulation.emplace_back(distance, route);
	}
}

void Genetic::enumerateAllPossiblePairs() {
	std::random_device seed;
	std::mt19937 randomGenerator(seed());
	std::uniform_int_distribution<> crossoverRangeTransformer(0, 99);
	std::uniform_int_distribution<> vertexRangeTransformer(1, numberOfCities - 2);

	int crossoverLimit = static_cast<int>(crossoverCoefficient * 100);
	int random;

	for (int i = 0; i < currentPopulation.size(); ++i) {
		for (int j = i + 1; j < currentPopulation.size(); ++j) {
			random = crossoverRangeTransformer(randomGenerator);
			if (random < crossoverLimit) {
				int firstRandomVertex = vertexRangeTransformer(randomGenerator);

				int secondRandomVertex;
				do {
					secondRandomVertex = vertexRangeTransformer(randomGenerator);
				} while (secondRandomVertex < firstRandomVertex);

				std::vector<int> firstOffspring = currentPopulation[i].second;
				std::vector<int> secondOffspring = currentPopulation[j].second;

				for (int k = 0; k < numberOfCities; ++k) {
					if (k < firstRandomVertex || k > secondRandomVertex) {
						firstOffspring[k] = -1;
						secondOffspring[k] = -1;
					}
				}

				findMissingCitiesInOffsprings(j, firstOffspring, secondRandomVertex + 1);
				findMissingCitiesInOffsprings(i, secondOffspring, secondRandomVertex + 1);

				nextGeneration.push_back(firstOffspring);
				nextGeneration.push_back(secondOffspring);

				numberOfChecks += 2;
			}
		}
	}
}

void Genetic::findMissingCitiesInOffsprings(int populationPosition, std::vector<int>& offspring, int startingVertex) {
	int offspringPosition = startingVertex;
	int parentPosition = startingVertex;

	for (int k = 0; k < numberOfCities; ++k) {
		if (std::find(offspring.begin(), offspring.end(), currentPopulation[populationPosition].second[parentPosition]) == offspring.end()) {
			offspring[offspringPosition] = currentPopulation[populationPosition].second[parentPosition];
			offspringPosition++;
		}
		parentPosition++;

		if (parentPosition == numberOfCities) {
			parentPosition = 0;
		}
		if (offspringPosition == numberOfCities) {
			offspringPosition = 0;
		}
	}

	int x = 0;
	x++;
}

void Genetic::enumerateNextGenerationForPossibleMutations() {
	std::random_device seed;
	std::mt19937 randomGenerator(seed());
	std::uniform_int_distribution<> rangeTransformer(0, 99);

	int mutationLimit = static_cast<int>(mutationCoefficient * 100);
	int random;

	for (int i = 0; i < nextGeneration.size(); ++i) {
		random = rangeTransformer(randomGenerator);

		if (random < mutationLimit) {
			if (useEdgeMutation) {
				doEdgeMutation(i);
			} else {
				doVertexMutation(i);
			}
		}
	}
}

void Genetic::doEdgeMutation(int position) {
	std::random_device seed;
	std::mt19937 randomGenerator(seed());
	std::uniform_int_distribution<> firstVertexRangeTransformer(0, numberOfCities - 2);
	std::uniform_int_distribution<> secondVertexRangeTransformer(1, numberOfCities - 1);

	int firstVertex = firstVertexRangeTransformer(randomGenerator);

	int secondVertex;
	do {
		secondVertex = secondVertexRangeTransformer(randomGenerator);
	} while (secondVertex <= firstVertex);

	std::reverse(nextGeneration[position].begin() + firstVertex, nextGeneration[position].begin() + secondVertex + 1);
}

void Genetic::doVertexMutation(int position) {
	std::random_device seed;
	std::mt19937 randomGenerator(seed());
	std::uniform_int_distribution<> vertexRangeTransformer(0, numberOfCities - 1);

	int firstVertex = vertexRangeTransformer(randomGenerator);

	int secondVertex;
	do {
		secondVertex = vertexRangeTransformer(randomGenerator);
	} while (secondVertex == firstVertex);

	std::swap(nextGeneration[position][firstVertex], nextGeneration[position][secondVertex]);
}

void Genetic::restoreStartVertexForBestSolution() {
	auto startVertexPosition = std::find(bestRoute.begin(), bestRoute.end(), startVertex);

	std::vector<int> temp(startVertexPosition, bestRoute.end());

	for (auto it = bestRoute.begin(); it < startVertexPosition; ++it) {
		temp.push_back(*it);
	}

	bestRoute.assign(temp.begin(), temp.end());
}
