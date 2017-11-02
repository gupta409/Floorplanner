#pragma once
#include "Size.hpp"
#include "iostream"
#include <list>
#include <string>
using namespace std;
void nodeUnitTest();
class Node{
private:
	string id;
	bool nodeType;	//1: Hard, 0: Soft
	double softArea;
	double softMinAspect;
	double softMaxAspect;
	int cutType;	//1(vertical), 2(horizontal), 3(endNode)
	Node* parent;
	Node* left;
	Node* right;
	Size optimumSize;
	list<Size> sizeOptions;
public:
	//Constructors
	Node(const string& id, double softArea, double softMinAspect, double softMaxAspect);
	Node(const string& id, list<Size>& sizeOptions);
	Node(int cutType, Node* left, Node* right);
	//Getter Setters
	int getCutType() const;
	bool isNodeType() const;
	const Size& getOptimumSize() const;
	void setOptimumSize(Size& optimumSize);
	const Node* getParent() const;
	const Node* getRight() const;
	const Node* getLeft() const;
	list<Size>& getSizeOptions() ;
	double getSoftArea() const;
	double getSoftMaxAspect() const;
	double getSoftMinAspect() const;
	void setParent(Node* parent);
	const string& getId() const;
	//Static Constants
	static const int VERTICAL_CUT = 1;
	static const int HORIZONTAL_CUT = 2;
	static const int END_NODE = 3;
	static const bool HARD = true;
	static const bool SOFT = false;
};
