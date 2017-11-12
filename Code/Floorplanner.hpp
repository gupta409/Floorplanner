
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
	void cleanupNodes();
	static bool acceptMove(double deltaCost, double temperature);
	static double coolDown(double temperature);
	double coolDownMoves(double movesPerStep);
	void Floorplanner::sizeNode(Node* parent);
public:
	void swapNodes(Node* a, Node* b);
	Node* polishToTree(const vector<string>& experssion);
	Floorplanner(list<Node>& nodes);
	vector<string> generateInitialExpression();
	void processCords(Node * root);
	static vector<string> move(vector<string> currentPolish);
	Node* floorplan();
	void printNodes();
	unordered_map<string, Node*> getNodes();
	double computeNetArea();
	double computeBlackArea(Node* root);
	double computeCost(Node* root);
	vector<string> fastMove(vector<string> currentPolish);
};



#endif  /*FLOORPLANNER_HPP_*/
