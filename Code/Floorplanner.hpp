
#ifndef FLOORPLANNER_HPP_
#define FLOORPLANNER_HPP_
#include "unordered_map"
#include "Node.hpp"
#include "vector"
using namespace std;
void floorplannerUnitTest();
class Floorplanner {
private:
	unordered_map<string,Node*> nodes;
	
protected:
	Node* sizeNodes(Node &nodeA, Node &nodeB, int cutType);
	Node* polishToTree(const vector<string>& experssion);
	double computeCost(Node* root);
	static bool acceptMove(double deltaCost, double temperature);
	static double coolDown(double temperature);
public:
	Floorplanner(list<Node>& nodes);
	vector<string> generateInitialExpression();
	static vector<string> move(vector<string> currentPolish);
	void insertNode(Node& nodeA);
	void removeNode(string id);
	void floorplan();
	void printNodes();
};



#endif  /*FLOORPLANNER_HPP_*/
