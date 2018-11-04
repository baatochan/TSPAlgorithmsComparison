//
// Created by barto on 03.11.18.
//

#include <cmath>
#include "BruteForce.h"

BruteForce::BruteForce(std::shared_ptr<TravellingSalesmanProblem> TSP) : Algorithm(std::move(TSP)) {

}

std::string BruteForce::prepareToRun() {
	std::string output;

	output += "Ilosc permitacji: ";
	output += std::to_string(static_cast<int>(round(std::tgamma(TSP->getNumberOfCities()))));
	/**
	 * number of permutations -> (n-1)!; gamma(n) = (n-1)!
	 *
	 * gets the number of cities, calculates gamma function (explained above), result is stored as a double,
	 * rounds to int, the result of rounding is still the double, casts into int and coverts that int to string :D
	 * don't kill me, my future self xD
	 *
	 */

	return output;
}

std::string BruteForce::run() {
	// TODO: Not yet implemented!
	throw std::runtime_error("Not yet implemented!");
	return std::__cxx11::string();
}
