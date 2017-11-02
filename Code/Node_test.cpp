/*
 * Node_UnitTest.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: Destroyer
 */
#include "iostream"
#include "Node.hpp"
using namespace std;
void nodeUnitTest(){
	Node n("hard1",2.5,3.5,40);
	Size s1;
	list<Size> sizeops;
	Node n1("soft1",sizeops);
	Node top((int)Node::HORIZONTAL_CUT,&n,&n1);
	Node top1((int)Node::VERTICAL_CUT,&n,&n1);
	Node topS((int)Node::VERTICAL_CUT,&top,&top1);
	cout<<top.getId()<<endl;
	cout<<top1.getId()<<endl;
	cout<<topS.getId()<<endl;
}



