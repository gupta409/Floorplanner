#include "unordered_map"
#include "Floorplanner.hpp"
#include "Node.hpp"
#include "cmath"
#include "string"
//Finds the optimum size of the Nodes with the specified cut
void Floorplanner::sizeNodes(Node& nodeA, Node& nodeB, int cutType) {
	//TODO: Set optimum size based on cut; currently directly using first element of the options: considering only one option for each hard block
	list<Size> temp;
	Size defaultSize(0,0);
	//FIXME: Only Size nodeA and nodeB and not all nodes in the map
	if(!nodeA.getSizeOptions().empty()){
		nodeA.setOptimumSize(nodeA.getSizeOptions().front());
	}else{
		nodeA.setOptimumSize(defaultSize);
	}
	if(!nodeB.getSizeOptions().empty()){
		nodeB.setOptimumSize(nodeB.getSizeOptions().front());
	}else{
		nodeB.setOptimumSize(defaultSize);
	}
	if(cutType == Node::HORIZONTAL_CUT){
		Node n1(Node::HORIZONTAL_CUT, &nodeA, &nodeB);
		double length = fmax(nodeA.getOptimumSize().getLength(),nodeB.getOptimumSize().getLength());
		double width = nodeA.getOptimumSize().getWidth()+nodeB.getOptimumSize().getWidth();
		Size s(length,width);
		n1.setOptimumSize(s);
		std::pair<string,Node*> new_node(n1.getId(),&n1);
		this->nodes.insert(new_node);
	}else
	if(cutType == Node::VERTICAL_CUT){
			Node n1(Node::VERTICAL_CUT, &nodeA, &nodeB);
			double length = nodeA.getOptimumSize().getLength()+nodeB.getOptimumSize().getLength();
			double width = fmax(nodeA.getOptimumSize().getWidth(),nodeB.getOptimumSize().getWidth());
			Size s(length,width);
			n1.setOptimumSize(s);
			std::pair<string,Node*> new_node(n1.getId(),&n1);
			this->nodes.insert(new_node);
	}else{
		//TODO: Throw exception
		cout<<"Invalid Cut";
	}
}
//Converts polish expression to tree and computes sizing and area while converting. Returns: root node of the tree
Node Floorplanner::polishToTree(const vector<string>& experssion) {
	//TODO:
	//Node n;
	//return n;
}
//Traverses the tree and gives total area of the floorplan. Returns: Total Area
double Floorplanner::computeCost(const Node& root) {
	double cost = 0;
	//TODO:
	return cost;
}
//Returns: True/False
bool Floorplanner::acceptMove(double deltaCost, double temperature) {
	bool isAccepted = false;
	//TODO:
	return isAccepted;
}
//Makes changes in the polish expression based on the Wong-Liu Moves model
void Floorplanner::move(vector<string>& currentPolish) {
	//ToDO:
}
//Returns new temperature
double Floorplanner::coolDown(double temperature) {
	//TODO:
	return 0.0;
}

Floorplanner::Floorplanner(list<Node>& nodes) {
	for(auto it = nodes.begin(); it!=nodes.end();++it){
		std::pair<string,Node*> new_node(it->getId(),&*it);
		this->nodes.insert(new_node);
	}
}

void Floorplanner::floorplan() {
	//TODO: Write SA code here
}
void Floorplanner::printNodes(){
	for(auto it = this->nodes.begin(); it != this->nodes.end(); ++it){
		cout<<"ID:\t"<<it->first<<" Length:\t"<<it->second->getOptimumSize().getLength()<<" Width:\t"<<it->second->getOptimumSize().getWidth()<<endl;
	}
}
