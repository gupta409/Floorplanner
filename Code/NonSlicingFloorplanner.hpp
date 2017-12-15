#pragma once
#include "Floorplanner.hpp"
#include "GraphOperations.hpp"
class NonSlicingFloorplanner : public Floorplanner
{
private:
	void rotateObject(std::string id, int option);
	void swapFirstSeq(std::string idA, std::string idB);
	void swapSecondSeq(std::string idA, std::string idB);
	void swapBothSeq(std::string idA, std::string idB);
	pair<vector<string>, vector<string>> seq_pair;
protected:
	
public:

	GraphOperations *horizontalConstGraph;
	GraphOperations *verticalConstGraph;

	NonSlicingFloorplanner();
	NonSlicingFloorplanner(list<Node>& nodes);
	double computeCost(GraphOperations &graph);
	pair<double, bool>* move(double previousCost, double temperature);
	void printSeqPair();
	unordered_map<std::string, Node*> * processCords();
	void floorplan();
	//double computeNetArea();
	//double computeBlackArea();
	//double computeCost();
};

