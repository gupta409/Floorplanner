/*
 * main.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: Anish Gupta
 */
#include "iostream"
#include "Node.hpp"
#include "Floorplanner.hpp"
#include "PolishUtilities.hpp"
#include "RandomizeUtilites.hpp"
#include "FloorplannerConstants.hpp"
#include "IOUtilites.hpp"
#include <list>
using namespace std;
void unitTest();
int main(){
	//nodeUnitTest();
	//floorplannerUnitTest();
	//polishUtilitesUnitTest();
	//randomizeUnitTest();
	//floorplannerConstantsTest();
	//IOUtilitiesTest();
	unitTest();
	return 0;
}
void unitTest() {
	list<Node> data = IOUtilites::getInstance().readData();
	Floorplanner myPlanner(data);
	myPlanner.floorplan();
	//myPlanner.printNodes();
}