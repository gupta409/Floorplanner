/*
 * main.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: Anish Gupta
 */
#include "fstream"
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
int main(string fileName){
	try {
		unitTest();
		return 0;
	}
	catch (...) {
		cout << "EXCEPTION!!";
	}
}
void unitTest() {
	ofstream output;
	output.open("stats.txt");
	int start = clock();
	list<Node> data = IOUtilites::getInstance().readData();
	Floorplanner myPlanner(data);
	Node* root = myPlanner.floorplan();
	double totalArea = myPlanner.computeCost(root);
	double blackArea = myPlanner.computeBlackArea(root);
	IOUtilites::getInstance().writeData(myPlanner.getNodes(),totalArea,blackArea);
	cout << endl << "Runtime:" << (clock() - start) / double(CLOCKS_PER_SEC) << endl;
	output << to_string((clock() - start) / double(CLOCKS_PER_SEC)) << "," << to_string(100*blackArea/totalArea) << endl;
	output.close();
}
