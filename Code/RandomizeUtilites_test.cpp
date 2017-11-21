/*
 * RandomizeUtilites_test.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: Anish Gupta
 */

#include "RandomizeUtilites.hpp"
#include "iostream"
void randomUnitTest1();
void randomUnitTest2();
void randomUnitTest3();
void randomUnitTest4();
void randomizeUnitTest() {
	randomUnitTest4();
}
void randomUnitTest1() {
	for (int i = 0; i<30; i++)
		std::cout << RandomizeUtilites::getInstance().getRandom(0, 1) <<std::endl;
}
void randomUnitTest2() {
	for (int i = 0; i<30; i++)
		std::cout << RandomizeUtilites::getInstance().getRandom(0, 100) << std::endl;
}
void randomUnitTest3() {
	for (int i = 0; i<30; i++)
		std::cout << RandomizeUtilites::getInstance().getRandom(1, 1) << std::endl;
}
void randomUnitTest4() {
	for (int i = 0; i<30; i++)
		std::cout << RandomizeUtilites::getInstance().getRandomReal(0, 1) << std::endl;
}
