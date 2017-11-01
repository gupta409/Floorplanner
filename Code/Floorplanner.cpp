
#include "Floorplanner.hpp"
#include "Node.hpp"
//Finds the optimum size of the Nodes with the specified cut
void Floorplanner::sizeNodes(Node& nodeA, Node& nodeB, int cutType) {
	//TODO: Set optimum size based on cut

	//TODO: Make parent node with total of optimum sizes based on cut
	if(cutType == Node::HORIZONTAL_CUT){
		Node n1(Node::HORIZONTAL_CUT, &nodeA, &nodeB);
		double length = nodeA.getOptimumSize().getLength()+nodeB.getOptimumSize().getLength();
		double width = nodeA.getOptimumSize().getWidth()+nodeB.getOptimumSize().getWidth();
		Size s(length,width);
		n1.setOptimumSize(s);
		std::pair<string,Node*> new_node(n1.getId(),&n1);
		this->nodes.insert(new_node);
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

Floorplanner::Floorplanner(unordered_map<string, Node*>& nodes) {
	//TODO:
}

void Floorplanner::floorplan() {
	//TODO:
}
