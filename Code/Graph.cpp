#include <vector>
#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
Graph::Graph()
{
}

Graph::Graph(Vertex &vertex)
{
	this->addVertex(vertex);
}

Graph::Graph(std::vector<Vertex> &vertices)
{
	for (Vertex v : vertices) {
		this->addVertex(v);
	}
}

void Graph::addVertex(Vertex& vertex)
{
	this->vertices.insert(std::pair<std::string,Vertex*>(vertex.getData().getId(),&vertex));
}


Edge* Graph::findEdge(Vertex & source, Vertex & destination)
{
	std::unordered_map<std::string, Vertex*>::const_iterator got = vertices.find(source.getData().getId());
	if (got == vertices.end()) {
		//std::cout << "Source Vertex not found";
		return NULL;
	}
	else {
		return source.findEdge(destination);
	}
}

bool Graph::removeEdge(Vertex & source, Vertex & destination)
{
	std::unordered_map<std::string, Vertex*>::const_iterator got = vertices.find(source.getData().getId());
	if (got == vertices.end()) {
		//std::cout << "Source Vertex not found";
		return false;
	}
	else {
		return source.removeEdge(destination);
	}
}

bool Graph::addEdge(Vertex & source, Vertex & destination)
{
	return false;
}

bool Graph::addEdge(Vertex &source, Vertex &destination, double weight)
{
	std::unordered_map<std::string, Vertex*>::const_iterator got = vertices.find(source.getData().getId());
	if (got == vertices.end()) {
		//std::cout << "Source Vertex not found";
		return false;
	}
	else {
		source.addEdge(destination,weight);
		return true;
	}
}

std::unordered_map<std::string, Vertex*>& Graph::getVertices()
{
	return this->vertices;
}

void Graph::updateWeight(Vertex &source, double newWeight) {
	std::unordered_map<std::string, Vertex*>::const_iterator got = vertices.find(source.getData().getId());
	if (got == vertices.end()) {
		//std::cout << "UpdateWeight: Source Vertex not found";
	}
	else {
		for (auto it : got->second->getEdgeList()) {
			it.second->setWeight(newWeight);
		}
	}
}

Vertex * Graph::findVertex(string id)
{
	std::unordered_map<std::string, Vertex*>::const_iterator got = vertices.find(id);
	if (got == vertices.end()) {
		//std::cout << "UpdateWeight: Source Vertex not found";
		return NULL;
	}
	else {
		return got->second;
	}
}
