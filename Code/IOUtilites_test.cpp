/*
 * IOUtilites_test.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Anish Gupta
 */

#include "IOUtilites.hpp"
void readTest1();
void writeTest1();
void IOUtilitiesTest() {
	//readTest1();
	writeTest1();
}
void readTest1() {
	list<Node> data = IOUtilites::getInstance().readData();
	for (auto it : data) cout << it.getId() << "\t" << it.getSizeOptions().begin()->getLength() << "\t" << it.getSizeOptions().begin()->getWidth() << endl;
}
void writeTest1() {
	IOUtilites::getInstance().writeData(unordered_map<string, Node*>(),0,0);
}
