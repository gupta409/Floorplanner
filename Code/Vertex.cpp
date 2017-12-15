#include "Vertex.hpp"


Vertex::Vertex(Node data)
{
	this->data = data;
}


Node& Vertex::getData()
{
	return this->data;
}

void Vertex::setData(Node & data)
{
	this->data = data;
}

void Vertex::addEdge(Vertex &destination, int weight)
{
	edgeList.insert(std::pair<std::string, Edge*>(destination.getData().getId(),new Edge(*this,destination,weight)));
}

Edge* Vertex::findEdge(Vertex & v)
{
	std::unordered_map<std::string, Edge*>::const_iterator got = edgeList.find(v.getData().getId());
	if (got == edgeList.end()) {
		std::cout << "Node not found";
		return NULL;
	}
	else {
		return got->second;
	}
}

bool Vertex::removeEdge(Vertex & v)
{
	if (edgeList.erase(v.getData().getId()) == 1) {
		return true;
	}
	else {
		return false;
	}
}

unordered_map<std::string, Edge*>& Vertex::getEdgeList()
{
	return this->edgeList;
}

void Vertex::init()
{
	this->distance = 0;
	this->visitTime = 0;
	this->finishTime = 0;
	this->isVisited = false;
	this->previous = NULL;
}

void Vertex::setVisitTime(int time)
{
	this->visitTime = time;
}

void Vertex::setFinishTime(int time)
{
	this->finishTime = time;
}

void Vertex::setIsVisited(bool isVisited)
{
	this->isVisited = isVisited;
}

void Vertex::setPrevious(Vertex * previous)
{
	this->previous = previous;
}

void Vertex::setDistance(double distance)
{
	this->distance = distance;
}

int Vertex::getVisitTime()
{
	return this->visitTime;
}

int Vertex::getFinishTime()
{
	return this->finishTime;
}

bool Vertex::getIsVisited()
{
	return this->isVisited;
}

Vertex * Vertex::getPrevious()
{
	return this->previous;
}

double Vertex::getDistance()
{
	return this->distance;
}



