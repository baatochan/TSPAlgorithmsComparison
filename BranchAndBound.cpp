//
// Created by barto on 03.11.18.
//

#include "BranchAndBound.h"

BranchAndBound::BranchAndBound(std::shared_ptr<TravellingSalesmanProblem> TSP) : Algorithm(std::move(TSP)) {

}

std::string BranchAndBound::prepareToRun() {
	throw std::runtime_error("Not yet implemented!");
	return std::__cxx11::string();
}

std::string BranchAndBound::run() {
	throw std::runtime_error("Not yet implemented!");
	return std::__cxx11::string();
}
