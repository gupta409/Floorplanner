
#ifndef FLOORPLANNER_HPP_
#define FLOORPLANNER_HPP_
#include "unordered_map"
#include "Node.hpp"
#include "vector"
using namespace std;
void floorplannerUnitTest();
class Floorplanner {
private:
	const double coolDownRate = 0.95;
	const double freezingTemperature = 0.1;
	const double boltzmanConstant = 1;
	unordered_map<string,Node*> nodes;
	vector<string> generateInitialExpression();
protected:
	Node* sizeNodes(Node &nodeA, Node &nodeB, int cutType);
	Node* polishToTree(const vector<string>& experssion);
	double computeCost(Node* root);
	static bool acceptMove(double deltaCost, double temperature);
	static void move(vector<string>& currentPolish);
	static double coolDown(double temperature);
public:
	Floorplanner(list<Node>& nodes);
	void insertNode(Node& nodeA);
	void removeNode(string id);
	void floorplan();
	void printNodes();
};



#endif  /*FLOORPLANNER_HPP_*/
