#pragma once
//#include "Vertex.hpp"
class Vertex;
class Edge {
private:
	Vertex *source;
	Vertex *destination;
	int weight;
public:
	Edge();
	Edge(Vertex &source, Vertex &destination, int weight);
	Vertex* getSource();
	void setSource(Vertex &source);
	Vertex* getDestination();
	void setDestination(Vertex &destination);
	int getWeight();
	void setWeight(int weight);
};