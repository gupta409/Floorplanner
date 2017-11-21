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
int main(){
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
	list<Node> data = IOUtilites::getInstance().readData();
	double avgPercent = 0, avgRuntime = 0;
	for(int i=0;i<1;i++){
		int start = clock();
		Floorplanner myPlanner(data);
		Node* root = myPlanner.floorplan();
		double totalArea = myPlanner.computeCost(root);
		double blackArea = myPlanner.computeBlackArea(root);
		IOUtilites::getInstance().writeData(myPlanner.getNodes(),totalArea,blackArea);
		double runtime = (clock() - start) / double(CLOCKS_PER_SEC);
		double percent = 100*blackArea/totalArea;
		output << to_string(runtime) << "," << to_string(percent) << endl;
		avgPercent = avgPercent + percent;
		avgRuntime = avgRuntime + runtime;
	}
	cout<<endl<<"Runtime: "<< avgRuntime <<"Area Ratio"<< " \tPercentBlack: " << avgPercent <<endl;
	output.close();
}
