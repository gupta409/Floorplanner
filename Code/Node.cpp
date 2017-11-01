#include "Node.hpp"
#include "string"
//FIXME: optimumSize, sizeOptions cannot be set to null. Must be handled properly for garbage values.
//FIXME: Implementation of assigning ids to new blocks is poor. May lead to very large id size when large number of blocks are used
//TODO: Method to create hard blocks from these softblocks
//Constructor to make soft blocks
Node::Node(const std::string& id, double softArea, double softMinAspect, double softMaxAspect){
	this->id = id;
	this->nodeType = SOFT;
	this->cutType = END_NODE;
	this->softArea = softArea;
	this->softMinAspect = softMinAspect;
	this->softMaxAspect = softMaxAspect;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
	cout<<"\nSoft Node Made\n";
}
//Constructor to make hard blocks
Node::Node(const string& id, set<Size>& sizeOptions){
	this->id = id;
	this->nodeType = HARD;
	this->cutType = END_NODE;
	this->sizeOptions = sizeOptions;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
	this->softArea = 0;
	this->softMinAspect = 0;
	this->softMaxAspect = 0;
	cout<<"\nHard Node Made\n";
}
//Constructor to make nodes with cut specification
Node::Node(int cutType, Node* left, Node* right){
	if(cutType == VERTICAL_CUT){
		if(left != NULL && right != NULL)
			this->id = "v_"+left->getId()+"_"+right->getId();
		else
			this->id = "v_invalid";
		this->cutType = cutType;
	}else if(cutType == HORIZONTAL_CUT){
		if(left != NULL && right != NULL)
			this->id = "h_"+left->getId()+"_"+right->getId();
		else
			this->id = "h_invalid";
		this->cutType = cutType;
	}
	else{
		//TODO: Throw exception or strong error
		cout<<"\nInvalid Cut Given\n";
		this->cutType = VERTICAL_CUT;
		if(left != NULL && right != NULL)
			this->id = "v_"+left->getId()+"_"+right->getId();
		else
			this->id = "invalid";

	}
	this->left = left;
	left->setParent(this);
	this->right = right;
	right->setParent(this);
	this->parent = NULL;
	this->softArea = 0;
	this->softMinAspect = 0;
	this->softMaxAspect = 0;
	this->nodeType = HARD;
	cout<<"\nBasic Node made\n";
}

int Node::getCutType() const {
	return cutType;
}


const Node* Node::getLeft() const {
	return left;
}

bool Node::isNodeType() const {
	return nodeType;
}

const Size& Node::getOptimumSize() const {
	return optimumSize;
}

void Node::setOptimumSize(const Size& optimumSize) {
	this->optimumSize = optimumSize;
}

const Node* Node::getParent() const {
	return parent;
}

const Node* Node::getRight() const {
	return right;
}

const set<Size>& Node::getSizeOptions() const {
	return sizeOptions;
}

double Node::getSoftArea() const {
	return softArea;
}

double Node::getSoftMaxAspect() const {
	return softMaxAspect;
}

void Node::setParent(Node* parent) {
	this->parent = parent;
}

double Node::getSoftMinAspect() const {
	return softMinAspect;
}

const string& Node::getId() const {
	return id;
}
