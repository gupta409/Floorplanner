#pragma once
#include "Node.hpp"
//FIXME: optimumSize, sizeOptions cannot be set to null. Must be handled properly for garbage
//Constructor to make soft blocks
Node::Node(double softArea, double softMinAspect, double softMaxAspect){
	this->nodeType = SOFT;
	this->cutType = END_NODE;
	this->softArea = softArea;
	this->softMinAspect = softMinAspect;
	this->softMaxAspect = softMaxAspect;
	this->left = NULL;
	this->right = NULL;
	//TODO: Call create hard blocks from these softblocks
	cout<<"\nSoft Node Made\n";
}
//Constructor to make hard blocks
Node::Node(set<Size> sizeOptions){
	this->nodeType = HARD;
	this->cutType = END_NODE;
	this->sizeOptions = sizeOptions;
	this->left = NULL;
	this->right = NULL;
	this->softArea = 0;
	this->softMinAspect = 0;
	this->softMaxAspect = 0;
	cout<<"\nHard Node Made\n";
}
//Constructor to make nodes with cut specification
Node::Node(int cutType, Node* left, Node* right){
	if(cutType == VERTICAL_CUT || cutType == HORIZONTAL_CUT){
		this->cutType = cutType;
	}else{
		//TODO: Throw exception or strong error
		cout<<"\nInvalid Cut Given\n";
		this->cutType = VERTICAL_CUT;
	}
	this->left = left;
	this->right = right;
	this->softArea = 0;
	this->softMinAspect = 0;
	this->softMaxAspect = 0;
	cout<<"\nBasic Node made\n";
}
