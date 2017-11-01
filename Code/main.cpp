/*
 * main.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: Anish Gupta
 */
#pragma once
#include "iostream"
#include "Node.hpp"
using namespace std;
int main(){
	Node n(2.5,3.5,40);
	Size s1;
	set<Size> sizeops;
	Node n1(sizeops);
	Node top((int)Node::HORIZONTAL_CUT,&n,&n1);
	return 0;
}



