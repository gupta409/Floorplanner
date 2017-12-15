#pragma once
#include"Graph.hpp"
class GraphOperations
{
private:
	Graph* g;
	vector<Vertex*> topologicalSort;
	int DFSVisit(Vertex &u, int time);
public:
	GraphOperations();
	GraphOperations(Graph* g);
	Vertex& addSource();
	Vertex& addSink();
	void performDFS();
	double getLongestPath();
	void printGraph();
	Graph* getGraph();
};

