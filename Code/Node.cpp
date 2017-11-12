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
Node::Node(int cutType, Node* left, Node* right){
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
bool Node::isLeftChild()
{
	bool isLeftChild = false;
	if (this->parent != NULL) {
		isLeftChild = this->parent->getLeft() == this;
	}
	return isLeftChild;
}
bool Node::isRightChild()
{
	bool isRightChild = false;
	if (this->parent != NULL) {
		isRightChild = this->parent->getRight() == this;
	}
	return isRightChild;
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
	return optimumSize;
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
