/*
 * RandomizeUtilites.h
 *
 *  Created on: Nov 3, 2017
 *      Author: Destroyer
 */

#ifndef RANDOMIZEUTILITES_H_PP
#define RANDOMIZEUTILITES_H_PP
#include <random>
void RandomizeUnitTest();
class RandomizeUtilites {
private:
	std::default_random_engine* generator;
	void init();
	RandomizeUtilites();
public:
	int getRandom(int start, int end);
	//Making class singleton
	static RandomizeUtilites& getInstance()
	{
		static RandomizeUtilites instance;
		return instance;
	}
	RandomizeUtilites(RandomizeUtilites const&) = delete;
	void operator=(RandomizeUtilites const&) = delete;
};

#endif /* RANDOMIZEUTILITES_H_PP */
