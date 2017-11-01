#pragma once
#include "Size.hpp"
#include "iostream"
#include <set>
using namespace std;
class Node{
private:
	bool nodeType;	//1: Hard, 0: Soft
	double softArea;
	double softMinAspect;
	double softMaxAspect;
	int cutType;	//1(vertical), 2(horizontal), 3(endNode)
	Node* left;
	Node* right;
	Size optimumSize;
	set<Size> sizeOptions;
	Node();
public:
	Node(double softArea, double softMinAspect, double softMaxAspect);
	Node(set<Size> sizeOptions);
	Node(int cutType, Node* left, Node* right);
static const int VERTICAL_CUT = 1;
static const int HORIZONTAL_CUT = 2;
static const int END_NODE = 3;
static const bool HARD = true;
static const bool SOFT = false;


};




