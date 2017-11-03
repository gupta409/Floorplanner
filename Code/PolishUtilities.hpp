/*
 * PolishUtilities.h
 *
 *  Created on: Nov 2, 2017
 *      Author: Destroyer
 */

#ifndef POLISHUTILITIES_HPP_
#define POLISHUTILITIES_HPP_
#include <string>
#include <vector>
using namespace std;
void polishUtilitesUnitTest();
class PolishUtilities {
private:
	PolishUtilities();
public:
	static bool isVerticalCut(string s);
	static bool isHorizontalCut(string s);
	static bool isValidCut(string s);
	static bool isValidExpression(const vector<string>& experssion);
	static int getCutType(string s);
	static const string VERTICAL_CUT;
	static const string HORIZONTAL_CUT;
};



#endif /* POLISHUTILITIES_HPP_ */
