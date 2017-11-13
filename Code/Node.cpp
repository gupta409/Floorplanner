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
	//Makes 3 sizes out-of the ratios given
	double l = sqrt(softArea*softMinAspect);
	double w = sqrt(softArea/softMinAspect);
	//TODO: Add rotations
	Size sMin(l,w);
	this->sizeOptions.push_back(sMin);
	l = sqrt(softArea*softMaxAspect);
	w = sqrt(softArea / softMaxAspect);
	Size sMax(l, w);
	this->sizeOptions.push_back(sMax);
	if (softMaxAspect>1 && softMinAspect<1) {
		double l = sqrt(softArea);
		double w = sqrt(softArea);
		Size sOne(l, w);
		this->sizeOptions.push_back(sOne);
	}
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
	this->llCord= pair<double, double>(0, 0);
	this->urCord = pair<double, double>(0, 0);
}
//Constructor to make hard blocks
Node::Node(const string& id, list<Size>& sizeOptions){
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
	this->llCord = pair<double, double>(0, 0);
	this->urCord = pair<double, double>(0, 0);
}
//Constructor to make nodes with cut specification
Node::Node(int cutType, Node* left, Node* right, list<Size>& sizeOptions){
	if(cutType == VERTICAL_CUT){
		if(left != NULL && right != NULL)
			//FIXME: Potential space complexity issues here
			this->id = "v_"+left->getId()+"_"+right->getId();
		else
			this->id = "v_invalid";
		this->cutType = cutType;
	}else if(cutType == HORIZONTAL_CUT){
		if(left != NULL && right != NULL)
			//FIXME: Potential space complexity issues here
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
	this->sizeOptions = sizeOptions;
	this->parent = NULL;
	this->softArea = 0;
	this->softMinAspect = 0;
	this->softMaxAspect = 0;
	this->nodeType = HARD;
	this->llCord = pair<double, double>(0, 0);
	this->urCord = pair<double, double>(0, 0);
}
bool Node::isEndNode() {
	bool isEnd = false;
	if (this->left == NULL && this->right == NULL) {
		isEnd = true;
	}
	return isEnd;
}
int Node::getCutType() const {
	return cutType;
}


Node* Node::getLeft() const {
	return left;
}

bool Node::isNodeType() const {
	return nodeType;
}

const Size& Node::getOptimumSize() const {
	return this->optimumSize;
}

void Node::setOptimumSize(Size& optimumSize) {
	this->optimumSize = optimumSize;
}

Node* Node::getParent() const {
	return parent;
}

Node* Node::getRight() const {
	return right;
}

list<Size>& Node::getSizeOptions() {
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

void Node::setLeft(Node * left)
{
	this->left = left;
}

void Node::setRight(Node * right)
{
	this->right = right;
}

double Node::getSoftMinAspect() const {
	return softMinAspect;
}

const string& Node::getId() const {
	return id;
}

pair<double,double> Node::getLLCord()
{
	return llCord;
}

pair<double, double> Node::getURCord()
{
	return urCord;
}

void Node::setLLCord(pair<double,double> llCord)
{
	this->llCord = llCord;
}
void Node::setURCord(pair<double, double> urCord)
{
	this->urCord = urCord;
}
