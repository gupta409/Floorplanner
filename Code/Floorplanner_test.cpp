/*
 * Floorplanner_test.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: Anish Gupta
 */

#include "Floorplanner.hpp"
#include "PolishUtilities.hpp"
#include "RandomizeUtilites.hpp"
#include "list"
#include "Node.hpp"
using namespace std;
void floorplanUnitTest1();
void floorplanUnitTest2();
void floorplannerUnitTest(){
	floorplanUnitTest1();
	//floorplanUnitTest2();
}
void floorplanUnitTest1() {
	list<Size> l1;
	Size s(1, 2);
	l1.push_back(s);
	Node n1("hard1", l1);
	Node n2("hard2", l1);
	Node n3("hard3", l1);
	Node n4("hard4", l1);
	list<Node> nodes;
	nodes.push_back(n1);
	nodes.push_back(n2);
	nodes.push_back(n3);
	nodes.push_back(n4);
	Floorplanner floorplanner1(nodes);
	floorplanner1.floorplan();
	//floorplanner1.printNodes();
}
void floorplanUnitTest2() {
	list<Size> l1;
	Size s(1, 2);
	l1.push_back(s);
	Node n1("hard1", l1);
	Node n2("hard2", l1);
	Node n3("hard3", l1);
	Node n4("hard4", l1);
	list<Node> nodes;
	nodes.push_back(n1);
	nodes.push_back(n2);
	nodes.push_back(n3);
	nodes.push_back(n4);
	Floorplanner floorplanner1(nodes);
	vector<string> expresion = floorplanner1.generateInitialExpression();
	//PolishUtilities::printExpression(expresion);
	for (int i = 0; i < 200; i++) {
		cout << std::endl;
		expresion = Floorplanner::move(expresion);
		//if(!PolishUtilities::isNormalizedExpression(expresion))
			//cout<<"Wrong Expression Found"<<endl;
		PolishUtilities::printExpression(expresion);
	}
}
