
#ifndef FLOORPLANNER_HPP_
#define FLOORPLANNER_HPP_
#include "unordered_map"
#include "Node.hpp"
#include "vector"
using namespace std;
void floorplannerUnitTest();
class Floorplanner {
private:
	
protected:
	unordered_map<string, Node*> nodes;
	Node* sizeNodes(Node &nodeA, Node &nodeB, int cutType);
	void cleanupNodes();
	static bool acceptMove(double deltaCost, double temperature);
	static double coolDown(double temperature);
	double coolDownMoves(double movesPerStep);
	void assignOptimum(Node* root);
public:
	Floorplanner();
	Floorplanner(list<Node>& nodes);
	Node* polishToTree(const vector<string>& experssion);
	vector<string> generateInitialExpression();
	void processCords(Node * root);
	static vector<string> move(vector<string> currentPolish);
	Node* floorplan();
	void printNodes();
	unordered_map<string, Node*> getNodes();
	virtual double computeNetArea();
	double computeBlackArea(Node* root);
	double computeCost(Node* root);
};



#endif  /*FLOORPLANNER_HPP_*/
