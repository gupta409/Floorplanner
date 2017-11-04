/*
 * RandomizeUtilites.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: Destroyer
 */

#include "RandomizeUtilites.hpp"
#include <chrono>
#include <random>
RandomizeUtilites::RandomizeUtilites() {
	// TODO Auto-generated constructor stub
	init();
}
void RandomizeUtilites:: init() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator = new std::default_random_engine(seed);
}
int RandomizeUtilites::getRandom(int start, int end) {
	std::uniform_int_distribution<int> distribution(start, end);
	int randomNumber = distribution(*this->generator);
	return randomNumber;
}
