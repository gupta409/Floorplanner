
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

	Node* polishToTree(const vector<string>& experssion);
	double computeCost(const Node& root);
	static bool acceptMove(double deltaCost, double temperature);
	static void move(vector<string>& currentPolish);
	static double coolDown(double temperature);
public:
	Node* sizeNodes(Node &nodeA, Node &nodeB, int cutType);
	Floorplanner(list<Node>& nodes);
	void insertNode(Node& nodeA);
	void removeNode(string id);
	void floorplan();
	void printNodes();
};



#endif  /*FLOORPLANNER_HPP_*/
