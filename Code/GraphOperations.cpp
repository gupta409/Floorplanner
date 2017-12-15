#include "GraphOperations.hpp"

void GraphOperations::performDFS()
{
	int time = 0;
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		std::cout << "Empty Graph Found";
		return;
	}
	else {
		//INIT Vertices
		for (auto it : data) {
			it.second->init();
		}
		//Start DFS
		for (auto it : data) {
			if (!it.second->getIsVisited()) {
				time = DFSVisit(*it.second, time);
			}
		}
	}
}

int GraphOperations::DFSVisit(Vertex &u, int time)
{
	time = time + 1;
	u.setVisitTime(time);
	u.setIsVisited(true);
	unordered_map<std::string, Edge*> edgeList = u.getEdgeList();
	if (!edgeList.empty()) {
		for (auto e : edgeList) {
			if (e.second->getDestination()->getIsVisited() == false) {
				e.second->getDestination()->setPrevious(&u);
				DFSVisit(*e.second->getDestination(), time);
			}
		}
	}
	time = time + 1;
	u.setFinishTime(time);
	topologicalSort.push_back(&u);
	return time;
}

double GraphOperations::getLongestPath()
{
	double distance = 0;
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		std::cout << "Empty Graph Found";
		return 0.0;
	}
	else {
		performDFS();
		for (auto it : data) {
			it.second->init();
		}
		for (int i = topologicalSort.size()-1; i >= 0;i--) {
			std::unordered_map<std::string, Edge*> edgeList = topologicalSort.at(i)->getEdgeList();
			for (auto e : edgeList) {
				if (e.second->getDestination()->getDistance() < topologicalSort.at(i)->getDistance() + e.second->getWeight()) {
					distance = topologicalSort.at(i)->getDistance() + e.second->getWeight();
					e.second->getDestination()->setDistance(distance);
				}
			}
		}
	}
	return distance;
}
GraphOperations::GraphOperations()
{
}
GraphOperations::GraphOperations(Graph* g)
{
	this->g = g;
	addSource();
	addSink();
}

Vertex& GraphOperations::addSource()
{
	Vertex *source = new Vertex(*new Node("super_source"));
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		std::cout << "Empty Graph Found";
	}
	else {
		g->addVertex(*source);
		for (auto it : data) {
			g->addEdge(*source, *it.second,0);
		}
	}
	return *source;
}
Vertex& GraphOperations::addSink()
{
	Vertex *sink = new Vertex(*new Node("super_sink"));
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		std::cout << "Empty Graph Found";
	}
	else {
		g->addVertex(*sink);
		for (auto it : data) {
			g->addEdge(*it.second,*sink);
		}
	}
	return *sink;
}

void GraphOperations::printGraph() {
	std::unordered_map<std::string, Vertex*> data = g->getVertices();
	if (data.empty()) {
		std::cout << "Empty Graph Found";
	}
	else {
		for (auto v : data) {
			std::cout << v.second->getData().getId()  << "\t\t" << v.second->getDistance() << endl;
		}
	}
}

Graph* GraphOperations::getGraph() {
	return this->g;
}