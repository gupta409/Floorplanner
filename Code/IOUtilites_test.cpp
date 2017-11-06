/*
 * IOUtilites_test.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Destroyer
 */

#include "IOUtilites.hpp"
void readTest1();
void IOUtilitiesTest() {
	readTest1();
}
void readTest1() {
	list<Node> data = IOUtilites::getInstance().readData();
	for (auto it : data) cout << it.getId() << "\t" << it.getSizeOptions().begin()->getLength() << "\t" << it.getSizeOptions().begin()->getWidth() << endl;
}
