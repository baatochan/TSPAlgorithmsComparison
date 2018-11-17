//
// Created by barto on 03.11.18.
//

#include "Algorithm.h"

Algorithm::Algorithm(std::shared_ptr<TravellingSalesmanProblem> TSP) : TSP(std::move(TSP)) {}

Algorithm::~Algorithm() = default;
