#pragma once
#include<unordered_map>
#include"Vertex.hpp"
#include"Edge.hpp"
class Graph {
protected:
	std::unordered_map<std::string, Vertex*> vertices;
public:
	Graph();
	Graph(Vertex &vertex);
	Graph(vector<Vertex> &vertices);
	void addVertex(Vertex &vertex);
	Edge* findEdge(Vertex &source, Vertex &destination);
	bool removeEdge(Vertex &source, Vertex &destination);
	bool addEdge(Vertex &source, Vertex &destination, int weight);
	std::unordered_map<std::string, Vertex*>& getVertices();
};