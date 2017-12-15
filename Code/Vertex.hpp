#pragma once
#include "unordered_map"
#include "string"
#include "Edge.hpp"
#include "Node.hpp"
void vertexUnitTest();
class Vertex{
private:
	Node data;
	unordered_map<std::string,Edge*> edgeList;
	//Data needed for graph operations
	double distance;
	int visitTime;
	int finishTime;
	bool isVisited;
	Vertex* previous;
public:
	Vertex(Node data);
	Node& getData();
	void setData(Node &data);
	void addEdge(Vertex &destination, int weight);
	Edge* findEdge(Vertex &v);
	bool removeEdge(Vertex &v);
	unordered_map<std::string, Edge*>& getEdgeList();
	//Graph operations related functions
	void init();
	//Setter and Getter functions
	void setVisitTime(int time);
	void setFinishTime(int time);
	void setIsVisited(bool isVisited);
	void setPrevious(Vertex* previous);
	void setDistance(double distance);
	int getVisitTime();
	int getFinishTime();
	bool getIsVisited();
	Vertex* getPrevious();
	double getDistance();
};
