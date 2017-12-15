#pragma once
#include "Floorplanner.hpp"
#include "GraphOperations.hpp"
class NonSlicingFloorplanner : public Floorplanner
{
private:
	void rotateObject(std::string id, int option);
	void swapFirstSeq(std::string idA, std::string idB);
	void swapSecondSeq(std::string idA, std::string idB);
	//void bothSeq();
protected:
	GraphOperations horizontalConstGraph;
	GraphOperations verticalConstGraph;
public:
	NonSlicingFloorplanner();
	NonSlicingFloorplanner(list<Node>& nodes);
	double computeCost(GraphOperations &graph);
	//void move();
	//void processCords();
	//double computeNetArea();
	//double computeBlackArea();
	//double computeCost();
};

