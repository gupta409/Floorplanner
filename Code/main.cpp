/*
 * main.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: Anish Gupta
 */
#include "iostream"
#include "ctime"
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
	int start = clock();
	unitTest();
	cout<<endl<<"Runtime:"<<(clock()-start)/double(CLOCKS_PER_SEC)<<endl;
	return 0;
}
void unitTest() {
	list<Node> data = IOUtilites::getInstance().readData();
	//FloorplannerConstants::getInstance();
	Floorplanner myPlanner(data);
	Node* root = myPlanner.floorplan();
	double totalArea = myPlanner.computeCost(root);
	IOUtilites::getInstance().writeData(myPlanner.getNodes(),totalArea,myPlanner.computeBlackArea(root));
}
